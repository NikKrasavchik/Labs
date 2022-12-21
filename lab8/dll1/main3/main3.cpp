#include <iostream>
#include "..\Dllfirst\Math.h"

using namespace std;

int main()
{

    cout << "Exp:\n";
    for (double x = 0; x < 20; x++)
        cout << Exponenta(x) << " " << exp(x) << endl;


    cout << "\nSin:\n";
    for (double x = 0; x < 20; x++)
        cout << Sin(x) << " " << sin(x) << endl;


    cout << "\nCos:\n";
    for (double x = 0; x < 20; x++)
        cout << Cos(x) << " " << cos(x) << endl;


    cout << "\nTan:\n";
    for (double x = 0; x < 20; x++)
        cout << Tan(x) << " " << tan(x) << endl;


    cout << "\nNLog:\n";
    for (double x = 0.1; x < 0.9; x += 0.1)
        cout << NLog(x) << " " << log(x) << " " << x << endl;


    cout << "\nArcSin:\n";
    for (double x = -0.9; x < 0.9; x += 0.1)
        cout << ArcSin(x) << " " << asin(x) << " " << x << endl;


    cout << "\nArcTan:\n";
    for (double x = -0.9; x < 0.9; x += 0.1)
        cout << ArcTan(x) << " " << atan(x) << " " << x << endl;
}