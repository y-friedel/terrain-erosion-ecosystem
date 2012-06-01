#ifndef __TERRAIN__
#define __TERRAIN__

#include "maya.h"
#include "math.h"

#include "Stuff.h"
//#include "Perlin.h"

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
	double* _sediment;
	double* _sedimentTmp;
	double _terrainSize;
	double _rainLevel;
	int _size;
	int _sizeArray;

public:
	bool* _growLayer;

public:
	Terrain(int x);
	double getHeight(int x, int y) const;
	double getHeightOnLayer(int x, int y, int layer) const;
	double getRelativeHeightOnLayer(int x, int y, int layer) const;
	int getLastLayer(int x, int y) const;

	//Vegetation
	void setGrowLayer();
	bool isVegHost(int x, int y) const;

	int getSize()
{
	return _size;
}
	void setAllLayer(double* height_map, int layer);
	void setLayerHeight(int x, int y, int layer, double height);

	Vector getTerrainPoint(int i, int j, double h) const;
	Vector getTerrainPoint(double i, double j, double h) const;

	MayaGeometry toMG() const;
	MayaGeometry noWaterToMG() const;
	MayaGeometry waterToMG() const;

//Fast Hydrolic Simulation
protected:
	void fhsWaterFlow_PipeCell(int i, int j);
	void fhsWaterFlow_Pipe();
	void fhsWaterFlow_Move();
	void fhsWaterFlow_Speed();
	void fhsErosion();
	void fhsTransport();

public:
	void fhsIterationWater();
	void fhsIterationErosion();
	void fhsRain(double level);
	void fhsEvaporation(double level);

	void thermalErosion(double T, double C);

	void jetDEau(int i, int j);
};

#endif