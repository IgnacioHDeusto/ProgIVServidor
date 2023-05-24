#ifndef DATOS_PEDIDO_CARRITO_H_
#define DATOS_PEDIDO_CARRITO_H_
#include "Producto.h"

class Carrito {
public:
	Producto * productos;
	int numProductos;
	Carrito();
	Carrito(Producto* , int);
	virtual ~Carrito();
	void AnadirProd(Producto p);
	Producto* EliminarProd(int id);
	void imprimirProducto (Producto p);
	void imprimirCarrito(Carrito c);
};

#endif /* DATOS_PEDIDO_CARRITO_H_ */
