#include "Pedido.h"
#include <string.h>
#include <iostream>
using namespace std;

Pedido::Pedido() {
	cout << "Constructor Pedido" << endl;
	this->n_ped = NULL;
	this->dni = NULL;
	this->fecha = NULL;
}

Pedido::Pedido(int n_ped, char* fecha, char* dni) {
	cout << "Constructor Pedido" << endl;
	this->n_ped = n_ped;
	this->fecha = new char[strlen(fecha) + 1];
	strcpy(this->fecha, fecha);
	this->dni = new char[strlen(dni) + 1];
	strcpy(this->dni, dni);
}

Pedido::~Pedido() {
	cout << "Destructor Pedido" << endl;
	delete fecha;
	delete dni;
}
void Pedido::imprimirPedido ()
{
    cout << "Pedido -> Nº: "<< this->n_ped <<" FECHA: "<< this->fecha << endl;
}
