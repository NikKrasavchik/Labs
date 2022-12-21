#include <iostream>
#include <cmath>
#include <Windows.h>

using mymath = double(double x);

using namespace std;

int main()
{
    HMODULE Lib = LoadLibraryW(L"Dllfirst.dll");
    mymath* e = (mymath*)GetProcAddress(Lib, "Exponenta");
    mymath* s = (mymath*)GetProcAddress(Lib, "Sin");
    mymath* c = (mymath*)GetProcAddress(Lib, "Cos");
    mymath* t = (mymath*)GetProcAddress(Lib, "Tan");
    mymath* nl = (mymath*)GetProcAddress(Lib, "NLog");
    mymath* as = (mymath*)GetProcAddress(Lib, "ArcSin");
    mymath* at = (mymath*)GetProcAddress(Lib, "ArcTan");

    cout << "Exp:\n";
    for (double x = 0; x < 20; x++)
        cout << e(x) << " " << exp(x) << endl;


    cout << "\nSin:\n";
    for (double x = 0; x < 20; x++)
        cout << s(x) << " " << sin(x) << endl;


    cout << "\nCos:\n";
    for (double x = 0; x < 20; x++)
        cout << c(x) << " " << cos(x) << endl;


    cout << "\nTan:\n";
    for (double x = 0; x < 20; x++)
        cout << t(x) << " " << tan(x) << endl;


    cout << "\nNLog:\n";
    for (double x = 0.1; x < 0.9; x += 0.1)
        cout << nl(x) << " " << log(x) << " " << x << endl;


    cout << "\nArcSin:\n";
    for (double x = -0.9; x < 0.9; x += 0.1)
        cout << as(x) << " " << asin(x) << " " << x << endl;


    cout << "\nArcTan:\n";
    for (double x = -0.9; x < 0.9; x += 0.1)
        cout << at(x) << " " << atan(x) << " " << x << endl;

    FreeLibrary(Lib);
}