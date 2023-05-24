/*
 * Producto.h
 *
 *  Created on: 22 may 2023
 *      Author: Iñaki
 */

#ifndef DATOS_PRODUCTO_PRODUCTO_H_
#define DATOS_PRODUCTO_PRODUCTO_H_

class Producto {
public:
	int id_prod;
	char* nombre;
	char* descripcion;
	int cod_cat;
	int precio;
	char* tamanyo;
	Producto();
	Producto(int, char*, char*, int, int, char*);
	virtual ~Producto();
	void imprimirProducto ();
};

#endif /* DATOS_PRODUCTO_PRODUCTO_H_ */
