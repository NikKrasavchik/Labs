#include <iostream>
#include <locale>
#include <iomanip>

using namespace std;

int f(int* m, int n)
{
    int sum = 0;
    for (auto i = 0; i < n; i++) sum += m[i];
    return sum / n;
}

int main()
{
    setlocale(LC_ALL, "RU");

    int n;
    cin >> n;
    int** matrix = new int* [n];
    for (int i = 0; i < n; i++)
    {
        matrix[i] = new int[n];
        for (int j = 0; j < n; j++) matrix[i][j] = rand() % 100;
    }

    cout << endl << setw(4);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++) cout << matrix[i][j] << setw(4);
        cout << "|" << setw(4) << f(matrix[i], n) << setw(4) << endl;
    }
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (i == j) if (f(matrix[i], n) < matrix[i][j]) matrix[i][j] = 0;

    cout << endl << setw(4);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++) cout << matrix[i][j] << setw(4);
        cout << endl;
    }
}