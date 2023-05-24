#include "../datos/Producto/Producto.h"
#include "../datos/Producto/Categoria.h"
#include "../datos/Producto/Carrito.h"
#include "../datos/Pedido/Pedido.h"

#ifndef FUNCIONES_FUNCIONESBD_H_
#define FUNCIONES_FUNCIONESBD_H_

	char* load_config(char* filename, char* buscar);
	void iniciarBD();

//	void insertarCategoria(Categoria c);
//
//	void insertarCiudad(Ciudad ci);
//
//	void insertarProvincia(Provincia prov);
//
//	void BorrarProvincia(int id);
//
//	void selectCategoria(int ct);
//
//	void selectProvincia(int pr);
//
//	void crearGestor(Trabajador t);
//
//	void crearProducto(Producto p);
//
//	int comprobarUsuario(char* usuario, char* contrasena);

	int comprobarUsuario(char* usuario, char* contrasena);

	void MostrarTrabajadores();

	void ListaProductos();

	int nProductos();

	Producto* Productos();

	int UsuarioExiste(char * usuario);

//	void BorrarProducto(int id);
//
//	void insertarAlmacen(Almacen al);
//
//	void BorrarAlmacen(int id);
//
//	void ListaAlmacenes();
//
//	void aumentarStock(int stock, int id_prod, int id_alm);
//
//	void borrarStock(int id_prod, int id_alm);
//
//	int comprobarStock(int id_prod, int id_alm);
//
//	void ConsultarStock();
//
//	void insertarPedido(Pedido ped);
//
//	void listaPedidos();
//
//	void EnviarPedido(int id);
//
//	int comprobarPedido(int n_ped);
//
//	void BorrarCompraProd(int id_prod, int n_ped);
//
//	void ComprobarStockPedido(int id_prod, int n_ped, int j, int i);
//
//	void ComprobarStockPedido();
//
//	void comprobarStockEs0(int id_prod, int id_alm);
//	//void crearProducto(char* nombre, char* descripcion, int categoria, int precio, char* tamanyo);
//	void editarPrecio(int id_prod, int precio);
//
	void insertarCliente(char *, char *, char*, int, int, char *);
//
//	void MostrarClientes();
//
//	int comprobarAlmacen(int id_alm);
//
Producto comprobarProducto(int id_prod);
//
//	int comprobarCiudad(int cod_ciu);
//
//	int comprobarCategoria(int cod_cat);
//
//	void listaCategorias();
//
//	void BorrarStock(int id_prod);
//
//	void BorrarProdCompra(int id_prod);

#endif /* FUNCIONES_FUNCIONESBD_H_ */
