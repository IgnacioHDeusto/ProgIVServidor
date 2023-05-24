/*
 * Pedido.h
 *
 *  Created on: 22 may 2023
 *      Author: Iñaki
 */

#ifndef DATOS_PEDIDO_PEDIDO_H_
#define DATOS_PEDIDO_PEDIDO_H_

class Pedido {

public:
	int n_ped;
	char* fecha;
	char* dni;
	Pedido();
	Pedido(int, char *, char *);
	virtual ~Pedido();
};

#endif /* DATOS_PEDIDO_PEDIDO_H_ */
