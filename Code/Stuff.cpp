#include "Stuff.h"

const double pi = 3.14159265;

double gauss_terrain(int x, int y, int size)
{
	double a = (double)(1./size);
	double b = 0.0002;
	double c = (double)(1./size);
	return (size/3)*exp(-(a*pow((float)(x-(size/2)),2) + 2*b*(x-(size/2))*(y-(size/2))+ c*pow((float)(y-(size/2)),2)));
}

double gaussianFunction(double x, double sig)
{
	return exp((-(x*x)/(2.*sig*sig)))/(sig*sqrt(2.*3.14159265));
}

void gaussian2D(double* input, int size, int sig)
{
	int ks = sig*3+1;
	double level = 0;

	double* temp = new double[size*size];
	double* output = new double[size*size];

	int val_end = 0; //valeur pour adapter les bords du terrain a la gaussienne

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
			ks = sig*3+1;
			for(int x=-ks; x<=ks; x++)
			{
				if(i+x < 0)
				{
					val_end = abs(i+x);
				}
				else if(i+x > size)
				{
					val_end = size - (i+x-size);
				}
				else if (i+x == size)
				{
					val_end = size-1;
				}
				else
				{
					val_end = i+x;
				}

				level+= (input[val_end + size*j] * gaussianFunction(x, sig));
			}
			temp[i+ size*j] = level;
		}
	}

	for(int j=0; j<size; j++)
	{
		for(int i=0; i<size; i++)
		{
			level = 0;
			ks = sig*3+1;
			for(int y=-ks; y<=ks; y++)
			{
				if(j+y > size)
				{
					val_end = size - (j+y-size);
				}
				else if(j+y < 0)
				{
					val_end = abs(j+y);
				}
				else if(j+y >= 0 && j+y < size)
				{
					val_end = j+y;
				}

				level+= (temp[i + size*(val_end)] * gaussianFunction(y, sig));

				output[i+ size*j] = level;
			}
		}
	}

	for(int i=0; i<size*size; i++)
	{
		input[i] = output[i];
	}

	delete[] temp;
	delete[] output;
}


double interpolation_cos1D(double a, double b, double x)
{
   double k = (1 - cos(x * pi)) / 2;
    return a * (1 - k) + b * k;
}

double interpolation_cos2D(double a, double b, double c, double d, double x, double y) 
{
   double y1 = interpolation_cos1D(a, b, x);
   double y2 = interpolation_cos1D(c, d, x);
   return  interpolation_cos1D(y1, y2, y);
}