#include <iostream>
#include <string>
#include <vector>


//FUNCIONES
void divide_vector(std::vector<std::string>& v, int ini, int fin);
void pref_comun(std::vector<std::string>& v, int ini, int fin);


std::string pref;	//Almacena el prefijo común entre dos palabras concretas
std::string prefComun;	//Almacena el prefijo que hay anteriormente en pref


int main()
{
	std::string pal1 = "abrir";
	std::string pal2 = "cueva";
	std::string pal3 = "casa";

	std::vector<std::string> palabras;
	palabras.push_back(pal1);
	palabras.push_back(pal2);
	palabras.push_back(pal3);

	divide_vector(palabras, 0, palabras.size());

	std::cout << pref << std::endl;

	system("pause");
	return 0;
}


//Esta función está en O(nm), siendo n el tamaño del vector y m tamaño de la palabra más larga
void divide_vector(std::vector<std::string>& v, int ini, int fin)
{
	if (v.size() > 1)
	{
		if (ini < fin - 1)
		{
			int mid = (fin + ini) / 2;
			divide_vector(v, ini, mid);
			divide_vector(v, mid, fin);
			pref_comun(v, ini, fin);
		}
	}
	else
		pref = v[0];
}


//Esta función tiene un coste en O(m), siendo m el tamaño de las palabra más larga
void pref_comun(std::vector<std::string>& v, int ini, int fin)
{
	int i;
	i = 0;
	bool comunes = true;

	std::string pal1 = v[ini];
	std::string pal2 = v[fin - 1];

	if (pref.empty())
		prefComun = pal1;
	else
		prefComun = pref;

	pref.clear();

	while (i < pal1.size() && i < pal2.size() && comunes)
	{
		if (pal1[i] == pal2[i] && pal1[i] == prefComun[i])
			pref.push_back(pal1[i]);
		else
		{
			pref.push_back(' ');
			comunes = false;
		}
			
		i++;
	}
}