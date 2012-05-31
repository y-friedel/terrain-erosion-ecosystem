#include "Foret.h"
#include "cmath"
#include <time.h>

Arbre::Arbre() : x(0), y(0), _age(0), _taille(0), _radius(0)
{

}

Arbre::Arbre(double _x, double _y) : x(_x), y(_y), _age(0), _taille(0), _radius(0)
{

}

Arbre::Arbre(double _x, double _y, int age, double taille) : x(_x), y(_y), _age(age), _taille(taille), _radius(taille)
{

}
double Arbre::getX() const
{
	return x;
}
double Arbre::getY() const
{
	return y;
}

int Arbre::getAge() const
{
	return _age;
}
double Arbre::getTaille() const
{
	return _taille;
}

double Arbre::getRadius() const
{
	return _radius;
}

bool Arbre::isInRadius(Arbre a)
{
	return( pow((x-a.getX()), 2) + pow((y-a.getY()),2) < a.getRadius()*10 );
}

void Arbre::setAge(int age)
{
	_age = age;
}

void Arbre::setTaille(double taille)
{
	_taille = taille;
}

bool Arbre::lifeProba(double proba)
{

	/* proba entre 0 et 1 */
	srand ( (unsigned int)time(NULL) );
	return ((double)rand()/(double)RAND_MAX < proba);

}

bool Arbre::grow()
{
	if(_age < 100)
	{
		_age ++;
		if(_taille <0.1)
		{
			_taille += 0.01;
		}
		_radius = _taille;
		return lifeProba(0.99);
	}
	return false;
}

Foret::Foret()
{
	_arbres = QVector<Arbre>();
}

void Foret::addArbre(Arbre a)
{
	_arbres.append(a);
}

void Foret::killArbre(int i)
{
	_arbres.remove(i);
}

Arbre Foret::getArbre(int i)
{
	return _arbres[i];
}

void Foret::allGrow()
{
	int k = 0;
	for(int i=0; i<_arbres.size(); i++)
	{
		//Si l'arbre est mort dans son developpement, on le retire de la liste
		if(!_arbres[i].grow())
		{
			_arbres.remove(i);	
		}
		else
		{
			//On parcours tous les arbres suivants dans la liste
			for(int j=i+1; j<_arbres.size(); j++)
			{
				//Si deux arbres sont trop proches
				if(_arbres[i].isInRadius(_arbres[j]))
				{
					k++;
					//On lance une proba pour savoir quel arbre partira
					if(_arbres[i].lifeProba(0.50))
					{
						_arbres.remove(j);
					}
					else
					{
						_arbres.remove(i);
						j = _arbres.size();
					}
				}
			}
		}
	}
	std::cout << "nb de collision : " << k << std::endl;
}

void Foret::fillTerrain(Terrain* ter, int nb_arbres, int type)
{
	int i = 0;
	double x_arbre;
	double y_arbre;
	bool ajout = false;
	int retrait;
	int delay=0;

	//Ajout du premier arbre
	srand((unsigned int)time(NULL));
	x_arbre = ((double)rand()/(double)RAND_MAX)*(ter->getSize()-1);
	y_arbre = ((double)rand()/(double)RAND_MAX)*(ter->getSize()-1);
	_arbres.append(Arbre(x_arbre, y_arbre));

			srand((unsigned int)time(NULL));
	std::cout << "REMPLISSAGE TERRAIN :" << std::endl;
	while(i < nb_arbres && delay != nb_arbres*nb_arbres)
	{
		delay++;
		do
		{
		x_arbre = ((double)rand()/(double)RAND_MAX)*(ter->getSize()-1);
		y_arbre = ((double)rand()/(double)RAND_MAX)*(ter->getSize()-1);
		}
		while(!ter->isVegHost((int)x_arbre, (int)y_arbre));

		Arbre ab = Arbre(x_arbre, y_arbre);
		retrait = 0;

		//Parcours de la liste d'arbres existants
		for(int n = 0; n < _arbres.size(); n++)
		{
			retrait = 0;
			Arbre concurrent = _arbres[n];

			//Si le concurrent est dans la zone de l'arbre
			if(concurrent.isInRadius(ab))
			{
				//Si le concurrent perd
				if(!concurrent.lifeProba(0.9))
				{
					//Le concurrent est elimine
					_arbres.remove(n);
					retrait++;
				}
				else
				{
					ajout = false;
					n = _arbres.size();
				}
			}
			else
			{
				ajout = true;
			}
		}

		if(ajout)
		{
			_arbres.append(Arbre(x_arbre, y_arbre, 1, 0.01));
			if(i%(int)(nb_arbres/100) == 0)
			{
				std::cout << "." ;
			}
			i++;
			i-=retrait;
		}
	}
	for (int i=0; i< _arbres.size(); i++)
	{
		//std::cout << i << " : (" << _arbres[i].getX() << "," << _arbres[i].getY() << ")" << std::endl;
	}
	std::cout << std::endl;
	std::cout << "FILL TERRAIN OK" << std::endl;

}

MayaGeometrySet Foret::foretToMGS(Terrain* ter)
{
	std::cout << "TO MGS" << std::endl;
	MayaGeometry mg = MayaGeometry("foret");

	MaterialObject mo={ ShaderPhong, None, AColor(0.3,0.6,0.3,1.0), AColor(0.5,0.4,0.2,1.0), AColor(0.1,0.1,0.1,1.0), 50.,QString("")};
	MaterialObject mo_tronc={ ShaderPhong, None, AColor(0.3,0.3,0.,1.0), AColor(0.5,0.4,0.2,1.0), AColor(0.1,0.1,0.1,1.0), 50.,QString("")};

	//Fabrication du MG arbre
	MayaGeometry mg_tree=MayaGeometry::CreateCone(Vector(0,0,.3),Vector(0,0,2), 0.3,50);
	mg_tree.setName("tree");
	mg_tree.setMaterialObject(mo);
	MayaGeometry mg_tronc=MayaGeometry::CreateCylinder(Vector(0,0,0),Vector(0,0,.3), 0.1,50);
	mg_tronc.setMaterialObject(mo_tronc);
	mg_tree.Merge(mg_tronc);

	MayaGeometrySet mgs = MayaGeometrySet(mg_tree,MayaFrame::Id);

	Vector posTree = Vector(0.);
	Vector scaleTree = Vector(1);
	int bla = 0;
	std::cout << _arbres.size() << std::endl;
	
	for(int j = 0; j < _arbres.size() ; j++)
	{
		scaleTree = Vector(_arbres[j].getTaille());
		Vector convertSize = ter->getTerrainPoint(_arbres[j].getX(), _arbres[j].getY(), ter->getHeight((int)_arbres[j].getX(), (int)_arbres[j].getY()) );
		Vector posTree = Vector(convertSize[0], convertSize[1], convertSize[2]-0.01);
		MayaFrame frame(Matrix::Identity, posTree, scaleTree);
		mgs.Append(frame);
	}

	return mgs;


}