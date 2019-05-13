/*
* bst.h
*
* Implementación del TAD arbol binario de búsqueda sin repeticiones con nodos enlazados usando shared_ptr
*
*  Estructuras de Datos y Algoritmos
*  Facultad de Informática
*  Universidad Complutense de Madrid
*
*  Copyright (c) 2017 Enrique Martín Martín. All rights reserved.
*/

#ifndef BST_EDA_H_
#define BST_EDA_H_

#include <memory>    // shared_ptr, make_shared
#include <iomanip>   // setw en graphAux
#include <iostream>  // endl
#include <algorithm>
using namespace std;

/*
T: tipo de los elementos almacenados en el bst
Compare: clase que implementa operator() aceptando 2 referencias constantes a valores de tipo T, y devuelve
si el primer valor es "menor" que el segundo. Debe ser un 'strict weak ordering':
(1) irreflexivo, (2) asimétrico, (3) transitivo y con (4) transitividad de la incomparabilidad.
(Ver más detalles en https://en.wikipedia.org/wiki/Weak_ordering#Strict_weak_orderings)
*/
template <typename T, typename Compare = less<T>>
class bst {
private:
	const int TREE_INDENTATION = 4;

	/*
	Nodo que almacena internamente el elemento (de tipo T)
	y dos 'punteros unicos', uno al hijo izquierdo y al hijo derecho.
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

	// objeto comparador
	Compare cmp;


	// busqueda de nodo
	bool search_rec(const T& e, const Link& raiz) const {
		if (raiz == nullptr) {
			return false;
		}
		else if (cmp(e, raiz->elem)) {
			return search_rec(e, raiz->izq);
		}
		else if (cmp(raiz->elem, e)) {
			return search_rec(e, raiz->der);
		}
		else { // e == nodo->elem
			return true;
		}
	}


	// cálculo recursivo del tamaño
	size_t size_rec(const Link& nodo) const {
		if (nodo == nullptr) {
			return 0;
		}
		else {
			return size_rec(nodo->izq) + size_rec(nodo->der) + 1;
		}
	}


	// inserción recursiva de elemento 
	void insert_rec(Link& raiz, const T& e) {
		if (raiz == nullptr) {
			raiz = make_shared<Nodo>(e);
		}
		else if (cmp(e, raiz->elem)) {
			insert_rec(raiz->izq, e);
		}
		else if (cmp(raiz->elem, e)) {
			insert_rec(raiz->der, e);
		}
		else {
			// Si e == raiz-elem el elemento ya esta, puedo lanzar una excepcion 
			// o no hacer nada
		}
	}


	// Dada la raiz de un árbol NO VACIO (es decir, raiz != nullptr), borra el nodo mínimo y 
	// devuelve el elemento que había ahí
	void remove_min(Link& raiz, T& min) {
		if (raiz->izq == nullptr) { // El nodo raiz contiene el mínimo
			min = raiz->elem;
			raiz = raiz->der; // El anterior nodo al que apuntaba raiz ya no tiene dueño, se libera la memoria
		}
		else {
			remove_min(raiz->izq, min);
		}
	}


	void remove_rec(Link& raiz, const T& e) {
		if (raiz == nullptr) // Imposible eliminar en árbol vacío
			return;

		if (cmp(e, raiz->elem)) {
			remove_rec(raiz->izq, e);
		}
		else if (cmp(raiz->elem, e)) {
			remove_rec(raiz->der, e);
		}
		else if (raiz->der == nullptr) { // e == raiz->elem
			raiz = raiz->izq;
		}
		else { // e == raiz->elem && raiz->der != nullptr
			T min;
			remove_min(raiz->der, min);
			raiz->elem = min;
		}
	}


	// Muestra por 'out' una representación del árbol
	// Adaptado de "ADTs, DataStructures, and Problem Solving with C++", Larry Nyhoff, Person, 2015
	void graph_rec(ostream & out, int indent, Link raiz) const {
		if (raiz != nullptr) {
			graph_rec(out, indent + TREE_INDENTATION, raiz->der);
			out << setw(indent) << " " << raiz->elem << endl;
			graph_rec(out, indent + TREE_INDENTATION, raiz->izq);
		}
	}


	// Realiza una copia de todos los nodos que cuelgan de 'raiz'
	Link copia(Link raiz) {
		if (raiz == nullptr) {
			return nullptr;
		}
		else {
			Link ni = copia(raiz->izq);
			Link nd = copia(raiz->der);
			return make_shared<Nodo>(ni, raiz->elem, nd);
		}
	}

	//El coste de esta función es O(n), siendo n la distancia en el árbol del nodo al elemento
	int dist_nodo_elem(Link nodo, const T& elem, int& dist) const
	{
		if (cmp(nodo->elem, elem))
			dist_nodo_elem(nodo->der, elem, dist);
		else if (cmp(elem, nodo->elem))
			dist_nodo_elem(nodo->izq, elem, dist);

		dist++;
		return dist;
	}

	//El coste de esta función es O(n), siendo n la distancia de la raíz al nodo común buscado
	Link nodo_comun(Link raiz, const T& a, const T& b) const
	{
		if (raiz->elem != a && raiz->elem != b)
		{
			if (cmp(b, raiz->elem))
				raiz = nodo_comun(raiz->izq, a, b);
			else if (cmp(raiz->elem, a))
				raiz = nodo_comun(raiz->der, a, b);
			else
				return raiz;
		}
		else
			return raiz;

		return raiz;
	}

	//El coste de este método es O(n), siendo n la distancia entre a y b
	void calcula_distancia(Link raiz, const T& a, const T& b, int& dist) const
	{
		Link ncomun;
		ncomun = nodo_comun(raiz, a, b);

		int dist_a = 0;
		int dist_b = 0;

		dist_a = dist_nodo_elem(ncomun, a, dist_a);
		dist_b = dist_nodo_elem(ncomun, b, dist_b);

		dist_a = dist_a - 1;
		dist_b = dist_b - 1;

		dist = dist_a + dist_b;
	}

	//El coste de este algoritmo es O(n), siendo n la distancia entre los dos nodos
	void diametro_rec(Link raiz, int& diam, int& h) const
	{
		if (raiz == nullptr)
		{
			diam = -1;
			h = 0;
		}			
		else
		{
			int diamIzq, hIzq;
			diametro_rec(raiz->izq, diamIzq, hIzq);
			int diamDer, hDer;
			diametro_rec(raiz->der, diamDer, hDer);
			diam = max(max(diamIzq, diamDer), hIzq + hDer);
			h = 1 + max(hIzq, hDer);
		}
	}

public:
	// constructor de bst vacío
	bst() : raiz(nullptr) {}


	// constructor por copia
	bst(const bst<T, Compare>& other) {
		raiz = copia(other.raiz);
	}

	// Asignacion
	bst<T, Compare>& operator=(const bst<T, Compare>& other) {
		if (this != &other) {
			raiz.reset();
			raiz = copia(other.raiz);
		}
		return *this;
	}


	// saber si el bst es vacío 
	bool empty() const {
		return (raiz == nullptr);
	}


	// tamaño del bst
	size_t size() const {
		return size_rec(raiz);
	}

	// buscar un elemento
	bool search(const T& e) const {
		return search_rec(e, raiz);
	}


	// insertar un elemento
	void insert(const T& e) {
		insert_rec(raiz, e);
	}


	// borrar un elemento
	void remove(const T& e) {
		remove_rec(raiz, e);
	}


	// Muestra por 'out' una representación del árbol
	// Adaptado de "ADTs, DataStructures, and Problem Solving with C++", Larry Nyhoff, Person, 2015
	void graph(ostream & out) const {
		out << "==== Tree =====" << endl;
		graph_rec(out, 0, raiz);
		out << "===============" << endl;
	}

	//El coste de este método es O(n), siendo n la distancia entre a y b
	int distancia(const T& a, const T& b) const
	{
		int dist = 0;

		if (cmp(a, b))
			calcula_distancia(raiz, a, b, dist);	
		else
			calcula_distancia(raiz, b, a, dist);

		return dist;
	}

	//El coste de esta función es O(n), siendo n la distancia entre los dos nodos
	int diametro() const
	{
		int diametro, altura;
		diametro_rec(raiz, diametro, altura);
		
		if (diametro == -1)
			diametro = 0;
		
		return diametro;
	}
};

#endif /* BST_EDA_H_ */

//------------------------------------------------------------------------------------------------
// PROGRAMA PRINCIPAL


// FUNCIONES



int main()
{
	int numCasos;
	cin >> numCasos;

	for (int i = 0; i < numCasos; i++)
	{
		int elemsArbol;
		cin >> elemsArbol;
		bst<int> tree = bst<int>();

		for (int i = 0; i < elemsArbol; i++)
		{
			int n;
			cin >> n;
		
			tree.insert(n);	
		}

		int diametro = tree.diametro();
		cout << diametro << endl;

		int numDist;
		cin >> numDist;

		for (int i = 0; i < numDist; i++)
		{
			int dist = 0;
			int num1, num2;

			cin >> num1;
			cin >> num2;

			dist = tree.distancia(num1, num2);

			cout << dist << endl;
		}

		cout << endl;
	}

	return 0;
}
