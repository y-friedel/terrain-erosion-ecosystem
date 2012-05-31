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
	return( pow((x-a.getX()), 2) + pow((y-a.getY()),2) < a.getRadius() );
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
	return (proba > (double)rand()/(double)RAND_MAX);

}

bool Arbre::grow()
{
	if(_age < 100)
	{
		_age ++;
		_taille += 0.1;
		_radius = _taille;
		return true;
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
	while(i < nb_arbres || delay == 20000)
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
			_arbres.append(Arbre(x_arbre, y_arbre, 1, 0.1));
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

MayaGeometrySet Foret::ForetToMGS(Terrain* ter)
{
	std::cout << "TO MGS" << std::endl;
	MayaGeometry mg = MayaGeometry("foret");

	//Fabrication du MG arbre
	MayaGeometry mg_tree=MayaGeometry::CreateCone(Vector(0,0,.3),Vector(0,0,2), 0.3,50);
	mg_tree.setName("tree");
	MayaGeometry mg_tronc=MayaGeometry::CreateCylinder(Vector(0,0,0),Vector(0,0,.3), 0.1,50);
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