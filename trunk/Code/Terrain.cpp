#include "Terrain.h"

#include <cmath>

Terrain::Terrain(int size)
{
	_size = size;
	_sizeArray = _size*_size;

	_bedRock = new double[_sizeArray];
	_sandLayer = new double[_sizeArray];
	_waterLayer = new double[_sizeArray];
	_growLayer = new bool[_sizeArray];

	//Hydrolic Erosion
	_waterPipe = new double[_sizeArray*4];
	_waterVelocity = new double[_sizeArray*2];
	_sediment = new double[_sizeArray];
	_sedimentTmp = new double[_sizeArray];

	for(int i=0; i<_sizeArray; i++)
	{
		_bedRock[i] = 0;
		_sandLayer[i] = 0;
		_waterLayer[i] = 0;
		_growLayer[i] = false;
		_sediment[i] = 0;

		//Hydrolic Erosion
		_waterPipe[i*4  ] = 0.0;
		_waterPipe[i*4+1] = 0.0;
		_waterPipe[i*4+2] = 0.0;
		_waterPipe[i*4+3] = 0.0;
		_waterVelocity[i*2  ] = 0.0;
		_waterVelocity[i*2+1] = 0.0;
	}
	

}

double Terrain::getHeight(int x, int y) const
{
	int ind = y*_size + x;
	return _bedRock[ind] + _sandLayer[ind] + _waterLayer[ind];
}

double Terrain::getHeightOnLayer(int x, int y, int layer) const
{
	int ind = y*_size + x;
	if(ind < 0 || ind > _sizeArray) return -1;

	double height = _bedRock[ind];
	if(layer == LAYERTYPE_ROCK)
	{
		return height;
	}	
	if(layer == LAYERTYPE_SAND)
	{
		return height + _sandLayer[ind];
	}	
	if(layer == LAYERTYPE_WATER)
	{
		return height + _sandLayer[ind] + _waterLayer[ind];
	}
	else
	{
		return -1;
	}
}

double Terrain::getRelativeHeightOnLayer(int x, int y, int layer) const
{
	int ind = y*_size + x;
	if(layer == LAYERTYPE_ROCK)
	{
		return _bedRock[ind];
	}	
	if(layer == LAYERTYPE_SAND)
	{
		return _sandLayer[ind];
	}	
	if(layer == LAYERTYPE_WATER)
	{
		return _waterLayer[ind];
	}
	else
	{
		return -1;
	}
}

int Terrain::getLastLayer(int x, int y) const
{
	int ind = y*_size + x;
	if(_waterLayer[ind] != 0)
	{
		return LAYERTYPE_WATER;
	}
	if(_sandLayer[ind] != 0)
	{
		return LAYERTYPE_SAND;
	}
	return LAYERTYPE_ROCK;

}



void Terrain::setLayerHeight(int x, int y, int layer, double height)
{
	int ind = y*_size + x;
	if(layer == LAYERTYPE_ROCK)
	{
		_bedRock[ind] = height;
	}
	if(layer == LAYERTYPE_SAND)
	{
		_sandLayer[ind] = height;
	}
	if(layer == LAYERTYPE_WATER)
	{
		_waterLayer[ind] = height;
	}
}

void Terrain::setAllLayer(double* height_map, int layer)
{
	for(int i=0; i<_sizeArray; i++)
	{
		_bedRock[i] = height_map[i];
	}
}

