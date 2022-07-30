#include <iostream>
#include <ctime>
#include <windows.h>


using namespace std;

class Cube
{
private:
	int facets; // количество граней	
	int ort_facets; //количества элементов вектора ort

	double* ver;//вектор вероятностей
	double* ort;//вектор
	int* pract;//вектор вероятностей полученных в результате эксперимента



public:
	Cube(int f)
	{
		facets = f;
		double p, sum;
		p = 1.0 / facets;
		sum = 0;
		ver = new double[facets];
		ort = new double[facets];

		for (int i = 0; i < facets; i++)
		{
			ver[i] = p;
		}

		ort_facets = facets + 1;
		ort = new double[ort_facets];
		ort[0] = 0;
		for (int i = 1; i < ort_facets; i++)
		{
			ort[i] = ort[i - 1] + ver[i - 1];
		}

	}


	Cube(int f, int edge, double probability)
	{

		double prob;
		facets = f;


		ver = new double[facets];
		prob = 1 - probability;


		for (int i = 0; i < facets; i++)
		{

			ver[i] = prob / (facets - 1);



		}

		ver[edge - 1] = probability;
		ort_facets = facets + 1;
		ort = new double[ort_facets];
		ort[0] = 0;
		for (int i = 1; i < ort_facets; i++)
		{
			ort[i] = ort[i - 1] + ver[i - 1];
		}
	}



	Cube(Cube& kop) {
		facets = kop.facets;
		ver = new double[facets];
		ort = new double[facets];
		for (int i = 0; i < facets; i++) {
			ort[i] = kop.ort[i];
			ver[i] = kop.ver[i];
		}
	}


	int Play()
	{
		double r;
		r = (double)(rand()) / RAND_MAX;
		for (int i = 0; i < ort_facets; i++)
		{
			if (ort[i] >= r)
			{


				return i;
			}

		}
		return -1;
	}




	void Start(int n)
	{

		int x;
		srand(time(0));


		pract = new int[facets]();
		for (int i = 0; i < facets; i++)
		{
			pract[i] = 0;
		}
		for (int i = 0; i < n; i++)
		{
			x = Play();
			pract[x - 1]++;
		}

	}





void Print() {
	cout << fixed;
	cout.precision(3);
	cout << "Кубик с " << facets << " гранями подкинули " << 1000 << " раз" << endl << endl;
	cout << "   Грань  |" << "Теор.вероятость|" << "Выпала раз грань|" << "  Практ.вероятность" << endl;
	for (int i = 0; i < facets; i++)
		cout << "      " << i + 1 << "   |\t" << ver[i] << "\t  |\t " << pract[i] << "\t   |\t " << (double)pract[i] / 1000 << " " << endl;
}
};



int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Cube green(8);

	green.Start(1000);
	green.Print();

	Cube yellow(8, 8, 0.4);

	yellow.Start(1000);
	yellow.Print();

	getchar();

}
