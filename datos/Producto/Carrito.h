#ifndef DATOS_PEDIDO_CARRITO_H_
#define DATOS_PEDIDO_CARRITO_H_
#include "Producto.h"

class Carrito {
public:
	Producto* productos;
	int numProductos;
	Carrito();
	Carrito(int);
	virtual ~Carrito();
	void EliminarProd(int id);
	void imprimirCarrito();
};

#endif /* DATOS_PEDIDO_CARRITO_H_ */
