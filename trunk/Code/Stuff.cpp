#include "Stuff.h"

const double pi = 3.14159265;

double gauss_terrain(int x, int y, int size)
{
	double a = (double)(1./size);
	double b = 0.0002;
	double c = (double)(1./size);
	return (size/3)*exp(-(a*pow((float)(x-(size/2)),2) + 2*b*(x-(size/2))*(y-(size/2))+ c*pow((float)(y-(size/2)),2)));
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