#include <iostream>
#include <set>
#include <queue>
#include <string>


//FUNCIONES
bool comprueba_cocina_entrada(std::set<std::string>& set, std::string s);
bool comprueba_cocina_salida(std::set<std::string>& set, std::string s);


int main()
{
	std::set<std::string> lista;
	lista = std::set<std::string>();


	int numEntradas, numSalidas;
	std::cin >> numEntradas;
	std::cin >> numSalidas;

	do 
	{
		std::queue<std::pair<int, std::string>> entradas;
		std::queue<std::pair<int, std::string>> salidas;

		for (int i = 0; i < numEntradas; i++)
		{
			int tiempo;
			std::cin >> tiempo;
			std::string nombre;
			std::getline(std::cin, nombre);

			std::pair<int, std::string> p;
			p.first = tiempo;
			p.second = nombre;

			entradas.push(p);
		}

		for (int j = 0; j < numSalidas; j++)
		{
			int tiempo;
			std::cin >> tiempo;
			std::string nombre;
			std::getline(std::cin, nombre);

			std::pair<int, std::string> p;
			p.first = tiempo;
			p.second = nombre;

			salidas.push(p);
		}
		
		int personas;
		int maxPersonas = 0;
		bool error = false;

		while (!error && (!entradas.empty() || !salidas.empty()))
		{

			int tiempoEntradas;
			int tiempoSalidas;

			if (!entradas.empty())
				tiempoEntradas = entradas.front().first;
			if (!salidas.empty())
				tiempoSalidas = salidas.front().first;

			if (!entradas.empty() && (salidas.empty() || tiempoEntradas < tiempoSalidas))
			{
				if (comprueba_cocina_entrada(lista, entradas.front().second))
				{
					personas = lista.size();
					if (personas > maxPersonas)
						maxPersonas = personas;
					entradas.pop();
				}
				else
					error = true;
			}
			else if (!salidas.empty())
			{
				if (comprueba_cocina_salida(lista, salidas.front().second))
					salidas.pop();
				else
					error = true;
			}

		
		}

		if (error)
			std::cout << "ERROR" << std::endl;
		else
			std::cout << maxPersonas << std::endl;

		lista.clear();

		std::cin >> numEntradas;
		std::cin >> numSalidas;


	} while (numEntradas != -1 && numSalidas != -1);

	return 0;
}


//Comprueba que si el valor no estaba, lo insertamos
//Esta función tiene un coste en O(n), siendo n la distancia desde el primer elemento del conjunto hasta el solicitado
bool comprueba_cocina_entrada(std::set<std::string>& set, std::string s)
{
	bool b = true;

	if (set.find(s) == set.end())	//El valor no estaba ya en el conjunto
		set.insert(s);
	else
		b = false;

	return b;
}


//Comprueba que si el valor estaba en la cocina lo eliminamos
//Esta función tiene un coste en O(n), siendo n la distancia desde el primer elemento del conjunto hasta el solicitado
bool comprueba_cocina_salida(std::set<std::string>& set, std::string s)
{
	bool b = true;

	if (set.find(s) != set.end())	//Si el elto está lo eliminamos
		set.erase(s);
	else
		b = false;

	return b;
}