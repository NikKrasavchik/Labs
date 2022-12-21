#include <iostream>
#include "..\include\Header.h"
#include <cmath>


using namespace std;

int main()
{
    for (double x = 0; x < 20; x++)
        cout << Exponenta(x) << " " << exp(x) << endl;
}