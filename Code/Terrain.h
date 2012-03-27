#ifndef __TERRAIN__
#define __TERRAIN__

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
	double* _bedRock;
	double* _sandLayer;
	double* _waterLayer;
	double* _waterPipe;
	double* _waterVelocity;
	int _size;
	int _sizeArray;

public:	
	Terrain(int x);
	double getHeight(int x, int y) const;
	double getHeightOnLayer(int x, int y, int layer) const;
	double getRelativeHeightOnLayer(int x, int y, int layer) const;
	int getLastLayer(int x, int y) const;

	void setLayerHeight(int x, int y, int layer, double height);

	MayaGeometry toMG() const;

//Fast Hydrolic Simulation
protected:
	void fhsWaterFlow_PipeCell(int i, int j);
	void fhsWaterFlow_Pipe();
	void fhsWaterFlow_Move();

public:
	void fhsIteration();
};

#endif