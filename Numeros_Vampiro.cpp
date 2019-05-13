#include <iostream>
#include <string>
#include <vector>


//FUNCIONES
void numVampiro(std::vector<int>& sol, int k, int vamp, bool& encontrado);
bool es_solucion(std::vector<int>& sol, int vamp);
bool es_completable(std::vector<int>& sol, int k, int vamp);
void procesa_solucion();
bool longPar(int num);
bool mismosDigitos(int num, int vamp);
bool noAcabanEn_0(std::vector<int>& sol);
bool mitadDeDigitos(int num, int vamp);


int main()
{
	int vamp;
	int numCasos;
	std::cin >> numCasos;
	bool vamp_encontrado = false;

	std::vector<int> sol(2);
	sol[0] = 1;
	sol[1] = 1;

	for (int i = 0; i < numCasos; i++)
	{
		std::cin >> vamp;
		numVampiro(sol, 0, vamp, vamp_encontrado);
		if (!vamp_encontrado)
			std::cout << "NO" << std::endl;
		vamp_encontrado = false;
	}

	system("pause");
	return 0;
}


void numVampiro(std::vector<int>& sol, int k, int vamp, bool& encontrado)
{	
	std::string v = std::to_string(vamp);
	if (longPar(vamp))
	{
		int i = 0;
		while (i < vamp && !encontrado)
		{
			std::string n = std::to_string(i);
			if (n.size() == v.size() / 2 && mismosDigitos(i, vamp))
			{
				sol[k] = i;
				if (es_solucion(sol, vamp))
				{
					procesa_solucion();
					encontrado = true;
				}
				else if (es_completable(sol, k, vamp))
					numVampiro(sol, k + 1, vamp, encontrado);
			}		
			i++;
		}
	}
	else
		encontrado = false;
	
}


//El coste de esta función es O(n^2)
bool es_completable(std::vector<int>& sol, int k, int vamp)
{
	bool b;

	if (k < 1 && noAcabanEn_0(sol) && mismosDigitos(sol[0], vamp))
		b = true;
	else
		b = false;

	return b;
}


//El coste de esta función es O(1)
bool es_solucion(std::vector<int>& sol, int vamp)
{
	return /*(mitadDeDigitos(sol[1], vamp)) && (mismosDigitos(sol[1], vamp)) &&*/ (sol[0] * sol[1] == vamp);
}


//El coste de esta función es O(1)
void procesa_solucion()
{
	std::cout << "SI" << std::endl;
}


//El coste de esta función es O(1)
bool longPar(int num)
{
	std::string n = std::to_string(num);
	return n.size() % 2 == 0;
}


//El coste de esta función es O(n^2)
bool mismosDigitos(int num, int vamp)
{
	std::string v = std::to_string(vamp);
	std::string n = std::to_string(num);

	std::vector<bool> marcado(n.size());
	int cont = 0;
	bool encontrado = false;
	bool posible = true;

	int i, j;
	i = j = 0;

	while (i < n.size() && posible)
	{
		j = 0;
		while (j < v.size())
		{
			if (n[i] == v[j] && !marcado[i])
			{
				cont++;
				marcado[i] = true;
			}
			j++;
		}

		if (cont == 0)
			posible = false;

		i++;
	}

	return cont == v.size() / 2;
}


//El coste de esta función O(1)
bool noAcabanEn_0(std::vector<int>& sol)
{
	std::string n1 = std::to_string(sol[0]);
	std::string n2 = std::to_string(sol[1]);
	bool b;

	if (n1[n1.size() - 1] == 0 && n2[n2.size() - 1] == 0)
		b = false;
	else
		b = true;

	return b;
	//return (n1[n1.size() - 1] == 0 && n2[n2.size() - 1] != 0) || (n1[n1.size() - 1] != 0 && n2[n2.size() - 1] == 0) || (n1[n1.size() - 1] != 0 && n2[n2.size() - 1] != 0);
}


//El coste de esta función es O(1)
bool mitadDeDigitos(int num, int vamp)
{
	std::string n1 = std::to_string(num);
	std::string v = std::to_string(vamp);

	return (n1.size() == v.size() / 2);
}