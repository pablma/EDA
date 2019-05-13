/*
* bintree_eda.h
*
* Implementación del TAD arbol binario con nodos enlazados usando shared_ptr
*
*  Estructuras de Datos y Algoritmos
*  Facultad de Informática
*  Universidad Complutense de Madrid
*
*  Copyright (c) 2017 Enrique Martín Martín. All rights reserved.
*/

#ifndef BINTREE_EDA_H_
#define BINTREE_EDA_H_

#include <stdexcept> // domain_error
#include <algorithm> // max
#include <memory>    // shared_ptr, make_shared
#include <iomanip>   // setw
#include <iostream>  // endl
#include <vector>
#include <string>

using namespace std;


template <typename T>
class bintree {
private:
	const int TREE_INDENTATION = 4;

	/*
	Nodo que almacena internamente el elemento (de tipo T)
	y dos 'punteros compartidos', uno al hijo izquierdo y al hijo derecho.
	*/
	class Nodo; // Declaración adelantada para poder definir Link
	using Link = shared_ptr<Nodo>; // Alias de tipo

	class Nodo {
	public:
		Link izq;
		T elem;
		Link der;

		Nodo(const T& elem) : izq(nullptr), elem(elem), der(nullptr) {}
		Nodo(Link izq, const T& elem, Link der) : izq(izq), elem(elem), der(der) {}
	};

	// puntero a la raíz
	Link raiz;

	// constructora privada a partir de un puntero a Nodo
	// Para construir los árboles generados por left() y right()
	bintree(Link r) : raiz(r) {} // O(1)

								 // Muestra por 'out' una representación del árbol
								 // Adaptado de "ADTs, DataStructures, and Problem Solving with C++", Larry Nyhoff, Person, 2015
	void graph_rec(ostream & out, int indent, Link raiz) const { // O(n), donde 'n' es el número de nodos alcanzables desde 'raiz'
		if (raiz != nullptr) {
			graph_rec(out, indent + TREE_INDENTATION, raiz->der);
			out << setw(indent) << " " << raiz->elem << endl;
			graph_rec(out, indent + TREE_INDENTATION, raiz->izq);
		}
	}

	void draw_fib_tree_rec(Link raiz)
	{
		if (raiz != nullptr)
		{
			cout << raiz->elem << endl;
			draw_fib_tree_rec(raiz->izq);
			draw_fib_tree_rec(raiz->der);
		}

	}

	void levels_rec(Link raiz, vector<string>& order, int n, int level)	//n empieza con valor 1
	{
		int huecos = 3 * level;
		
		if (raiz != nullptr)
		{
			for (int i = 0; i < huecos; i++)
				order[n - 1].push_back(' ');

			transforma_inserta_nums(raiz->elem, order, n);
			
			int nIzq = 2 * n;
			levels_rec(raiz->izq, order, nIzq, level + 1);

			int nDer = (2 * n) + 1;
			levels_rec(raiz->der, order, nDer, level + 1);
		}

	}


	void transforma_inserta_nums(int num, vector<string>& order, int n)
	{
		string s = to_string(num);
		for (int i = 0; i < s.size(); i++)
			order[n - 1].push_back(s[i]);
	}

	int fib(int n) const
	{
		if (n == 0)
			return 0;
		else if (n == 1)
			return 1;
		else
			return fib(n - 2) + fib(n - 1);
	}

public:
	// constructor de árbol vacío
	bintree() : raiz(nullptr) {} // O(1)

								 // constructor de árbol hoja
	bintree(const T& elem) : raiz(make_shared<Nodo>(elem)) {} // O(1)

															  // constructor de árbol con 2 hijos
	bintree(const bintree<T>& izq, const T& elem, const bintree<T>& der) : // O(1)
		raiz(make_shared<Nodo>(izq.raiz, elem, der.raiz)) {}

	bintree<T> build_fib_tree(const T& e) const
	{
		int n = fib(e);

		if ((n == 0 || n == 1) && (e - 2 < 0))
			return bintree<T>(n);
		else
		{
			bintree<T> izq = build_fib_tree(e - 2);
			bintree<T> der = build_fib_tree(e - 1);

			return bintree<T>(izq, n, der);
		}
	}

	// valor en la raíz (si existe)
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

	// saber si el árbol es vacío 
	bool empty() const { // O(1)
		return (raiz == nullptr);
	}

	// altura del árbol
	size_t height() const { // O(n), donde 'n' es el número de nodos en el árbol
		if (empty()) {
			return 0;
		}
		else {
			size_t hl = left().height();
			size_t hr = right().height();
			return max<size_t>(hl, hr) + 1;
		}
	}

	// Muestra por 'out' una representación del árbol
	// Adaptado de "ADTs, DataStructures, and Problem Solving with C++", Larry Nyhoff, Person, 2015
	void graph(ostream & out) const { // O(n), donde 'n' es el número de nodos en el árbol
		out << "==== Tree =====" << endl;
		graph_rec(out, 0, raiz);
		out << "===============" << endl;
	}

	vector<string> draw_fib_tree()
	{
		int h = height();
		vector<string> fib_order(pow(2, h) - 1);
		int n = 1;
		int level = 0;
		levels_rec(raiz, fib_order, n, level);

		return fib_order;
	}
};

#endif /* BINTREE_EDA_H_ */

//PROGRAMA PRINCIPAL

//FUNCIONES
void representa_vector(vector<string>& v);



int main()
{
	int raiz;
	vector<string> vec;
	cin >> raiz;

	while (raiz >= 0)
	{
		bintree<int> tree = tree.build_fib_tree(raiz);
		vec = tree.draw_fib_tree();
		representa_vector(vec);
		cin >> raiz;
	}

	return 0;
}


void representa_vector(vector<string>& v)
{
	for (int i = 0; i < v.size(); i++)
	{
		if(!v[i].empty())
		cout << v[i] << endl;
	}

	cout << "====" << endl;
}