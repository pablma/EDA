#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <string>


struct DatosJugador
{
	int bonus;
	std::list<int> lista;
};

//FUNCIONES
int maxLosses(std::list<int>& l);
void ganadores(std::map<std::string, DatosJugador> d, int premio);


int main()
{
	int numCasos;
	std::cin >> numCasos;

	std::map<std::string, DatosJugador> jugadores;
	std::string nombre;
	int bonus;
	int numPartidas;
	std::pair<std::string, DatosJugador> p;


	for (int n = 0; n < numCasos; n++)
	{
		int numJugadores;
		int premio;

		std::cin >> numJugadores;
		std::cin >> premio;

		for (int m = 0; m < numJugadores; m++)
		{
			std::getline(std::cin, nombre, ' ');
			std::cin >> bonus;
			std::cin >> numPartidas;
			std::list<int> partidas;

			for (int i = 0; i < numPartidas; i++)
			{
				int puntuacion;
				std::cin >> puntuacion;
				partidas.push_back(puntuacion);
			}

			p.first = nombre;
			p.second.bonus = bonus;
			p.second.lista = partidas;

			jugadores.insert(p);
		}

		ganadores(jugadores, premio);

		jugadores.clear();
	
	}

	system("pause");
	return 0;
}


int maxLosses(std::list<int>& l)
{
	int numMax = 0;
	int num = 0;
	int size = l.size();

	for (int i = 0; i < size; i++)
	{
		int partida = l.front();
		
		if (partida < 5)
			num++;
		else
		{
			if (num > numMax)
			{
				numMax = num;
				num = 0;
			}
		}
		

		l.pop_front();
	}

	if (num > numMax)
		numMax = num;

	return numMax;

}


void ganadores(std::map<std::string, DatosJugador> d, int premio)
{
	auto it = d.begin();
	int n;
	int max;
	std::pair<std::string, DatosJugador> p;
	std::list<std::pair<std::string, DatosJugador>> l;
	int numMax = 0;


	//Saco el mayor número de partidas consecutivas perdidas de cada jugador y meto los datos en un vector
	while (it != d.end())
	{
		max = maxLosses(it->second.lista);	//También se puede hacer it->second->lista
		p.first = (*it).first;
		p.second.bonus = (*it).second.bonus;
		(*it).second.lista.push_back(max);
		p.second.lista = (*it).second.lista;
		
		l.push_back(p);

		//Con esta instrucción ya sabré cuál es el número máximo de derrotas
		if (max > numMax)
			numMax = max;

		++it;
	}


	auto it2 = l.begin();

	while (it2 != l.end())
	{
		if ((*it2).second.lista.front() == numMax)
		{
			std::string player;
			player = (*it2).first;
			int bonus;
			bonus = (*it2).second.bonus;
			bonus += premio;
			(*it2).second.bonus += premio;
			std::cout << player << " " << bonus << std::endl;
		}

		++it2;
	}


}