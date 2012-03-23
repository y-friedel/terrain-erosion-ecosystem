class gVector {
protected:
	double c[3];
public:
	gVector() {}
	gVector(const double& x, const double& y, const double& z)
	{
		c[0] = x;
		c[1] = y;
		c[2] = z;
	}
	gVector(const gVector& v)
	{
		c[0] = v[0];
		c[1] = v[1];
		c[2] = v[2];
	}

	double operator[] (int i) const;

};