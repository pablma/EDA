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

	// Calcula la altura de un árbol dada su raíz
	//Este método tiene un coste de O(n), siendo n la altura del árbol
	int height_sub_tree(Link raiz, bool& bst)
	{
		if (raiz == nullptr)
			return 0;
		else
		{
			int hl = height_sub_tree(raiz->izq, bst);
			int hr = height_sub_tree(raiz->der, bst);
			
			if (raiz->izq != nullptr)
			{
				if (raiz->izq->elem >= raiz->elem )
					bst = false;
			}

			if (raiz->der != nullptr)
			{
				if (raiz->der->elem <= raiz->elem)
					bst = false;
			}
			 

			return max(hl, hr) + 1;
		}
			
			
	}



public:
	// constructor de árbol vacío
	bintree() : raiz(nullptr) {} // O(1)

								 // constructor de árbol hoja
	bintree(const T& elem) : raiz(make_shared<Nodo>(elem)) {} // O(1)

															  // constructor de árbol con 2 hijos
	bintree(const bintree<T>& izq, const T& elem, const bintree<T>& der) : // O(1)
		raiz(make_shared<Nodo>(izq.raiz, elem, der.raiz)) {}

	bintree<T> build_tree()
	{
		int raiz;
		cin >> raiz;

		if (raiz == 0)
			return bintree<T>();

		bintree<T> izq = build_tree();
		bintree<T> der = build_tree();

		return bintree<T>(izq, raiz, der);
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

	// Este método tiene un coste de O(n), siendo n la altura de los subárboles izqdo y dcho (tomamos como n el mayor de ambos)
	pair<bool, bool> Equilibrado_Bst()
	{
		int hIzq, hDer;
		bool bst = true;
		bool balanceado = false;

		if (raiz->izq != nullptr)
		{
			if (raiz->elem <= raiz->izq->elem)
				bst = false;
		}

		if (raiz->der != nullptr)
		{
			if (raiz->der->elem <= raiz->elem)
				bst = false;
		}

		if (empty())
		{
			balanceado = true;
			bst = false;
		}		
		else
		{
			// Calculamos la altura de cada subárbol, el izq y el der
			hIzq = height_sub_tree(raiz->izq, bst);
			hDer = height_sub_tree(raiz->der, bst);

			int dif = abs(hIzq - hDer);

			if (dif == 0 || dif == 1)
				balanceado = true;
		}

		
		return make_pair(balanceado, bst);

	}

	bool balanceado(Link raiz, int& height)
	{
		int hl = 0;
		int hr = 0;

		if (raiz == nullptr)
		{
			height = 0;
			return true;
		}
		else
		{
			hl = balanceado(raiz->izq, hl);
			hr = balanceado(raiz->der, hr);

			int dif = abs(hl - hr);

			if (dif > 1)
				return false;

			if (hl > hr)
				height = hl + 1;
			else
				height = hr + 1;
		}
	}

	//Método separado para saber si es balanceado
	int balanceado(Link raiz, bool& eq)
	{
		if (raiz == nullptr)
			return 0;
		else
		{
			int hl = balanceado(raiz->izq, eq);
			int hr = balanceado(raiz->der, eq);
			
			int dif = abs(hl - hr);

			if (dif > 1)
				eq = false;

			return max(hl, hr) + 1;
		}
	}

	//Método separado para saber si es bst
	bool es_bst(Link raiz, int min, int max, bool& bst)
	{
		if (raiz == nullptr)
			return true;
		else
		{
			bool bstIzq = es_bst(raiz->izq, min, raiz->elem - 1, bst);
			bool bstDer = es_bst(raiz->der, raiz->elem + 1, max, bst);


			if (raiz->elem >= max || raiz->elem <= min)
				return false;

			if (!bstIzq || !bstDer)
				bst = false;
		}
	}

	//Método que combina ambos para que esté en un coste de O(n)
	pair<bool, int> balanceado_bst(Link raiz, int min_interval, int max_interval, bool& eq, bool& bst)
	{
		if (raiz == nullptr)
			return make_pair(true, 0);
		else
		{
			pair<bool, int> l = balanceado_bst(raiz->izq, min_interval, raiz->elem - 1, eq, bst);
			pair<bool, int> r = balanceado_bst(raiz->der, raiz->elem + 1, max_interval, eq, bst);
		
			int dif = abs(l.second - r.second);
			if (dif > 1)
				eq = false;

			if ((raiz->elem > max_interval) || (raiz->elem < min_interval))
				return make_pair(false, max(l.second, r.second) + 1);

			if (!l.first || !r.first)
				bst = false;

			return make_pair(true, max(l.second, r.second) + 1);
		}
	}

	//Método que calcula si el árbol es bst
	bool bst()
	{
		bool bst = true;
		es_bst(raiz, 1, raiz->elem, bst);
		return bst;
	}

	//Método que calcula si está balanceado
	bool esta_balanceado()
	{
		bool b = true;
		balanceado(raiz, b);
		return b;
	}

	//Método que combina ambos para que su coste se O(n)
	pair<bool, bool> esta_balanceado_bst()
	{
		bool bst = true;
		bool balanceado = true;
		balanceado_bst(raiz, 1, 9999, balanceado, bst);

		return make_pair(balanceado, bst);
	}

	// Muestra por 'out' una representación del árbol
	// Adaptado de "ADTs, DataStructures, and Problem Solving with C++", Larry Nyhoff, Person, 2015
	void graph(ostream & out) const { // O(n), donde 'n' es el número de nodos en el árbol
		out << "==== Tree =====" << endl;
		graph_rec(out, 0, raiz);
		out << "===============" << endl;
	}
};

#endif /* BINTREE_EDA_H_ */

//PROGRAMA PRINCIPAL


int main()
{
	bintree<int> tree = tree.build_tree();

	pair<bool, bool> p = tree.esta_balanceado_bst();

	if (p.first)
		cout << "BALANCEADO";
	else
		cout << "NO BALANCEADO";		

	cout << " ";

	if(p.second)
		cout << "BST";
	else
		cout << "NO BST";

	
	cout << endl;
	system("pause");
	return 0;
}