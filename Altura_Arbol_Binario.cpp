/*
* bintree_eda.h
*
* Implementaci�n del TAD arbol binario con nodos enlazados usando shared_ptr
*
*  Estructuras de Datos y Algoritmos
*  Facultad de Inform�tica
*  Universidad Complutense de Madrid
*
*  Copyright (c) 2017 Enrique Mart�n Mart�n. All rights reserved.
*/

#ifndef BINTREE_EDA_H_
#define BINTREE_EDA_H_

#include <stdexcept> // domain_error
#include <algorithm> // max
#include <memory>    // shared_ptr, make_shared
#include <iomanip>   // setw
#include <iostream>  // endl
#include <string>
using namespace std;


template <typename T>
class bintree {
private:
	const int TREE_INDENTATION = 4;
	int i = 0;

	/*
	Nodo que almacena internamente el elemento (de tipo T)
	y dos 'punteros compartidos', uno al hijo izquierdo y al hijo derecho.
	*/
	class Nodo; // Declaraci�n adelantada para poder definir Link
	using Link = shared_ptr<Nodo>; // Alias de tipo

	class Nodo {
	public:
		Link izq;
		T elem;
		Link der;

		Nodo(const T& elem) : izq(nullptr), elem(elem), der(nullptr) {}
		Nodo(Link izq, const T& elem, Link der) : izq(izq), elem(elem), der(der) {}
	};

	// puntero a la ra�z
	Link raiz;

	// constructora privada a partir de un puntero a Nodo
	// Para construir los �rboles generados por left() y right()
	bintree(Link r) : raiz(r) {} // O(1)

								 // Muestra por 'out' una representaci�n del �rbol
								 // Adaptado de "ADTs, DataStructures, and Problem Solving with C++", Larry Nyhoff, Person, 2015
	void graph_rec(ostream & out, int indent, Link raiz) const { // O(n), donde 'n' es el n�mero de nodos alcanzables desde 'raiz'
		if (raiz != nullptr) {
			graph_rec(out, indent + TREE_INDENTATION, raiz->der);
			out << setw(indent) << " " << raiz->elem << endl;
			graph_rec(out, indent + TREE_INDENTATION, raiz->izq);
		}
	}

public:
	// constructor de �rbol vac�o
	bintree() : raiz(nullptr) {} // O(1)

								 // constructor de �rbol hoja
	bintree(const T& elem) : raiz(make_shared<Nodo>(elem)) {} // O(1)

															  // constructor de �rbol con 2 hijos
	bintree(const bintree<T>& izq, const T& elem, const bintree<T>& der) : // O(1)
		raiz(make_shared<Nodo>(izq.raiz, elem, der.raiz)) {}

	// Construye un �rbol Binario
	bintree<T> build_bintree()
	{
		T raiz = ' ';
		string s;
		
		getline(cin, s);

		if (i != 0)
			i++;

		while (i < s.size())
		{

			raiz = s[i];

			if (raiz == '.')
				return bintree();

			bintree<T> izq = build_bintree();
			bintree<T> der = build_bintree();

			return bintree<T>(izq, raiz, der);
		}

	}

	// valor en la ra�z (si existe)
	const T& root() const { // O(1)
		if (empty()) {
			throw std::domain_error("No hay raiz en arbol vacio");
		}
		else {
			return raiz->elem;
		}
	}

	// hijo izquierdo (si existe)
	bintree<T> left() const { // O(1)
		return bintree(raiz->izq);
	}

	// hijo derecho (si existe)
	bintree<T> right() const { // O(1)
		return bintree(raiz->der);
	}

	// saber si el �rbol es vac�o 
	bool empty() const { // O(1)
		return (raiz == nullptr);
	}

	// altura del �rbol
	size_t height() const { // O(n), donde 'n' es el n�mero de nodos en el �rbol
		if (empty()) {
			return 0;
		}
		else {
			size_t hl = left().height();
			size_t hr = right().height();
			return max<size_t>(hl, hr) + 1;
		}
	}

	// Muestra por 'out' una representaci�n del �rbol
	// Adaptado de "ADTs, DataStructures, and Problem Solving with C++", Larry Nyhoff, Person, 2015
	void graph(ostream & out) const { // O(n), donde 'n' es el n�mero de nodos en el �rbol
		out << "==== Tree =====" << endl;
		graph_rec(out, 0, raiz);
		out << "===============" << endl;
	}
};

#endif /* BINTREE_EDA_H_ */



int main()
{
	int numCasos;
	cin >> numCasos;

	for (int i = 0; i < numCasos; i++)
	{
		bintree<char> tree = tree.build_bintree();

	}

	system("pause");
	return 0;
}