#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <math.h>

class Layer
{
public:
	int size;
	double *v;
	double persistence;

public:
	Layer();
	Layer(int _size, double _p);
	~Layer();

	void random_v();
};


class Perlin_d
{
public:
	int size;
	Layer* l_random;

	int freq_init;

	std::vector<Layer*> t_layer;

public:
	Perlin_d(int _size, int nb_layers);
	~Perlin_d();

	void fill_layers();
	double* generate();
	double compute_value(int i, int j, double frequence, Layer* l);

};
