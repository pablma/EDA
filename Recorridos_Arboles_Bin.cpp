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

	//Todos los recorridos están en O(n), siendo n el número de nodos del árbol

	// Recorrido preorden recursivo
	void preorder_rec(Link raiz, vector<T>& order) const
	{
		if (raiz != nullptr)
		{
			order.push_back(raiz->elem);
			preorder_rec(raiz->izq, order);
			preorder_rec(raiz->der, order);
		}
	}

	// Recorrido inorden recursivo
	void inorder_rec(Link raiz, vector<T>& order) const
	{
		if (raiz != nullptr)
		{
			inorder_rec(raiz->izq, order);
			order.push_back(raiz->elem);
			inorder_rec(raiz->der, order);
		}
	}

	// Recorrido postorden recursivo
	void postorder_rec(Link raiz, vector<T>& order) const
	{
		if (raiz != nullptr)
		{
			postorder_rec(raiz->izq, order);
			postorder_rec(raiz->der, order);
			order.push_back(raiz->elem);
		}
	}

	// Recorrido niveles recursivo
	void levels_rec(Link raiz, vector<T>& order, T& n) const
	{
		if (raiz != nullptr)
		{
			order[n - 1] = raiz->elem;

			int nIzq = 2 * n;
			levels_rec(raiz->izq, order, nIzq);
			
			int nDer = (2 * n) + 1;
			levels_rec(raiz->der, order, nDer);
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


	// construye un árbol de forma recursiva
	bintree<T> Build_tree()
	{
		T raiz;
		cin >> raiz;

		if (raiz == 0)
			return bintree<T>();

		bintree<T> izq = Build_tree();
		bintree<T> der = Build_tree();
		
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

	// Muestra por 'out' una representación del árbol
	// Adaptado de "ADTs, DataStructures, and Problem Solving with C++", Larry Nyhoff, Person, 2015
	void graph(ostream & out) const { // O(n), donde 'n' es el número de nodos en el árbol
		out << "==== Tree =====" << endl;
		graph_rec(out, 0, raiz);
		out << "===============" << endl;
	}

	// Recorrido preorden
	vector<T> preorder() const
	{
		vector<T> preorder;
		preorder_rec(raiz, preorder);
		return preorder;
	}

	// Recorrido inorden
	vector<T> inorder() const
	{
		vector<T> inorder;
		inorder_rec(raiz, inorder);
		return inorder;
	}

	// Recorrido postorden
	vector<T> postorder() const
	{
		vector<T> postorder;
		postorder_rec(raiz, postorder);
		return postorder;
	}

	// Recorrido niveles
	vector<T> levels() const
	{
		int h = height();
		vector<T> levels_order(pow(2, h) - 1);
		int n = 1;
		
		levels_rec(raiz, levels_order, n);
		return levels_order;
	}

};

#endif /* BINTREE_EDA_H_ */

//------------------------------------------------------------------------------------------------
// PROGRAMA PRINCIPAL


// FUNCIONES
void imprime_vector(vector<int> v);


int main()
{
	int numCasos;
	cin >> numCasos;
	vector<int> recorrido;


	for (int i = 0; i < numCasos; i++)
	{
		bintree<int> arbol = arbol.Build_tree();

		// Preorden
		recorrido = arbol.preorder();
		imprime_vector(recorrido);

		// Inorden
		recorrido = arbol.inorder();
		imprime_vector(recorrido);

		//Postorden
		recorrido = arbol.postorder();
		imprime_vector(recorrido);

		//Niveles
		recorrido = arbol.levels();
		imprime_vector(recorrido);
		
		cout << "==" << endl;	
	}

	return 0;
}


// El coste de esta función es O(n), siendo n el tamaño del vector
void imprime_vector(vector<int> v)
{
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i] != 0)
		{
			if (i != v.size() - 1)
				cout << v[i] << " ";
			else
				cout << v[i];
		}
	}
	
	cout << endl;
}