MayaGeometry Terrain::toMG() const
{

	//Creation de la liste de Vecteurs et couleurs associ�es
	//couleurs
	//(0,0,0)=Tex1
	//(1,0,0)=Tex2
	//(0,1,0)=Tex3
	//(0,0,1)=Tex4
	QVector<Vector> vec_point = QVector<Vector>();
	QVector<Vector> vec_couleur = QVector<Vector>();

	for(int j = 0; j<_size; j++)
	{
		for(int i = 0; i<_size; i++)
		{
			if(getLastLayer(i, j) == LAYERTYPE_ROCK)
			{
				if(isVegHost(i, j))
				{
					vec_couleur.append(Vector(0.3,0.6,0.3));
				}
				else
				{
					vec_couleur.append(Vector(0.3,0.3,0.3));
				}
				//vec_couleur.append(Vector(0,0,0));
				vec_point.append(Vector(i, j, getHeight(i, j)));
			}
			if(getLastLayer(i, j) == LAYERTYPE_SAND)
			{
				vec_couleur.append(Vector(0.5,0.4,0.2));
				//vec_couleur.append(Vector(0,1,0));
				vec_point.append(Vector(i, j, getHeight(i, j)));
			}
			if(getLastLayer(i, j) == LAYERTYPE_WATER)
			{
				if(getRelativeHeightOnLayer(i, j, LAYERTYPE_SAND) > 2)
				{
					vec_couleur.append(Vector(0.5,0.4,0.2));
				}
				else
				{
					if(isVegHost(i, j))
					{
						vec_couleur.append(Vector(0.3,0.6,0.3));
					}
					else
					{
						vec_couleur.append(Vector(0.3,0.3,0.3));
					}
				}
				//vec_couleur.append(Vector(0,0,1));
				vec_point.append(Vector(i, j, getHeightOnLayer(i, j, LAYERTYPE_SAND)));
			}
		}

	}
	
	//Creation du QVector de triangles
	QVector<int> vec_tri_int = QVector<int>();
	for(int j = 0; j<(_size-1); j++)
	{
		for(int i = 0; i<(_size-1); i++)
		{
			vec_tri_int.append(j*_size + i);
			vec_tri_int.append(j*_size + i);

			vec_tri_int.append(j*_size+ _size + i+1);
			vec_tri_int.append(j*_size+ _size + i+1);

			vec_tri_int.append(j*_size + _size +i);
			vec_tri_int.append(j*_size + _size +i);

			vec_tri_int.append((j*_size)+i);
			vec_tri_int.append((j*_size)+i);

			vec_tri_int.append(j*_size + (i+1));
			vec_tri_int.append(j*_size + (i+1));

			vec_tri_int.append(j*_size + _size + (i+1));
			vec_tri_int.append(j*_size + _size + (i+1));

			//m.AddTriangle(vec_point.value((j*size)+i), vec_point.value(j*size+ size +i), vec_point.value(j*size+size+i+1));
			//m.AddTriangle(vec_point.value((j*size)+i), vec_point.value((j*size + size +(i+1))), vec_point.value(j*(size)+(i+1)));

		}
	}


	//Creation du QVector de normales
	QVector<Vector> vec_normale = QVector<Vector>(_sizeArray);
	vec_normale.fill(Vector(0,0,0));

	for(int j = 0; j<vec_tri_int.size(); j+=6)
	{
		//std::cout << "OP " << vec_tri_int.value(j) << " " << vec_tri_int.value(j+2) << " " << vec_tri_int.value(j+4) << std::endl;
		
		double x1 = vec_point.value(vec_tri_int.value(j))[0];
		double y1 = vec_point.value(vec_tri_int.value(j))[1];
		double z1 = vec_point.value(vec_tri_int.value(j))[2];

		double x2 = vec_point.value(vec_tri_int.value(j+2))[0];
		double y2 = vec_point.value(vec_tri_int.value(j+2))[1];
		double z2 = vec_point.value(vec_tri_int.value(j+2))[2];

		double x3 = vec_point.value(vec_tri_int.value(j+4))[0];
		double y3 = vec_point.value(vec_tri_int.value(j+4))[1];
		double z3 = vec_point.value(vec_tri_int.value(j+4))[2];

		double x = (y2-y1)*(z3-z1) - (z2-z1)*(y3-y1);
		double y = (z2-z1)*(x3-x1) - (x2-x1)*(z3-z1);
		double z = (x2-x1)*(y3-y1) - (y2-y1)*(x3-x1);

		Vector normale = Vector(x, y, z);

		vec_normale[vec_tri_int.value(j)]+=normale;
		vec_normale[vec_tri_int.value(j+2)]+=normale;
		vec_normale[vec_tri_int.value(j+4)]+=normale;

	}

	//Cr�ation du MG

	
	//MaterialObject mo={ ShaderTextureUV, UVMapping, AColor(0.5,0.5,0.5,1.0), AColor(0.3,0.3,0.3,1.0), AColor(0.1,0.1,0.1,1.0), 50.,QString("Shaders\Tex1.bmp")};
	//MaterialObject mo={ ShaderTerrainTexture3D, VertexColor, AColor(0.5,0.5,0.5,1.0), AColor(0.3,0.3,0.3,1.0), AColor(0.1,0.1,0.1,1.0), 50., QString("")};
	MaterialObject mo={ ShaderPhongVertexColor, VertexColor, AColor(0.5,0.5,0.5,1.0), AColor(0.3,0.3,0.3,1.0), AColor(0.1,0.1,0.1,1.0), 50.,QString("")};

	MayaGeometry m = MayaGeometry("mg_terrain", vec_point, vec_normale, vec_couleur, vec_tri_int, mo);

	return m;
}


