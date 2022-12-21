#include "pch.h"
#include <cmath>



extern "C" __declspec(dllexport) double Exponenta(double x)
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

extern "C" __declspec(dllexport) double Sin(double x)
{
	double n = x;
	double sum = 0.0;
	int i = 1;

	do
	{
		sum += n;
		n *= -1.0 * x * x / ((2 * i) * (2 * i + 1));
		i++;
	} while (fabs(n) > 0.000000001);

	return sum;
}

extern "C" __declspec(dllexport) double Cos(double x)
{
	double n = 1.0;
	double sum = 0.0;
	int i = 1;

	do
	{
		sum += n;
		n *= -1.0 * x * x / ((2 * i - 1) * (2 * i));
		i++;
	} while (fabs(n) > 0.000000001);

	return sum;
}

extern "C" __declspec(dllexport) double Tan(double x)
{
	return Sin(x)/Cos(x);
}


extern "C" __declspec(dllexport) double NLog(double x)
{
	double sum = 0;
	int n = 1;
	int sign = 1;
	while (true)
	{
		double q = sign*(pow(x-1, n))/n;
		sum += q;
		sign *= -1;
		n += 1;
		if (fabs(q) < 0.000000001)
			break;
	}
	return sum;
}

long double fact(int N)
{
	if (N < 0)
		return 0;
	if (N == 0)
		return 1;
	else
		return N * fact(N - 1);
}

extern "C" __declspec(dllexport) double ArcSin(double x)
{
	double sum = 0;
	int n = 0;
	while (true)
	{
		double q = fact(2 * n) / (pow(4, n) * pow(fact(n), 2) * (2 * n + 1)) * pow(x, 2 * n + 1);
		sum += q;
		n += 1;
		if (fabs(q) < 0.000000001)
			break;
	}
	return sum;
}

extern "C" __declspec(dllexport) double ArcTan(double x)
{
	double sum = 0;
	int n = 0;
	while (true)
	{
		double q = pow(-1, n) * (pow(x, 2*n+1)) / (2*n+1);
		sum += q;
		n += 1;
		if (fabs(q) < 0.000000001)
			break;
	}
	return sum;
}
