#include <stdio.h>
#include <winsock2.h>
#include "math.h"
#include "BD/funcionesBD.h"
#include "string.h"
#include <iostream>
#include "datos/Producto/Producto.h"
#include "datos/Producto/Categoria.h"
#include "datos/Producto/Carrito.h"
#include "datos/Pedido/Pedido.h"
using namespace std;

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

int main(){
		WSADATA wsaData;
		SOCKET conn_socket;
		SOCKET comm_socket;
		struct sockaddr_in server;
		struct sockaddr_in client;
		char sendBuff[512], recvBuff[512];
		Carrito carrito;

		printf("\nInitialising Winsock...\n");
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
			printf("Failed. Error Code : %d", WSAGetLastError());
			return -1;
		}

		printf("Initialised.\n");

		//SOCKET creation
		if ((conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
			printf("Could not create socket : %d", WSAGetLastError());
			WSACleanup();
			return -1;
		}

		printf("Socket created.\n");

		server.sin_addr.s_addr = inet_addr(SERVER_IP);
		server.sin_family = AF_INET;
		server.sin_port = htons(SERVER_PORT);

		//BIND (the IP/port with socket)
		if (bind(conn_socket, (struct sockaddr*) &server,
				sizeof(server)) == SOCKET_ERROR) {
			printf("Bind failed with error code: %d", WSAGetLastError());
			closesocket(conn_socket);
			WSACleanup();
			return -1;
		}

		printf("Bind done.\n");

		//LISTEN to incoming connections (socket server moves to listening mode)
		if (listen(conn_socket, 1) == SOCKET_ERROR) {
			printf("Listen failed with error code: %d", WSAGetLastError());
			closesocket(conn_socket);
			WSACleanup();
			return -1;
		}

		//ACCEPT incoming connections (server keeps waiting for them)
		printf("Waiting for incoming connections...\n");
		int stsize = sizeof(struct sockaddr);
		comm_socket = accept(conn_socket, (struct sockaddr*) &client, &stsize);
		// Using comm_socket is able to send/receive data to/from connected client
		if (comm_socket == INVALID_SOCKET) {
			printf("accept failed with error code : %d", WSAGetLastError());
			closesocket(conn_socket);
			WSACleanup();
			return -1;
		}
		printf("Incomming connection from: %s (%d)\n", inet_ntoa(client.sin_addr),
				ntohs(client.sin_port));

		// Closing the listening sockets (is not going to be used anymore)
		closesocket(conn_socket);

		//SEND and RECEIVE data
		printf("Waiting for incoming messages from client... \n");

		iniciarBD();
		do {
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			printf("Command received: %s \n", recvBuff);
			fflush(stdout);

			if (strcmp(recvBuff, "RegistrarCliente") == 0){
				char dni[10];
				char nombre[20];
				char dir[30];
				int tlf;
				int cod_ciu;
				char contrasena[30];

				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				strcpy(dni, recvBuff);
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				strcpy(nombre, recvBuff);
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				strcpy(dir, recvBuff);
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				tlf= atoi(recvBuff);
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				cod_ciu= atoi(recvBuff);
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				strcpy(contrasena, recvBuff);

				insertarCliente(dni, nombre, dir, tlf, cod_ciu, contrasena);
				strcpy(recvBuff, "Registro exitoso");
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Response sent: %s \n", sendBuff);
				fflush(stdout);
			}

			if (strcmp(recvBuff, "ComprobarCliente") == 0){
				char dni[10];
				char contrasena[30];
				int comprueba;

				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				strcpy(dni, recvBuff);
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				strcpy(contrasena, recvBuff);

				comprueba = comprobarUsuario(dni, contrasena);
				if (comprueba == 1) {
					strcpy(recvBuff, "Contraseña OK");
					sprintf(sendBuff, "La contraseña es correcta");
				} else {
					strcpy(recvBuff, "Contraseña MAL");
					sprintf(sendBuff, "La contraseña es incorrecta");
				}
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Response sent: %s \n", sendBuff);
				fflush(stdout);
			}
			if (strcmp(recvBuff, "MostrarProductos") == 0){
				int tam = ListaProductos();
				Producto** productos = new Producto*[tam];

				productos = Productos();

				for (int i = 0; i < tam; ++i) {
					sprintf(sendBuff, "%d", productos[i]->id_prod);
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);
					strcpy(sendBuff, productos[i]->nombre);
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);
					strcpy(sendBuff, productos[i]->descripcion);
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);
					sprintf(sendBuff, "%d", productos[i]->cod_cat);
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);
					sprintf(sendBuff, "%d", productos[i]->precio);
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);
					strcpy(sendBuff, productos[i]->tamanyo);
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				}
				if (tam == 0) {
					strcpy(sendBuff, "TAMANYO 0");
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				}
				if (tam != 0) {
					strcpy(sendBuff, "TAMANYO > 0");
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);
					printf("Response sent: %d productos \n", tam);
				}
			}
			if (strcmp(recvBuff, "AnadirProducto") == 0){
				int id;
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				id= atoi(recvBuff);
				if (id == -1) {
					strcpy(sendBuff, "NO EXISTE PROD");
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				} else {
					Producto prod = comprobarProducto(id);
					carrito.AnadirProd(prod);
					strcpy(sendBuff, "Producto anadido");
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);
					printf("Response sent: PA \n");
					fflush(stdout);
				}


			}
			if (strcmp(recvBuff, "MostrarCarrito") == 0){

			}
			if (strcmp(recvBuff, "MostrarPedidos") == 0){

			}
			if (strcmp(recvBuff, "BorrarProductoCarrito") == 0){

			}
			if (strcmp(recvBuff, "ConfirmarCarrito") == 0){

			}
			if (strcmp(recvBuff, "EXIT") == 0)
						break;

		} while (1);

		// CLOSING the sockets and cleaning Winsock...
		closesocket(comm_socket);
		WSACleanup();

		return 0;
	return 1;
}
