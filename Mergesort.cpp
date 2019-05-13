#include<vector>
#include<iostream>

using namespace std;

template <class T>
void mergesort(vector<T>& v, int ini, int fin); 
template <class T>
void merge(vector<T>& v, int ini, int mit, int fin); 


int main()
{
	int numCasos;
	int tam;
	
	cin >> numCasos;

	for (int i = 0; i < numCasos; i++)
	{
		cin >> tam;
		vector<int> v(tam);
		for (int j = 0; j < v.size(); j++)
		{
			cin >> v[j];
		}
		mergesort(v, 0, v.size());
		for (int k = 0; k < v.size(); k++)
			cout << v[k] << " ";
		cout << endl;

	}


	return 0;
}

template <class T>
void mergesort(vector<T>& v, int ini, int fin)
{
	if (ini < fin - 1)	//El vector tiene más de un elto
	{
		int mit = (ini + fin) / 2;
		mergesort(v, ini, mit);	//Me divide el vector desde el ppo hasta el final
		mergesort(v, mit, fin); //Me divide el vector desde la mitad hasta el final
		merge(v, ini, mit, fin);
		
	}
}

template <class T>
void merge(vector<T>& v, int ini, int mit, int fin)
{

	int eltos_ini_mit = mit - ini;
	int eltos_mit_fin = fin - mit;

	vector<T> v1(eltos_ini_mit);
	vector<T> v2(eltos_mit_fin);

	for (int i = 0; i < v1.size(); i++)
	{
		v1[i] = v[ini + i];
	}
	for (int j = 0; j < v2.size(); j++)
	{
		v2[j] = v[mit + j];
	}

	int i, j;
	i = j = 0;


	for (int k = ini; k < fin; k++)
	{
		if (j >= eltos_mit_fin || (i < eltos_ini_mit && v1[i] <= v2[j]))
		{
			v[k] = v1[i];
			i++;
		}
		else
		{
			v[k] = v2[j];
			j++;
		}
	}

}

