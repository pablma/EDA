/*
* queue_eda2.h
*
* Implementaci�n del TAD cola con nodos enlazados y nodo fantasma
*
* Estructuras de Datos y Algoritmos
* Facultad de Inform�tica
* Universidad Complutense de Madrid
*
* Copyright (c) 2017 Enrique Mart�n Mart�n. All rights reserved.
*/

#ifndef QUEUE_EDA2_H_
#define QUEUE_EDA2_H_


#include <stdexcept>
#include <iostream>

template <typename T>
class ColaVIP {
private:

	class Nodo {
	public:
		T elem;
		T prioridad;
		Nodo* sig;
		Nodo(const T& e, Nodo* n, const T& p) : elem(e), sig(n), prioridad(p) {} // Constructor
		Nodo() : sig(nullptr) {} // Constructor
	};

	// n�mero de elementos en la cola
	size_t nelems;

	// n�mero m�ximo de prioridad que puede haber en la cola
	int maxPrioridades;

	// punteros al primer y �ltimo elemento
	Nodo* fantasma;
	Nodo* ultimo;

	// Libera la memoria din�mica
	void libera();

	// copia desde otra cola
	void copia(const ColaVIP<T> &other);

	// Copia una lista de nodos
	void copia_nodos(const Nodo* n);


public:
	//ColaVIP() : nelems(0), fantasma(new Nodo), ultimo(fantasma) {};

	// constructor: cola vac�a
	ColaVIP(int p);

	// destructor
	~ColaVIP();

	// constructor por copia
	ColaVIP(const ColaVIP<T>& other);

	// operador de asignaci�n
	ColaVIP<T> & operator=(const ColaVIP<T>& other);

	// encolar un elemento
	void push(T p, const T& elem);

	// consultar primer elemento
	T const& front() const;

	// eliminar primer elemento
	void pop();

	// consultar si la cola est� vac�a
	bool empty() const;

	// consultar el tama�o de la cola
	size_t size() const;
};



template<typename T>
void ColaVIP<T>::libera() {
	Nodo* node = fantasma;
	while (node != nullptr) {
		Nodo* next = node->sig;
		delete node;
		node = next;
	}
	fantasma = nullptr;
	ultimo = nullptr;
}


template<typename T>
void ColaVIP<T>::copia(const ColaVIP<T> &other) {
	nelems = other.nelems;
	copia_nodos(other.fantasma);
}


template<typename T>
void ColaVIP<T>::copia_nodos(const Nodo* head) {
	fantasma = new Nodo();
	ultimo = fantasma;
	while (head->sig != nullptr) {
		Nodo* aux = new Nodo(head->sig->elem, nullptr);
		ultimo->sig = aux;
		ultimo = aux;
		head = head->sig;
	}
}


template<typename T>
ColaVIP<T>::ColaVIP(int p) : nelems(0), fantasma(new Nodo), ultimo(fantasma), maxPrioridades(p) {}


template<typename T>
ColaVIP<T>::~ColaVIP() {
	libera();
}


template<typename T>
ColaVIP<T>::ColaVIP(const ColaVIP<T>& other) : nelems(0), fantasma(nullptr), ultimo(nullptr) {
	copia(other);
}


template<typename T>
ColaVIP<T> & ColaVIP<T>::operator=(const ColaVIP<T>& other) {
	if (this != &other) { // evita auto-asignaci�n
		libera();
		copia(other);
	}
	return *this;
}



template<typename T>
void ColaVIP<T>::push(T p, const T& elem) { // O(1)
	Nodo* node = new Nodo(elem, ultimo->sig, p);
	ultimo->sig = node;
	ultimo = node;
	nelems++;
}


template<typename T>
T const& ColaVIP<T>::front() const { // O(1)
	if (empty()) {
		throw std::domain_error("Cola vac�a");
	}
	else {
		int cont_p = maxPrioridades;
		Nodo* nodo = fantasma->sig;
		Nodo* VIPelem = nullptr;
		int i = 0;
		//return fantasma->sig->elem;
		while (i < size())
		{
			if (nodo->prioridad < cont_p)
			{
				VIPelem = nodo;
				cont_p = nodo->prioridad;
			}
				

			nodo = nodo->sig;
			i++;
		}

		return VIPelem->elem;
	}

}


template<typename T>
void ColaVIP<T>::pop() { // O(1)
	if (empty()) {
		throw std::domain_error("Eliminar en cola vac�a");
	}
	else {
		/*nelems--;
		Nodo* head = fantasma->sig;
		Nodo* head_next = head->sig;
		delete head;
		fantasma->sig = head_next;*/
		int cont_p = maxPrioridades;
		Nodo* nodo = fantasma->sig;
		Nodo* ant = fantasma;
		Nodo* VIPelem = nullptr;
		Nodo* VIPelem_ant = nullptr;
		int i = 0;
		//return fantasma->sig->elem;
		while (i < size())
		{
			if (nodo->prioridad < cont_p)
			{
				VIPelem = nodo;
				VIPelem_ant = ant;
				cont_p = nodo->prioridad;
			}

			ant = nodo;
			nodo = nodo->sig;
			i++;
		}

		VIPelem_ant->sig = VIPelem->sig;
		nelems--;
	}


}


template<typename T>
bool ColaVIP<T>::empty() const { // O(1)
	return size() == 0;
}

template<typename T>
size_t ColaVIP<T>::size() const { // O(1)
	return nelems;
}


#endif /* QUEUE_EDA2_H_ */


int main()
{
	int numCasos;
	std::cin >> numCasos;
	

	for (int i = 0; i < numCasos; i++)
	{
		int numPrioridades;
		int movimientos;
		int aforoMax;
		int aforo = 0;

		std::cin >> numPrioridades;
		std::cin >> movimientos;
		std::cin >> aforoMax;

		ColaVIP<int> cola = ColaVIP<int>(numPrioridades);

		for (int j = 0; j < movimientos; j++)
		{
			char c;
			std::cin >> c;

			if (c == '+')
			{
				int prioridad;
				std::cin >> prioridad;
				int e;
				std::cin >> e;
				aforo++;
				if (aforo > aforoMax)
					cola.push(prioridad, e);
			}
			else
			{
				if (!cola.empty())
					cola.pop();
			}
		
		}

		if (cola.empty())
			std::cout << "NADIE";
		else
		{
			int size = cola.size();
			for (int k = 0; k < size; k++)
			{
				std::cout << cola.front() << " ";
				cola.pop();
			}
		}
		std::cout << std::endl;
 	
	}

	return 0;
}