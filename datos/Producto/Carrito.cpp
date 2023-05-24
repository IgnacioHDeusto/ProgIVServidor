#include "Carrito.h"
#include <string.h>
#include <iostream>
using namespace std;

Carrito::Carrito() {
	this->numProductos = 0;
	this->productos = NULL;
}

Carrito::Carrito(Producto * productos, int numProd){
	this->productos = productos;
	this->numProductos = numProd;
}

Carrito::~Carrito() {
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


