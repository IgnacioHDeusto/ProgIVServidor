#include "Producto.h"
#include <string.h>
#include <iostream>
using namespace std;

Producto::Producto() {
	this->cod_cat = NULL;
	this->descripcion = NULL;
	this->id_prod = NULL;
	this->nombre = NULL;
	this->precio = NULL;
	this->tamanyo = NULL;
}

Producto::Producto(int cod_cat, char* desc, char* nom, int id_prod, int precio, char* tam){
	this->cod_cat = cod_cat;
	this->id_prod = id_prod;
	this->precio = precio;
	this->nombre = new char[strlen(nom) + 1];
	strcpy(this->nombre, nom);
	this->descripcion = new char[strlen(desc) + 1];
	strcpy(this->descripcion, desc);
	this->tamanyo = new char[strlen(tam) + 1];
	strcpy(this->tamanyo, tam);
}

Producto::~Producto() {
	delete descripcion;
	delete nombre;
	delete tamanyo;
}

