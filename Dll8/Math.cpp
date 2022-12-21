#include "Math.h"
#include "pch.h"

double Exponenta(double x)
{
	double Sum = 1;
	int n = 1;
	double t = x;
	while (t > 0.00001)
	{
		n++;
		Sum += t;
		t *= x / n;
	}
	return Sum;
}