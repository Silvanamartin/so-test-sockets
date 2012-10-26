#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


//#define DIRECCION "192.168.1.1"
#define DIRECCION INADDR_ANY   //INADDR_ANY representa la direccion de cualquier
							   //interfaz conectada con la computadora
#define PUERTO 5000
#define BUFF_SIZE 1024


int main() {

	int socketEscucha, socketNuevaConexion;
	int nbytesRecibidos;

	struct sockaddr_in socketInfo;
	char buffer[BUFF_SIZE];

	// Crear un socket:
	// AF_INET: Socket de internet IPv4
	// SOCK_STREAM: Orientado a la conexion, TCP
	// 0: Usar protocolo por defecto para AF_INET-SOCK_STREAM: Protocolo TCP/IPv4
	if ((socketEscucha = socket(AF_INET, SOCK_STREAM, 0)) != 0) {

		socketInfo.sin_family = AF_INET;
		socketInfo.sin_addr.s_addr = inet_addr("127.0.0.1");
		socketInfo.sin_port = htons(5000);

// Vincular el socket con una direccion de red almacenada en 'socketInfo'.
		if (bind(socketEscucha, (struct sockaddr*) &socketInfo,
				sizeof(socketInfo)) == 0) {

// Escuchar nuevas conexiones entrantes.
			if (listen(socketEscucha, 10) == 0) {

				printf("Escuchando conexiones entrantes.\n");

// Aceptar una nueva conexion entrante. Se genera un nuevo socket con la nueva conexion.
				if ((socketNuevaConexion = accept(socketEscucha, NULL, 0))
						>= 0) {

// Recibir hasta BUFF_SIZE datos y almacenarlos en 'buffer'.
					if ((nbytesRecibidos = recv(socketNuevaConexion, buffer,
							BUFF_SIZE, 0)) > 0) {

						printf("Mensaje recibido: \"%s\"\n", buffer);
						printf("Tamanio del buffer %d bytes!\n", nbytesRecibidos);

					} else {
						perror("Error al recibir datos");
					}

				} else {
					perror("Error al aceptar conexion entrante");
				}

			} else {
				perror("Error al poner a escuchar socket");
			}

		} else {
			perror("Error al bindear socket escucha");
		}

	} else {
		perror("socket");
	}


	return EXIT_SUCCESS;
}
