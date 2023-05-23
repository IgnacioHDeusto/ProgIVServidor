#include "Carrito.h"
#include "Pedido.h"
#include <string.h>
#include <iostream>
using namespace std;

Carrito::Carrito() {
	cout << "Constructor Carrito" << endl;
	this->numProductos = 0;
	this->productos = NULL;
}

Carrito::Carrito(Producto * productos, int numProd){
	this->productos = productos;
	this->numProductos = numProd;
}

Carrito::~Carrito() {
	cout << "Destructor Carrito" << endl;
	delete productos;
}

void Carrito::AnadirProd(Producto p){
	this->numProductos++;
	Producto * prods = new Producto[numProductos];
	for (int i = 0; i < numProductos; ++i) {
		if (i == numProductos) {
			prods[i] = p;
		} else {
			prods[i] = this->productos[i];
		}
	}
	this->productos = prods;
}


