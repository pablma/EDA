#include <iostream>
#include <vector>


//FUNCIONES
void divide_vector(std::vector<int>& v, int& pico, int ini, int fin, bool& encontrado);
void es_pico(std::vector<int>& v, int& pico, int ini, int mid, int fin, bool& encontrado);


int main()
{
	int pico = 0;
	std::vector<int> vec;
	int tam;
	bool encontrado = false;

	std::cin >> tam;
	for (int i = 0; i < tam; i++)
	{
		int n;
		std::cin >> n;
		vec.push_back(n);
	}

	divide_vector(vec, pico, 0, vec.size(), encontrado);

	std::cout << "Pico: " << pico << std::endl;

	system("pause");
	return 0;
}


//El coste de esta función es O(logn) siendo n el número de elementos desde ini hasta fin
void divide_vector(std::vector<int>& v, int& pico, int ini, int fin, bool& encontrado)
{
	if (ini < fin - 2)
	{
		int mid = (ini + fin) / 2;
		divide_vector(v, pico, ini, mid, encontrado);
		divide_vector(v, pico, mid, fin, encontrado);
		if(!encontrado)
			es_pico(v, pico, ini, mid, fin, encontrado);
	}
	else if (v.size() == 1)
		pico = v[0];
}


//El coste de esta función es O(1)
void es_pico(std::vector<int>& v, int& pico, int ini, int mid, int fin, bool& encontrado)
{

	if (mid < v.size())
	{
		if (v[mid - 1] >= v[mid])
		{
			pico = v[mid - 1];
			//Solución inmediata (extremo izqdo)
			if (mid - 1 == 0)
				encontrado = true;
		}			
		else
		{
			pico = v[mid];
			//Solución inmediata (extremo dcho)
			if (mid == v.size() - 1)
				encontrado = true;
		}	
	}	
}


//void es_pico(std::vector<int>& v, int& pico, int ini, int mid, int fin, bool& encontrado)
//{
//	if (v[mid] >= v[mid - 1])
//	{
//		if (v[mid] >= v[mid + 1])
//			pico = v[mid];
//		else
//			pico = v[mid + 1];
//	}
//	else
//		pico = v[mid - 1];
//		
//	if ((mid - 1) == 0 || (mid + 1) == v.size())
//		encontrado = true;
//
//}