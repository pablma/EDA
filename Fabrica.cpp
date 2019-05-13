#include <iostream>
#include <vector>


void vuelta_atras(std::vector<std::vector<int>> sueldosEmpleados, std::vector<int>& sol, std::vector<bool>& filasVisitadas, int k, int& total, int& mejorPrecio);
bool es_solucion(std::vector<int>& sol, int k, int total, int mejorCantidad);
void actualiza_solucion(int total, int& mejorCantidad);
bool es_completable(std::vector<int>& sol, int k);
bool trabajan_todos(std::vector<int>& sol, int k);


int main()
{
	int numEmpleados = 0;
	std::cin >> numEmpleados;
	int sueldo;

	while (numEmpleados != 0)
	{
		std::vector<std::vector<int>> sueldosEmpleados(numEmpleados, std::vector<int>(numEmpleados));
		
		for (int i = 0; i < numEmpleados; i++)
		{
			for (int j = 0; j < numEmpleados; j++)
			{
				std::cin >> sueldo;
				sueldosEmpleados[i][j] = sueldo;
			}
		}

		std::vector<int> sol(numEmpleados);
		std::vector<bool> filasVis(numEmpleados);
		int mejorPrecio = 10000;	//Empiezo con un valor de precio muy muy alto para que alguna solución del backtracking sea mejor
		int total = 0;

		vuelta_atras(sueldosEmpleados, sol, filasVis, 0, total, mejorPrecio);

		if (mejorPrecio != 10000)
			std::cout << mejorPrecio << std::endl;
		else
			std::cout << "FESTIVO" << std::endl;
		
		std::cin >> numEmpleados;
	}
	

	system("pause");
	return 0;
}

//Esta función está en O(n^n) siendo n la longitud del vector sol
void vuelta_atras(std::vector<std::vector<int>> sueldosEmpleados, std::vector<int>& sol, std::vector<bool>& filasVisitadas, int k, int& total, int& mejorPrecio)
{	
	for (int j = 0; j < sueldosEmpleados.size(); j++)
	{
		if (!filasVisitadas[j])
		{
			sol[k] = sueldosEmpleados[k][j];
			total += sol[k];

			if (es_solucion(sol, k, total, mejorPrecio))
				actualiza_solucion(total, mejorPrecio);
			else if (es_completable(sol, k))
			{
				filasVisitadas[j] = true;	//Marco fila
				vuelta_atras(sueldosEmpleados, sol, filasVisitadas, k + 1, total, mejorPrecio);
				filasVisitadas[j] = false;	//Desmarco fila
			}

			total -= sol[k];
		}
	}
}


//Esta función está en O(n), siendo n la longitud del vector solución según se va rellenando
bool es_completable(std::vector<int>& sol, int k)
{
	bool b = false;

	if (k < sol.size() - 1 && trabajan_todos(sol, k))
		b = true;

	return b;
}


//Esta función está en O(n), siendo n la longitud del vector solución según se va rellenando
bool trabajan_todos(std::vector<int>& sol, int k)
{
	bool b = true;
	int i = 0;

	while (i <= k && b)	//Es <= porque empezamos rellenando en sol[0], si no es así, en algún momento cascará
	{
		if (sol[i] == 0)
			b = false;
		i++;
	}

	return b;
}

//Coste O(1)
bool es_solucion(std::vector<int>& sol, int k, int total, int mejorCantidad)
{
	bool b = false;

	if ((k == sol.size() - 1) && (total < mejorCantidad))
		b = true;
	else
		b = false;

	return b;
}


//Coste O(1)
void actualiza_solucion(int total, int& mejorCantidad)
{
	mejorCantidad = total;
}