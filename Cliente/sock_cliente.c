#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define DIRECCION "127.0.0.1"
#define PUERTO 5000
#define BUFF_SIZE 1024

int main() {

	int unSocket;

	struct sockaddr_in socketInfo;
	char buffer[BUFF_SIZE];

	printf("Conectando...\n");

// Crear un socket:
// AF_INET: Socket de internet IPv4
// SOCK_STREAM: Orientado a la conexion, TCP
// 0: Usar protocolo por defecto para AF_INET-SOCK_STREAM: Protocolo TCP/IPv4
	if ((unSocket = socket(AF_INET, SOCK_STREAM, 0)) != 0) {

		socketInfo.sin_family = AF_INET;
		socketInfo.sin_addr.s_addr = inet_addr(DIRECCION );
		socketInfo.sin_port = htons(PUERTO);

// Conectar el socket con la direccion 'socketInfo'.
		if (connect(unSocket, (struct sockaddr*) &socketInfo,
				sizeof(socketInfo)) == 0) {

			printf("Conectado!\n");
			scanf("%s", buffer);

// Enviar los datos leidos por teclado a traves del socket.
			if (send(unSocket, buffer, BUFF_SIZE, 0) >= 0) {
				printf("Datos enviados!\n");
			} else {
				perror("Error al enviar datos");
			}

		} else {
			perror("Error al conectar socket");
		}
	} else {
		perror("Error al crear socket");
	}


	return EXIT_SUCCESS;

}
