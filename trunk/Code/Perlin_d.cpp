#include "Perlin_d.h"

#include <cstdlib>
#include <cmath>
#include <ctime>

#define max(a,b) (a>=b?a:b)
#define min(a,b) (a<=b?a:b)

Layer::Layer()
{
}

Layer::Layer(int _size, double _p)
{
	size = _size;
	v = new double[size*size];
	for (int j=0; j<size*size ; j++)
	{
		v[j]=0;
	}
	persistence = _p;
}

Layer::~Layer()
{
	delete(v);
}

void Layer::random_v()
{
	/* initialize random seed: */
	srand ( (unsigned int)time(NULL) );
	for (int j=0; j<size*size; j++)
	{
		/* generate random number: */
		v[j] = 255.0*(double)rand()/(double)RAND_MAX;
	}
}

Perlin_d::Perlin_d(int _size, int nb_layers)
{
	size = _size;
	freq_init = 2;
	l_random = new Layer(131, 1);
	l_random->random_v();
	t_layer = std::vector<Layer*>();
	double pers = 0.5;
	for(int i=0; i<nb_layers; i++)
	{
		Layer* layer = new Layer(size, pers);
		t_layer.push_back(layer);
		pers/=2;
	}
}

Perlin_d::~Perlin_d()
{
	delete l_random;
	for(int i=0; i<t_layer.size(); i++)
	{
		delete t_layer[i];
	}
}

double interpolate(double y1, double y2, double n, double delta){
	if (n==0)
	    return y1;
	if (n==1)
	    return y2;
	
	float a = (float)(delta/n);
	
	float v1 = 3*pow(1-a, 2) - 2*pow(1-a,3);
	float v2 = 3*pow(a, 2)   - 2*pow(a, 3);
	
	return y1*v1 + y2*v2;
}

double Perlin_d::compute_value(int i, int j, double frequence, Layer* l){
	/* déterminations des bornes */
	int borne1x, borne1y, borne2x, borne2y, q;
	float pas = (float)((t_layer[0]->size)/frequence);

	q = (int)(i/pas);
	borne1x = (int)(q*pas);
	borne2x = (int)((q+1)*pas);

	q = (int)(j/pas);
	borne1y = (int)(q*pas);
	borne2y = (int)((q+1)*pas);

	//std::cout << borne1x%l->size << " " << borne2x%l->size << " " << borne1y%l->size << " " << borne2y%l->size << std::endl;

	/* récupérations des valeurs aléatoires aux bornes */
	double b00,b01,b10,b11;
	b00 = l->v[borne1x%l->size + l->size*(borne1y%l->size)];
	b01 = l->v[borne1x%l->size + l->size*(borne2y%l->size)];
	b10 = l->v[borne2x%l->size + l->size*(borne1y%l->size)];
	b11 = l->v[borne2x%l->size + l->size*(borne2y%l->size)];

	//std::cout << borne1x%l->size + l->size*borne1y%l->size << " " << borne1x%l->size + l->size*borne2y%l->size << std::endl;

	//std::cout << b00 << " " << b01 << " " << b10 << " " << b11 << std::endl;

	double v1  = interpolate(b00, b01, borne2y-borne1y, j-borne1y);
	double v2  = interpolate(b10, b11, borne2y-borne1y, j-borne1y);


	double fin = interpolate(v1, v2, borne2x-borne1x , i-borne1x);

	return fin;
}

void Perlin_d::fill_layers()
{
	double current_freq = freq_init;
	//On parcourt chaque calque
	for(unsigned int s=0; s<t_layer.size(); s++)
	{
		//Dans chaque calque, on interpole a partir du calque random
		for(int j=0; j<size; j++)
		{
			for(int i=0; i<size; i++)
			{
				t_layer[s]->v[i + size*j] = compute_value(i, j, current_freq, l_random);
			}
		}
		current_freq*=freq_init;
	}
}

double* Perlin_d::generate()
{
	fill_layers();
	double* result = new double[size*size];

	for (int i=0; i<size*size; i++)
	{
		result[i]=0;
	}

	for(int i=0; i<size*size; i++)
	{
		for(unsigned int s=0; s<t_layer.size(); s++)
		{
			result[i]+=(t_layer[s]->v[i])*(t_layer[s]->persistence);
							//std::cout<< "hahahah L"<< s << " " << result[i] << std::endl;
		}
	}

	return result;

}
