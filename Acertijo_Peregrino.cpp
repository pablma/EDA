#include <iostream>


//FUNCIONES
void vuelta_atras(int& num, int k, int numGrupos, int& numDivisores, bool& encontrada, bool& completable);
bool es_solucion(int numGrupos, int numDivisores);
void procesa_solucion(int num);
bool es_completable(int num, int k, int numGrupos, int numDivisores);


int main()
{
	int numGrupos;
	std::cin >> numGrupos;
	int numDivisores = 0;
	bool encontrada = false;
	bool completable = true;
	int numIni = numGrupos + 1;

	vuelta_atras(numIni, 1, numGrupos, numDivisores, encontrada, completable);
	
	if (!encontrada)
		std::cout << "+INF" << std::endl;


	system("pause");
	return 0;
}


void vuelta_atras(int& num, int k, int numGrupos, int& numDivisores, bool& encontrada, bool& completable)
{	

	while (!encontrada && completable)
	{
		if (num % k == 0)
			numDivisores++;

		if (es_solucion(numGrupos, numDivisores))
		{
			procesa_solucion(num);
			encontrada = true;
		}
		else if (es_completable(num, k, numGrupos, numDivisores))
		{
			vuelta_atras(num, k + 1, numGrupos, numDivisores, encontrada, completable);		
			
			if(numDivisores > 0)
				numDivisores--;
		}
		else
		{
			completable = false;
			num++;
		}

		if (numDivisores == 0 && k == 1)
			completable = true;

	}

}


bool es_completable(int num, int k, int numGrupos, int numDivisores)
{
	if (num > numGrupos && k < num && numDivisores < numGrupos)
		return true;
	else
		return false;
}


bool es_solucion(int numGrupos, int numDivisores)
{
	if (numDivisores == numGrupos)
		return true;
	else 
		return false;
}


void procesa_solucion(int num)
{
	std::cout << num << std::endl;
}