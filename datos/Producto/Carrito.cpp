#include "Carrito.h"
#include "Producto.h"
#include "string.h"
#include <iostream>
using namespace std;

Carrito::Carrito() {
	this->numProductos = 0;
	this->productos = NULL;
}

Carrito::Carrito(int tamCarrito){
	this->productos = new Producto [tamCarrito];
	this->numProductos = 0;
}

Carrito::~Carrito() {
	delete productos;
}


void Carrito::EliminarProd(int id){
    Producto * productos2;
    for (int i = 0; i < numProductos; i++) {
        if (productos[i].id_prod != id) {
            productos2[i] = productos[i];
        }
      }
    this->productos = productos2;
}


void Carrito::imprimirCarrito()
{
    cout << "-------------------------" << endl;
    cout << "        TU CARRITO       " << endl;
    cout << "-------------------------" << endl;
    for (int i = 0; i < this->numProductos; ++i)
    {
        this->productos[i].imprimirProducto();
        fflush(stdout);
    }
}


