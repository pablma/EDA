#include <vector>
#include <iostream>

using namespace std;

void n_reinas(vector<int>& sol, int k, vector<bool> filas, vector<bool> d_asc, vector<bool> d_desc);  
bool es_solucion(vector<int>& sol, int k, vector<bool> filas, vector<bool> d_asc, vector<bool> d_desc);
bool es_completable(vector<int>& sol, int k, vector<bool> filas, vector<bool> d_asc, vector<bool> d_desc);
bool no_ataca(vector<int>& sol, int k, vector<bool> filas, vector<bool> d_asc, vector<bool> d_desc);
int diag_desc(int x, int y); int diag_asc(int x, int y); void procesar_solucion(vector<int>& sol, int k);

int main()
{
	int tam = 4;
	vector<int> prueba(tam);
	vector<bool> filas(tam);
	vector<bool> d_asc(tam);
	vector<bool> d_desc(tam);

	for (int i = 0; i < tam; i++)
		filas[i] = d_asc[i] = d_desc[i] = 0;

	n_reinas(prueba, 0, filas, d_asc, d_desc);

	system("pause");
	return 0;
}

void n_reinas(vector<int>& sol, int k, vector<bool> filas, vector<bool> d_asc, vector<bool> d_desc)
{
	for (int c = 0; c < sol.size(); c++)
	{
		sol[k] = c;

		if (es_solucion(sol, k, filas, d_asc, d_desc))
			procesar_solucion(sol, k);
		else if (es_completable(sol, k, filas, d_asc, d_desc))
		{
			filas[c] = true;
			d_asc[diag_asc(k, c)] = true;
			d_desc[diag_desc(k, c)] = true;
			n_reinas(sol, k + 1, filas, d_asc, d_desc);
			filas[c] = false;
			d_asc[diag_asc(k, c)] = false;
			d_desc[diag_desc(k, c)] = false;
		}
		
	}
}

void procesar_solucion(vector<int>& sol, int k)
{
	for (int i = 0; i < sol.size(); i++)
		cout << sol[i] << " ";
}

int diag_desc(int x, int y)
{
	int num = x - y;
	
	if (num < 0)
		num = -num;

	return num;
}

int diag_asc(int x, int y)
{
	return x + y;
}

bool no_ataca(vector<int>& sol, int k, vector<bool> filas, vector<bool> d_asc, vector<bool> d_desc)
{
	bool b = false;

	if (!filas[k] && !d_asc[diag_asc(k, sol[k])] && !d_desc[diag_desc(k, sol[k])])
		b = true;

	return b;
}

bool es_completable(vector<int>& sol, int k, vector<bool> filas, vector<bool> d_asc, vector<bool> d_desc)
{
	bool b = false;

	if (k < sol.size() && no_ataca(sol, k, filas, d_asc, d_desc))
		b = true;

	return b;
}

bool es_solucion(vector<int>& sol, int k, vector<bool> filas, vector<bool> d_asc, vector<bool> d_desc)
{
	bool b = false;

	if (k == sol.size() - 1 && no_ataca(sol, k, filas, d_asc, d_desc))
		b = true;

	return b;
}
