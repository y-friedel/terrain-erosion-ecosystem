#include "Terrain.h"

double Terrain::getHeight(int x, int y)
{
	return bedRock[y*size + x] + sandLayer[y*size + x] + waterLayer[y*size + x];
}

double Terrain::getHeightOnLayer(int x, int y, int layer)
{
	double height = bedRock[y*size + x];
	if(layer == LAYERTYPE_ROCK)
	{
		return height;
	}	
	if(layer == LAYERTYPE_SAND)
	{
		return height + sandLayer[y*size + x];
	}	
	if(layer == LAYERTYPE_WATER)
	{
		return height + sandLayer[y*size + x] + waterLayer[y*size + x];
	}

}

int Terrain::getLastLayer(int x, int y)
{
	if(waterLayer[y*size + x] != 0)
	{
		return LAYERTYPE_WATER;
	}
	if(sandLayer[y*size + x] != 0)
	{
		return LAYERTYPE_SAND;
	}
	return LAYERTYPE_ROCK;

}

void Terrain::setLayerHeight(int x, int y, int layer, double height)
{
	if(layer == LAYERTYPE_ROCK)
	{
		bedRock[y*size + x] = height;
	}
	if(layer == LAYERTYPE_SAND)
	{
		sandLayer[y*size + x] = height;
	}
	if(layer == LAYERTYPE_WATER)
	{
		waterLayer[y*size + x] = height;
	}
}

MayaGeometry Terrain::toMG()
{

	//Creation de la liste de Vecteurs et couleurs associées
	QVector<Vector> vec_point = QVector<Vector>();
	QVector<Vector> vec_couleur = QVector<Vector>();
	for(int j = 0; j<size; j++)
	{
		for(int i = 0; i<size; i++)
		{
			vec_point.append(Vector(i, j, getHeight(i, j)));
			if(getLastLayer(i, j) == LAYERTYPE_ROCK)
			{
				vec_couleur.append(Vector(0.3,0.3,0.3));
			}
			if(getLastLayer(i, j) == LAYERTYPE_SAND)
			{
				vec_couleur.append(Vector(255,255,0));
			}
			if(getLastLayer(i, j) == LAYERTYPE_WATER)
			{
				vec_couleur.append(Vector(255,0,0));
			}
		}

	}
	
	//Creation du QVector de triangles
	QVector<int> vec_tri_int = QVector<int>();
	for(int j = 0; j<(size-1); j++)
	{
		for(int i = 0; i<(size-1); i++)
		{
			vec_tri_int.append(j*size + i);
			vec_tri_int.append(j*size + i);

			vec_tri_int.append(j*size+ size + i+1);
			vec_tri_int.append(j*size+ size + i+1);

			vec_tri_int.append(j*size + size +i);
			vec_tri_int.append(j*size + size +i);

			vec_tri_int.append((j*size)+i);
			vec_tri_int.append((j*size)+i);

			vec_tri_int.append(j*size + (i+1));
			vec_tri_int.append(j*size + (i+1));

			vec_tri_int.append(j*size + size + (i+1));
			vec_tri_int.append(j*size + size + (i+1));

			//m.AddTriangle(vec_point.value((j*size)+i), vec_point.value(j*size+ size +i), vec_point.value(j*size+size+i+1));
			//m.AddTriangle(vec_point.value((j*size)+i), vec_point.value((j*size + size +(i+1))), vec_point.value(j*(size)+(i+1)));

		}
	}


	//Creation du QVector de normales
	QVector<Vector> vec_normale = QVector<Vector>(size*size);
	vec_normale.fill(Vector(0,0,0));

	for(int j = 0; j<vec_tri_int.size(); j+=6)
	{
		//std::cout << "OP " << vec_tri_int.value(j) << " " << vec_tri_int.value(j+2) << " " << vec_tri_int.value(j+4) << std::endl;
		
		double x1 = vec_point.value(vec_tri_int.value(j))[0];
		double y1 = vec_point.value(vec_tri_int.value(j))[1];;
		double z1 = vec_point.value(vec_tri_int.value(j))[2];;

		double x2 = vec_point.value(vec_tri_int.value(j+2))[0];;
		double y2 = vec_point.value(vec_tri_int.value(j+2))[1];;
		double z2 = vec_point.value(vec_tri_int.value(j+2))[2];;

		double x3 = vec_point.value(vec_tri_int.value(j+4))[0];;
		double y3 = vec_point.value(vec_tri_int.value(j+4))[1];;
		double z3 = vec_point.value(vec_tri_int.value(j+4))[2];;

		double x = (y2-y1)*(z3-z1) - (z2-z1)*(y3-y1);
		double y = (z2-z1)*(x3-x1) - (x2-x1)*(z3-z1);
		double z = (x2-x1)*(y3-y1) - (y2-y1)*(x3-x1);

		Vector normale = Vector(x, y, z);

		vec_normale[vec_tri_int.value(j)]+=normale;
		vec_normale[vec_tri_int.value(j+2)]+=normale;
		vec_normale[vec_tri_int.value(j+4)]+=normale;

	}

	//Création du MG
	
	MaterialObject mo={ ShaderPhong, VertexColor, AColor(0.3,0.3,0.3,1.0), AColor(0.5,0.4,0.2,1.0), AColor(0.1,0.1,0.1,1.0), 50.,QString("")};
	//MaterialObject mo={ ShaderPhong, VertexColor, AColor(0.1,0.1,0.1,1.0), AColor(0.5,0.2,0.2,1.0), AColor(0.1,0.1,0.1,1.0), 50.,QString("")};
	MayaGeometry m = MayaGeometry("mg_terrain", vec_point, vec_normale, vec_couleur, vec_tri_int, mo);

	return m;
}