MayaGeometry Terrain::waterToMG() const
{

	//Creation de la liste de Vecteurs et couleurs associ�es
	QVector<Vector> vec_point = QVector<Vector>();
	QVector<Vector> vec_couleur = QVector<Vector>();
	for(int j = 0; j<_size; j++)
	{
		for(int i = 0; i<_size; i++)
		{
			
			if(getLastLayer(i, j) == LAYERTYPE_ROCK)
			{
				vec_couleur.append(Vector());
				vec_point.append(Vector(i, j, 0));
			}
			if(getLastLayer(i, j) == LAYERTYPE_SAND)
			{
				vec_couleur.append(Vector());
				vec_point.append(Vector(i, j, 0));
			}
			if(getLastLayer(i, j) == LAYERTYPE_WATER)
			{
				vec_couleur.append(Vector(0.4,0.5,0.8));
				//vec_couleur.append(Vector(0,0,1));
				if(getRelativeHeightOnLayer(i, j, LAYERTYPE_WATER) > 0.1)
				{
					vec_point.append(Vector(i, j, getHeight(i, j)));
				}else{
					vec_point.append(Vector(i, j, 0));
				}
			}
		}

	}
	
	//Creation du QVector de triangles
	QVector<int> vec_tri_int = QVector<int>();
	for(int j = 0; j<(_size-1); j++)
	{
		for(int i = 0; i<(_size-1); i++)
		{
			vec_tri_int.append(j*_size + i);
			vec_tri_int.append(j*_size + i);

			vec_tri_int.append(j*_size+ _size + i+1);
			vec_tri_int.append(j*_size+ _size + i+1);

			vec_tri_int.append(j*_size + _size +i);
			vec_tri_int.append(j*_size + _size +i);

			vec_tri_int.append((j*_size)+i);
			vec_tri_int.append((j*_size)+i);

			vec_tri_int.append(j*_size + (i+1));
			vec_tri_int.append(j*_size + (i+1));

			vec_tri_int.append(j*_size + _size + (i+1));
			vec_tri_int.append(j*_size + _size + (i+1));
		}
	}


	//Creation du QVector de normales
	QVector<Vector> vec_normale = QVector<Vector>(_sizeArray);
	vec_normale.fill(Vector(0,0,0));

	for(int j = 0; j<vec_tri_int.size(); j+=6)
	{
		
		double x1 = vec_point.value(vec_tri_int.value(j))[0];
		double y1 = vec_point.value(vec_tri_int.value(j))[1];
		double z1 = vec_point.value(vec_tri_int.value(j))[2];

		double x2 = vec_point.value(vec_tri_int.value(j+2))[0];
		double y2 = vec_point.value(vec_tri_int.value(j+2))[1];
		double z2 = vec_point.value(vec_tri_int.value(j+2))[2];

		double x3 = vec_point.value(vec_tri_int.value(j+4))[0];
		double y3 = vec_point.value(vec_tri_int.value(j+4))[1];
		double z3 = vec_point.value(vec_tri_int.value(j+4))[2];

		double x = (y2-y1)*(z3-z1) - (z2-z1)*(y3-y1);
		double y = (z2-z1)*(x3-x1) - (x2-x1)*(z3-z1);
		double z = (x2-x1)*(y3-y1) - (y2-y1)*(x3-x1);

		Vector normale = Vector(x, y, z);

		vec_normale[vec_tri_int.value(j)]+=normale;
		vec_normale[vec_tri_int.value(j+2)]+=normale;
		vec_normale[vec_tri_int.value(j+4)]+=normale;

	}

	//Cr�ation du MG
	
	MaterialObject mo={ ShaderPhongVertexColor, VertexColor, AColor(1,0,0,1), AColor(0.6,0.6,0.6,0.6), AColor(1,1,1,0), 50.,QString("")};
	//MaterialObject mo={ ShaderPhongVertexColor, Wireframe, AColor(0.5,0.5,0.5,1.0), AColor(0.3,0.3,0.3,1.0), AColor(0.1,0.1,0.1,1.0), 50.,QString("")};

	MayaGeometry m = MayaGeometry("mg_water", vec_point, vec_normale, vec_couleur, vec_tri_int, mo);

	return m;
}






