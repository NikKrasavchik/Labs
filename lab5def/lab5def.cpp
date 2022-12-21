#include <locale>
#include <iostream>
#include <vector>

using namespace std;

int fill(vector<int>& v, int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        v.push_back(rand() % 100);
        cout << v[i] << " ";
        count += v[i];
    }
    cout << endl;

    return count / v.size();
}

int main()
{
    setlocale(LC_ALL, "RU");
    vector<int> v1, v2;

    int n1, n2;
    cin >> n1;
    int t1 = fill(v1, n1);
    cin >> n2;
    int t2 = fill(v2, n2);
    cout << t1 << " " << t2;
}