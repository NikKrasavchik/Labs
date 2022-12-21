#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>


using namespace std;

int main()
{
	ofstream fl("data.dat", ios::binary);
	int a[] = { 10,20,30,40,50 };
	fl.write((char*)&a, sizeof a);

	fl.close();

	fstream fl1("data.dat", ios::in | ios::out | ios::binary);
	int b;
	while (true)
	{
		fl1.read((char*)&b, sizeof(int));
		if (fl1.eof())
			break;
	}
	fl1.clear();
	fl1.seekp(0, ios::beg);

	int c = 60;
	fl1.write((char*)&c, sizeof c);


	fl1.seekp(0, ios::beg);


	while (true)
	{
		fl1.read((char*)&b, sizeof(int));
		if (fl1.eof())
		{
			cout << b << endl;
			break;
		}
	}


	fl1.close();

	cout << b << endl;

	system("pause");
}