void Terrain::fhsWaterFlow_PipeCell(int i, int j)
{
	const double dt = 0.00003;
	const double g = 9.809; //Gravity on Paris
	const double A = 2.5;
	const double l = 1./0.01;

	int ind = j*_size+i;
	double dh;

		_waterPipe[ind*4  ] = 0;
		_waterPipe[ind*4+1] = 0;
		_waterPipe[ind*4+2] = 0;
		_waterPipe[ind*4+3] = 0;

		_waterPipe[ind*4  ] = -_waterVelocity[ind*2+0]*dt*2500;
		_waterPipe[ind*4+1] = +_waterVelocity[ind*2+1]*dt*2500;
		_waterPipe[ind*4+2] = +_waterVelocity[ind*2+0]*dt*2500;
		_waterPipe[ind*4+3] = -_waterVelocity[ind*2+1]*dt*2500;

	//Left
	if(i > 0)
	{
		dh = getHeight(i, j) - getHeight(i-1, j);
		_waterPipe[ind*4  ] += dt*A*g*l*dh;
		if(_waterPipe[ind*4  ] < 0) _waterPipe[ind*4  ] = 0;
	}

	//Top
	if(j < _size-1)
	{
		dh = getHeight(i, j) - getHeight(i, j+1);
		_waterPipe[ind*4+1] += dt*A*g*l*dh;
		if(_waterPipe[ind*4+1] < 0) _waterPipe[ind*4+1] = 0;
	}

	//Right
	if(i < _size-1)
	{
		dh = getHeight(i, j) - getHeight(i+1, j);
		_waterPipe[ind*4+2] += dt*A*g*l*dh;
		if(_waterPipe[ind*4+2] < 0) _waterPipe[ind*4+2] = 0;
	}

	//Bottom
	if(j > 0)
	{
		dh = getHeight(i, j) - getHeight(i, j-1);
		_waterPipe[ind*4+3] += dt*A*g*l*dh;
		if(_waterPipe[ind*4+3] < 0) _waterPipe[ind*4+3] = 0;
	}

	//Normalize
	double wh = getRelativeHeightOnLayer(i, j, LAYERTYPE_WATER);
	double ws = 0;
	ws += _waterPipe[ind*4  ];
	ws += _waterPipe[ind*4+1];
	ws += _waterPipe[ind*4+2];
	ws += _waterPipe[ind*4+3];

	if(ws > wh)
	{
		double ratio;
		if(ws > 0.1) ratio = wh/ws;
		else ratio = 0;

		_waterPipe[ind*4  ] *= ratio;
		_waterPipe[ind*4+1] *= ratio;
		_waterPipe[ind*4+2] *= ratio;
		_waterPipe[ind*4+3] *= ratio;
	}
	/*double K = getRelativeHeightOnLayer(i, j, LAYERTYPE_WATER);*/


}

void Terrain::fhsWaterFlow_Pipe()
{
	for(int j=0; j<_size; j++)
	{
		for(int i=0; i<_size; i++)
		{
			fhsWaterFlow_PipeCell(i, j);
		}
	}
}


