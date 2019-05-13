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
using namespace std;

/*
T: tipo de los elementos almacenados en el bst
Compare: clase que implementa operator() aceptando 2 referencias constantes a valores de tipo T, y devuelve
si el primer valor es "menor" que el segundo. Debe ser un 'strict weak ordering':
(1) irreflexivo, (2) asimétrico, (3) transitivo y con (4) transitividad de la incomparabilidad.
(Ver más detalles en https://en.wikipedia.org/wiki/Weak_ordering#Strict_weak_orderings)
*/

struct Par
{
	int diam;
	int alt;
};

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

	int altura_elem(Link raiz, const T& a) const
	{
		int alt;
		int i = 0;

		if (a != raiz->elem)
		{
			i++;
			if (a < raiz->elem)
				altura_elem(raiz->izq, raiz->izq->elem);
			else
				altura_elem(raiz->izq, raiz->der->elem);
		}

		return i;

	}

	Par diametro_rec(bst<T> tree) const
	{
		Par p, p_izq, p_der;
		if (empty())
		{
			p.diam = -1;
			p.alt = 0;
		}
		else
		{
			p_izq = diametro_rec(tree->izq);
			p_der = diametro_rec(tree->der);
			p.diam = max(max(p_izq.diam, p_der.diam), p_izq.alt + p_der.alt);
			p.alt = 1 + max(p_izq.alt, p_der.alt);

		}

		return p;
	}

	int max(int a, int b)
	{
		int maximo = 0;
		if (a > b)
			maximo = a;
		else
			maximo = b;
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

	//Devuelve la distancia entre dos elementos a y b
	int distancia(const T& a, const T& b) const
	{
		//Si los elementos están en el mismo subarbol hay que restar
		//Si están en distintos subárboles hay que restar
		int h_a, h_b;
		int resultado;
		h_a = altura_elem(raiz, a);
		h_b = altura_elem(raiz, b);

		if ((a < raiz->elem && b > raiz->elem) || (a > raiz->elem && b < raiz->elem))
		{
			resultado = h_a + h_b;
		}
		else
		{
			
			resultado = h_a - h_b;
			if (resultado == 0)
				resultado = h_a;

		}
		
		return resultado;
	}

	int diametro(bst<T> t) const
	{
		Par p;
		p = diametro_rec(t);
		return p.diam;
	}
};

#endif /* BST_EDA_H_ */

int main()
{
	int numCasos, elem, nodos;
	int elem1, elem2;
	bst<int> tree = bst<int>();
	cin >> numCasos;
	for (int i = 0; i < numCasos; i++)
	{
		cin >> nodos;
		for (int i = 0; i < nodos; i++)
		{
			cin >> elem;
			tree.insert(elem);
		}
		cout << tree.diametro(tree) << endl;
		/*cin >> elem1;
		cin >> elem2;
		cout << tree.distancia(elem1, elem2) << endl;*/
	}

	system("pause");


	return 0;
}