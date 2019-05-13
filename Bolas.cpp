#include <iostream>
#include <vector>


//FUNCIONES
void distribuye_cajas(int ini, int fin); 
//void rellena_cajas(std::vector<int>& cajas, int ini, int fin);
void rellena_cajas();


int numViajes = 0;


int main()
{
	int numCajas;
	
	std::cin >> numCajas;
	distribuye_cajas(0, numCajas);
	
	std::cout << numViajes << std::endl;

	return 0;
}


//El coste de esta función es O(n.log n) siendo n la longitud del vector - 1
void distribuye_cajas(int ini, int fin)
{
	if (fin - ini <= 2)
		numViajes = fin - ini;
	else if (ini < fin - 1)
	{
		int mid = (ini + fin) / 2;
		distribuye_cajas(mid, fin);
		distribuye_cajas(ini, mid);
		rellena_cajas();
	}
}


//El coste de sta función es O(1) siendo n la longitud comprendida entre ini y fin
//void rellena_cajas(std::vector<int>& cajas, int ini, int fin)
//{
//	int numBolas = ini + 1;
//
//	for (int i = ini; i < fin; i++)
//	{
//		if (cajas[i] + numBolas <= i + 1)
//			cajas[i] += numBolas;
//	}
//	
//	numViajes++;
//}


void rellena_cajas()
{
	numViajes++;
}