void Terrain::fhsWaterFlow_Speed()
{
	int ind, nInd;
	for(int j=0; j<_size; j++)
	{
		for(int i=0; i<_size; i++)
		{
			ind = j*_size+i;

			double wvX = 0;
			double wvY = 0;

			//Left
			if(i > 0)
			{
				nInd = j*_size+i-1;
				wvX += _waterPipe[nInd*4+2] - _waterPipe[ind*4+0];
			}

			//Top
			if(j < _size-1)
			{
				nInd = (j+1)*_size+i;
				wvY += _waterPipe[ind*4+1] - _waterPipe[nInd*4+3];
			}

			//Right
			if(i < _size-1)
			{
				nInd = j*_size+i+1;
				wvX += _waterPipe[ind*4+2] - _waterPipe[nInd*4+0];
			}

			//Bottom
			if(j > 0)
			{
				nInd = (j-1)*_size+i;
				wvY += _waterPipe[nInd*4+1] - _waterPipe[ind*4+3];
			}

			wvX *= 2;
			wvY *= 2;
			
			_waterVelocity[ind*2+0] = wvX;
			_waterVelocity[ind*2+1] = wvY;
		}
	}
}

void Terrain::fhsWaterFlow_Move()
{
	double wl, wmotion = 0;
	int ind, nInd;
	for(int j=0; j<_size; j++)
	{
		for(int i=0; i<_size; i++)
		{
			wl = getRelativeHeightOnLayer(i, j, LAYERTYPE_WATER);
			
			ind = j*_size+i;
			wl -= _waterPipe[ind*4  ];
			wl -= _waterPipe[ind*4+1];
			wl -= _waterPipe[ind*4+2];
			wl -= _waterPipe[ind*4+3];

			//Left
			if(i > 0)
			{
				nInd = j*_size+i-1;
				wl += _waterPipe[nInd*4+2];
			}

			//Top
			if(j < _size-1)
			{
				nInd = (j+1)*_size+i;
				wl += _waterPipe[nInd*4+3];
			}

			//Right
			if(i < _size-1)
			{
				nInd = j*_size+i+1;
				wl += _waterPipe[nInd*4+0];
			}

			//Bottom
			if(j > 0)
			{
				nInd = (j-1)*_size+i;
				wl += _waterPipe[nInd*4+1];
			}

			//if(wl < 0.01) wl = 0;

			wmotion += wl;

			double dd = getRelativeHeightOnLayer(i, j, LAYERTYPE_WATER) + wl / 2.0;

			setLayerHeight(i, j, LAYERTYPE_WATER, wl);
		}
	}
}


void Terrain::fhsRain()
{
	for(int j=0; j<_size; j++)
	{
		for(int i=0; i<_size; i++)
		{
			double d = getRelativeHeightOnLayer(i, j, LAYERTYPE_WATER);
			setLayerHeight(i, j, LAYERTYPE_WATER, d+0.1);
		}
	}
}

void Terrain::fhsEvaporation()
{
	for(int j=0; j<_size; j++)
	{
		for(int i=0; i<_size; i++)
		{
			double d = getRelativeHeightOnLayer(i, j, LAYERTYPE_WATER);
			setLayerHeight(i, j, LAYERTYPE_WATER, max(d-0.1, 0.0));
		}
	}
}

void Terrain::fhsErosion()
{
	int ind;
	for(int j=0; j<_size; j++)
	{
		for(int i=0; i<_size; i++)
		{
			double d = getHeightOnLayer(i, j, LAYERTYPE_ROCK);
			
			ind = j*_size+i;

			double dhX = 0;
			double dhY = 0;

			//Left
			if(i > 0)
			{
				dhX += getHeightOnLayer(i-1, j, LAYERTYPE_ROCK);
			}

			//Top
			if(j < _size-1)
			{
				dhY -= getHeightOnLayer(i, j+1, LAYERTYPE_ROCK);
			}

			//Right
			if(i < _size-1)
			{
				dhX -= getHeightOnLayer(i+1, j, LAYERTYPE_ROCK);
			}

			//Bottom
			if(j > 0)
			{
				dhY += getHeightOnLayer(i, j-1, LAYERTYPE_ROCK);
			}

			double tilt = sqrt(dhX*dhX+dhY*dhY)*sqrt(pow(_waterVelocity[ind*2+0], 2) + pow(_waterVelocity[ind*2+1], 2))*0.1;
			

			if(tilt < 0.1)
			{
				setLayerHeight(i, j, LAYERTYPE_ROCK, d+_sediment[ind]*0.5);
				_sediment[ind] *= 0.5;
			}
			else
			{
				double newRock = max(0.0, d - tilt);
				setLayerHeight(i, j, LAYERTYPE_ROCK, newRock);
				_sediment[ind] += d - newRock;
				_sedimentTmp[ind] = 0;
			}
		}
	}
}

