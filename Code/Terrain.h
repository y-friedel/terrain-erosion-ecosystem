#include "maya.h"
#include "math.h"

enum LayerType
{
	LAYERTYPE_ROCK,
	LAYERTYPE_SAND,
	LAYERTYPE_WATER
};

class Terrain {
protected:
	double* bedRock;
	double* sandLayer;
	double* waterLayer;
	int size;
public:	
	Terrain(int x)
	{
		bedRock = new double[x*x];
		sandLayer = new double[x*x];
		waterLayer = new double[x*x];

		for(int j=0; j<x; j++)
		{
			for(int i=0; i<x; i++)
			{
				bedRock[j*x + i] = 0;
				sandLayer[j*x + i] = 0;
				waterLayer[j*x + i] = 0;
			}
		}

		size = x;
	};
	double getHeight(int x, int y);
	double getHeightOnLayer(int x, int y, int layer);
	int getLastLayer(int x, int y);

	void setLayerHeight(int x, int y, int layer, double height);

	MayaGeometry toMG();

};