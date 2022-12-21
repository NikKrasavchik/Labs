#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <bitset>
#include <locale>

#pragma warning(disable: 4996)

#define CP
#define BINARY

using namespace std;

int main()
{
#ifndef CP
    setlocale(LC_ALL, "RU");
    srand(time(NULL));
    FILE* in;
#ifndef BINARY
        fopen_s(&in, "data.dat", "wt");
#endif
#ifdef BINARY
    fopen_s(&in, "data.dat", "wb");
#endif
    char naming[10][256] = { "Первая", "Вторая", "Третья", "Четвёртая", "Пятая", "Шестая", "Седьмая", "Восьмая", "Девятая", "Десятая" };
    for (int i = 0; i < 10; i++) 
    {
        fprintf(in, "%s строка:", naming[i]);
        for (int j = 0; j < 10; j++)
            fprintf(in, " a%i%i->%i", i+1, j+1, (rand()%100));

        fprintf(in, "\n");
    }
    fclose(in);

#ifndef BINARY
    fopen_s(&in, "data.dat", "rt");
#endif
#ifdef BINARY
    fopen_s(&in, "data.dat", "rb");
#endif
    int nums[10][10];
    char st[256];
    int j = 0;
    int ind = 0;
    while (fgets(st, sizeof st, in) != 0)
    {
        int i = 0;
        int jn = 0;
        printf("%s", st);

        
        char* pch = strtok(st, " >");

        while (pch != NULL)
        {
            if (i > 2 && (i % 2 == 1))
            {
                nums[ind][jn] = atoi(pch);
                jn += 1;
            }
            pch = strtok(NULL, " >");
            i++;
        }
        cout << endl;
        j++;
        ind += 1;
    }
    fclose(in);


    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            if (10 - j - 1 == i)
                nums[i][9] = nums[i][j] * nums[0][j];


#ifndef BINARY
    fopen_s(&in, "result.res", "wt");
#endif
#ifdef BINARY
    fopen_s(&in, "result.res", "wb");
#endif

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
#ifdef BINARY
            fwrite(&nums[i][j], sizeof(int), 1, in);
#endif
#ifndef BINARY
            fprintf(in, "A%i%i ", i, j);
        fprintf(in, "\n");
        for (int j = 0; j < 10; j++)
            fprintf(in, "%i* ", nums[i][j]);
        fprintf(in, "\n");
#endif
    }

    fclose(in);

#endif
#ifdef CP
    setlocale(LC_ALL, "RU");
    ofstream fout;

#ifdef BINARY
    fout.open("data.dat", ios::out | ios::binary);
#endif
#ifndef BINARY
    fout.open("data.dat");
#endif

    vector<string> naming = { "Первая", "Вторая", "Третья", "Четвёртая", "Пятая", "Шестая", "Седьмая", "Восьмая", "Девятая", "Десятая" };

    for (int i = 0; i < 10; i++)
    {
        string st = naming[i] + " строка: ";
        for (int j = 0; j < 10; j++)
        {
            st += "a" + to_string(i+1) + to_string(j+1) + "-> " + to_string(rand() % 100) + " ";
        }
        st += '\n';
        fout << st;
    }
    fout.close();

    ifstream fin;
#ifdef BINARY
     fin.open("data.dat", ios::in | ios::binary);
#endif
#ifndef BINARY
    fin.open("data.dat");
#endif

    int count = 0, j = 0, i = 0;
    vector<vector<int>> nums(10);

    while (!fin.eof())
    {
        string st;
        fin >> st;
        

        if (count > 2 && (count % 2 == 1))
        {
            nums[j].push_back(stoi(st));
            i++;
        }
        count++;
        if (count > 21)
        {
            count = 0;
            i = 0;
            j++;
        }
    }

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            if (10 - j - 1 == i)
                nums[i][9] = nums[i][j] * nums[0][j];
    fin.close();

    ofstream fout2;
#ifdef BINARY
    fout2.open("result.res", ios::out | ios::binary);
#endif
#ifndef BINARY
    fout2.open("result.res");
#endif

    for (int i = 0; i < 10; i++)
    {
        string st = "";
        for (int k = 0; k < 10; k++)
            st += "A" + to_string(i + 1) + to_string(k + 1) + " ";
        st += '\n';
        for (int k = 0; k < 10; k++)
            st += to_string(nums[i][k]) + "* ";
#ifdef BINARY
        fout2.write((char*)&st, sizeof st);
#endif
#ifndef BINARY
        fout2 << st << endl;
#endif
    }
    fout2.close();
#endif
}