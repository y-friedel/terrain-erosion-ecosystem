#include "Perlin_d.h"


Layer::Layer()
{
}

Layer::Layer(int _size, float _p)
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
	srand ( time(NULL) );
	for (int j=0; j<size*size; j++)
	{
		/* generate secret number: */
		v[j] = rand() % 255 + 1;
	}
}

Perlin_d::Perlin_d(int _size, int nb_layers)
{
	size = _size;
	freq_init = 2;
	l_random = new Layer(size, 1);
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

}

//double interpolate(int y1, int y2, int n, int delta){
//	if (n!=0)
//		return (double)y1+delta*(y2-y1)/n;
//	else
//		return (double)y1;
//}

int interpolate(int y1, int y2, int n, int delta){
	if (n==0)
	    return y1;
	if (n==1)
	    return y2;
	
	float a = (float)delta/n;
	
	float v1 = 3*pow(1-a, 2) - 2*pow(1-a,3);
	float v2 = 3*pow(a, 2)   - 2*pow(a, 3);
	
	return y1*v1 + y2*v2;
}

double compute_value(int i, int j, int frequence, Layer* l){
	/* déterminations des bornes */
	int borne1x, borne1y, borne2x, borne2y, q;
	float pas;
	pas = (float)l->size/frequence;

	q = (float)i/pas;
	borne1x = q*pas;
	borne2x = (q+1)*pas;

	if(borne2x >= l->size) 
		borne2x = l->size-1;

	q = (float)j/pas;
	borne1y = q*pas;
	borne2y = (q+1)*pas;

	if(borne2y >= l->size) 
		borne2y = l->size-1;

	/* récupérations des valeurs aléatoires aux bornes */
	double b00,b01,b10,b11;
	b00 = l->v[borne1x + l->size*borne1y];
	b01 = l->v[borne1x + l->size*borne2y];
	b10 = l->v[borne2x + l->size*borne1y];
	b11 = l->v[borne2x + l->size*borne2y];

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

double gaussianFunction(double x, double sig)
{
	return exp((-(x*x)/(2.*sig*sig)))/(sig*sqrt(2.*3.14159265));
}


double* gaussianFilter(double* input, int size,  double sig)
{
	int ks = sig*3+1;
	double level = 0;

	double* output = new double[size*size];

	//init
	for(int j=0; j<size*size; j++)
	{
		output[j] = 0;
	}


	for(int j=0; j<size; j++)
	{
		for(int i=0; i<size; i++)
		{
			level=0;
			for(int x=-ks; x<=ks; x++)
			{
				if(i+x >= 0 && i+x < size)
				{
					//level+= (getPixel(inputImg, i+x, j)[0] * gaussianFunction(x, sig));
					level+= (input[i+x + size*j] * gaussianFunction(x, sig));
				}
			}
			output[i+ size*j] = level;
		}
	}

	for(int j=0; j<size; j++)
	{
		for(int i=0; i<size; i++)
		{
			level = 0;
			for(int y=-ks; y<=ks; y++)
			{
				if(j+y >= 0 && j+y < size)
				{
					//r+= (getPixel(tmpImg, i, j+y)[0] * gaussianFunction(y, sig));
					level+= (input[i + size*(j+y)] * gaussianFunction(y, sig));

				}
				output[i+ size*j] = level;
			}
		}
	}

	return output;
}

double* gaussianLand(double* input, int size)
{
	int sig;
	int ks /*sig*3+1*/;
	double level = 0;

	double* temp = new double[size*size];
	double* output = new double[size*size];

	//init
	for(int j=0; j<size*size; j++)
	{
		output[j] = 0;
		temp[j] = 0;
	}


	for(int j=0; j<size; j++)
	{
		for(int i=0; i<size; i++)
		{
			level=0;
			if(input[i + size*j]>170)
			{
				sig = 1;
			}else if (input[i + size*j]>85){
				sig = 3;
			}else{
				sig = 5;
			}
			ks = sig*3+1;
			for(int x=-ks; x<=ks; x++)
			{
				if(i+x >= 0 && i+x < size)
				{
					//level+= (getPixel(inputImg, i+x, j)[0] * gaussianFunction(x, sig));
					level+= (input[i+x + size*j] * gaussianFunction(x, sig));
				}
			}
			temp[i+ size*j] = level;
		}
	}

	for(int j=0; j<size; j++)
	{
		for(int i=0; i<size; i++)
		{
			level = 0;
			if(input[i + size*j]>170)
			{
				sig = 1;
			}else if (input[i + size*j]>85){
				sig = 3;
			}else{
				sig = 5;
			}
			ks = sig*3+1;
			for(int y=-ks; y<=ks; y++)
			{
				if(j+y >= 0 && j+y < size)
				{
					//r+= (getPixel(tmpImg, i, j+y)[0] * gaussianFunction(y, sig));
					level+= (input[i + size*(j+y)] * gaussianFunction(y, sig));

				}
				output[i+ size*j] = (level + temp[i+ size*j])/2;
			}
		}
	}

	return output;
}