void Terrain::fhsTransport()
{
	int ind;
	for(int j=0; j<_size; j++)
	{
		for(int i=0; i<_size; i++)
		{
			ind = j*_size+i;
			_sedimentTmp[ind] = 0;
		}
	}

	for(int j=0; j<_size; j++)
	{
		for(int i=0; i<_size; i++)
		{
			ind = j*_size+i;
			
			int nx = max(min(i+(int)(_waterVelocity[ind*2+0]*0.5), _size-1), 0);
			int ny = max(min(j+(int)(_waterVelocity[ind*2+1]*0.5), _size-1), 0);

			_sedimentTmp[ind] += _sediment[ind];
		}
	}

	for(int j=0; j<_size; j++)
	{
		for(int i=0; i<_size; i++)
		{
			ind = j*_size+i;
			_sediment[ind] = _sedimentTmp[ind];
		}
	}
}

void Terrain::fhsIteration()
{
	fhsRain();
	fhsWaterFlow_Pipe();
	fhsWaterFlow_Speed();
	fhsWaterFlow_Move();
	fhsErosion();
	fhsTransport();

	fhsEvaporation();
}

void Terrain::jetDEau(int i, int j)
{
	setLayerHeight(i, j ,LAYERTYPE_WATER,100);
	//_waterVelocity[(j*_size+i)*2+0] = 10.0;
}

//Vegetation data
void Terrain::setGrowLayer()
{
	//Calcul du niveau d'eau
	double* waterPart = new double[_sizeArray];
	double water_cell = 0;
	for(int i = 0; i < _sizeArray; i++)
	{
		water_cell = _waterLayer[i];
		waterPart[i] = _waterLayer[i];
		_growLayer[i] = false;
	}

	//Flou simulant l'infiltration
	gaussian2D(waterPart, _size, 5);

	//Calcul des pentes
	int p00, p01, p10, p11;

	for(int j=0; j<_size; j++)
	{
		for(int i=0; i<_size; i++)
		{
			p00= getHeightOnLayer(i-1, j, LAYERTYPE_ROCK);
			p01= getHeightOnLayer(i+1, j, LAYERTYPE_ROCK);
			p10= getHeightOnLayer(i, j-1, LAYERTYPE_ROCK);
			p11= getHeightOnLayer(i, j+1, LAYERTYPE_ROCK);
			_growLayer[i + _size*j] = 
					waterPart[i + _size*j] > 0 
				&& _waterLayer[i + _size*j] <= 0.1
				&& max(max(p00, p01), max(p10, p11)) - min(min(p00, p01), min(p10, p11)) < 2
				;
				
			//std::cout << _growLayer[i + _size*j] << " ";
		}
		//std::cout << endl;
	}
	

	//Affinage
	int compteur;
	bool redo = true;
	std::cout << "OKOKOKOKOKOKOKOK" << endl;
	while(redo)
	{
		redo = false;
		for(int j=1; j<_size-1; j++)
		{
			for(int i=1; i<_size-1; i++)
			{
				compteur = 0;
				if(_growLayer[i+1 + _size*j] || _waterLayer[i+1 + _size*j] >= 0.1) compteur ++;
				if(_growLayer[i-1 + _size*j] || _waterLayer[i-1 + _size*j] >= 0.1) compteur ++;
				if(_growLayer[i + _size*(j+1)] || _waterLayer[i + _size*(j+1)] >= 0.1) compteur ++;
				if(_growLayer[i + _size*(j-1)] || _waterLayer[i + _size*(j-1)] >= 0.1) compteur ++;
				//std::cout << compteur << std::endl;
				if(compteur <2 && _growLayer[i + _size*j] && _growLayer[i + _size*j])
				{
					//std::cout << "clean" << std::endl;
					_growLayer[i + _size*j] = false;
					redo = true;
				}
				if(compteur >2 && !_growLayer[i + _size*j])
				{
					_growLayer[i + _size*j] = true;
					redo = true;
				}

			}
		}
	}

}

bool Terrain::isVegHost(int x, int y) const
{
	return _growLayer[x+ _size*y];
}