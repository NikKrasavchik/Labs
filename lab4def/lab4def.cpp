#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <locale>

using namespace std;

int main()
{
    setlocale(LC_ALL, "RU");
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
        v[i] = rand() % 10;
    set<int> k(v.begin(), v.end());
    vector<int> y(k.begin(), k.end()), t(y.size());
    for (int i = 0; i < y.size(); i++)
        for (int j = 0; j < v.size(); j++)
            if (v[j] == y[i])
                t[i]++;
    auto it = max_element(begin(t), end(t));

    for (int i = 0; i < t.size(); i++)
        cout << y[i] << " " << t[i] << endl;

    int count = 0;
    int ind = 0;

    for (int i = 0; i < t.size(); i++)
    {
        if (count > 1)
            break;
        if (*it == t[i])
        {
            ind = y[i];
            count++;
        }
    }
    if (count == 1)
        cout << ind;
    else
        cout << "Неть.";
}