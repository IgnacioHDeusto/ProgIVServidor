#include <stdio.h>
#include <winsock2.h>
#include "math.h"
#include "BD/funcionesBD.h"
#include "string.h"
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

int main(){
		WSADATA wsaData;
		SOCKET conn_socket;
		SOCKET comm_socket;
		struct sockaddr_in server;
		struct sockaddr_in client;
		char sendBuff[512], recvBuff[512];

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
					strcpy(recvBuff, "La contraseña es correcta");
					sprintf(sendBuff, "La contraseña es correcta");
				} else {
					strcpy(recvBuff, "La contraseña es incorrecta");
					sprintf(sendBuff, "La contraseña es incorrecta");
				}
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Response sent: %s \n", sendBuff);
				fflush(stdout);
			}

		} while (1);

		// CLOSING the sockets and cleaning Winsock...
		closesocket(comm_socket);
		WSACleanup();

		return 0;
	return 1;
}
