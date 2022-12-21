#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

void f1(float N, float A, float B, float C)
{
    float Volume = N * A * B * C;
    cout << "Суммарный объём = " << fixed << setprecision(3) << Volume;
}

void f2(float& x, float& y)
{
	float R = sqrt(x * x + y * y);
	int res = 0;

	if (x > 0)
	{
		if (y > 0)
		{
			if (R > 2)
			{
				if (y < sqrt(x)) res = 1;
				else res = 2;
			}
			else
			{
				if (y > -1 * (x - 1) * (x - 1) * (x - 1))
				{
					if (y < sqrt(x)) res = 11;
					else res = 12;
				}
				else
				{
					if (y < sqrt(x)) res = 18;
					else res = 19;
				}
			}
		}
		else if (!y and (x == 1 or x == 2))
		{
			if (x == 1) res = 18;
			else if (x == 2) res = 11;
		}
		else
		{
			if (R > 2)
			{
				if (y >= -1 * (x - 1) * (x - 1) * (x - 1)) res = 9;
				else
				{
					if (y >= -x - 1) res = 8;
					else res = 7;
				}
			}
			else
			{
				if (y > -1 * (x - 1) * (x - 1) * (x - 1)) res = 10;
				else
				{
					if (y >= -x - 1) res = 17;
					else res = 16;
				}
			}
		}
	}
	else if (!x and (!y or y == -2))
	{
		if (!y) res = 24;
		else if (y == -2) res = 16;
	}
	else
	{
		if (y > 0)
		{
			if (R > 2)
			{
				if (y > -1 * (x - 1) * (x - 1) * (x - 1)) res = 3;
				else
				{
					if (y > -x - 1) res = 4;
					else res = 5;
				}
			}
			else
			{
				if (y >= -1 * (x - 1) * (x - 1) * (x - 1)) res = 23;
				else
				{
					if (y > -x - 1)
					{
						if (y * y > 0.25 - (x + 0.5) * (x + 0.5)) res = 13;
						else res = 20;
					}
					else res = 14;
				}
			}
		}
		else
		{
			if (R > 2)
			{
				if (x == 0) res = 7;
				else res = 6;
			}
			else
			{
				if (y * y <= 0.25 - (x + 0.5) * (x + 0.5))
				{
					if (y > -x - 1) res = 21;
					else res = 22;
				}
				else
				{
					if (y < -x - 1) res = 15;
					else res = 24;
				}
				if (x == -0.5 && y == -0.5) res = 24;
			}
		}
	}
	cout << "Зона номер: " << res << endl;
}

string f3()
{
	float x;
	cout << "Введите значение аргумента функции:";
	cin >> x;
	double Sum = 0, eps = 0.0001f;
	int n = 1;
	int sign = 1;
	while (true)
	{
		double q = sign * pow(x, n) / n;
		Sum += q;
		n += 2;
		sign = -sign;
		if (q < eps)
			break;
	}
	string st = "\nСумма ряда= " + to_string(Sum) + "; Значение ATAN(X) = " + to_string(atan(x)) + ";\n";
	return st;
}

//#define D1
//#define D2
#define D3
int main()
{
	setlocale(LC_ALL, "RUS");

	while (true)
	{
#ifdef D1
		float A, B, C, N;
		cout << "Введите количество N:" << endl;
		cin >> N;
		printf("Введите А, B, C в одну строчку через пробел:\n");
		cin >> A >> B >> C;
		f1(N, A, B, C);
		cout << endl;
#endif
#ifdef D2
		float x, y;
		cout << "Введите координаты x и y: ";
		cin >> x >> y;
		f2(x, y);
		cout << endl;
		cout << x;
#endif
#ifdef D3

		string st = f3();
		cout << st << endl;
#endif
	}
}


