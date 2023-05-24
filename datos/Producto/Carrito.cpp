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

Producto* Carrito::EliminarProd(int id){
    Producto * productos2;
    for (int i = 0; i < numProductos; i++) {
        if (productos[i].id_prod != id) {
            productos2[i] = productos[i];
        }
      }
    return productos2;
}

void Carrito::imprimirProducto (Producto p)
{
    cout << "Producto -> ID: "<< p.id_prod <<" NOMBRE: "<< p.nombre <<" PRECIO: "<< p.precio << "€" << endl;
}


void Carrito::imprimirCarrito(Carrito c)
{
    cout << "-------------------------" << endl;
    cout << "        TU CARRITO       " << endl;
    cout << "-------------------------" << endl;
    for (int i = 0; i < c.numProductos; ++i)
    {
        imprimirProducto(c.productos[i]);
    }
}


