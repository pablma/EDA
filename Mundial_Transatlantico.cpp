#include <queue>
#include <vector>
#include <iostream>


int ultimo_al_agua(std::vector<bool> balones, int fallo);


int main()
{
	int numBalones, tirosHastaFallo;
	int ultBalon;

	std::cin >> numBalones;
	std::cin >> tirosHastaFallo;

	while (numBalones != 0 && tirosHastaFallo != 0)
	{
		std::vector<bool> balones(numBalones);
		ultBalon = ultimo_al_agua(balones, tirosHastaFallo);
		std::cout << ultBalon << std::endl;
		std::cin >> numBalones;
		std::cin >> tirosHastaFallo;
	}

	return 0;
}


//El coste de esta función es O(n) siendo n el tamaño de balones
int ultimo_al_agua(std::vector<bool> balones, int fallo)
{
	std::queue<int> balones_al_agua;
	int i = 0;
	int tiros = 0;

	while (balones_al_agua.size() != balones.size())
	{
		if (!balones[i])
			tiros++;

		if(tiros == fallo)
		{
			tiros = 0;
			balones[i] = true;
			balones_al_agua.push(i + 1);
		}

		i++;

		if (i >= balones.size())
			i = 0;
	}
	
	return balones_al_agua.back();
}