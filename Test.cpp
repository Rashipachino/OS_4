#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <iostream>
#include <stdexcept>
#include "doctest.h"

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 3490

TEST_CASE("checking stack functions") {
    int sock = 0, valread;
	struct sockaddr_in serv_addr;
	char buffer[1024] = { 0 };
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary
	// form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
		<= 0) {
		printf(
			"\nInvalid address/ Address not supported \n");
	}

	if (connect(sock, (struct sockaddr*)&serv_addr,
				sizeof(serv_addr))
		< 0) {
		printf("\nConnection Failed \n");
	}

    char text[1025];

    send(sock, "PUSH hello world!", sizeof("PUSH hello world!"), 0);
    send(sock, "TOP", sizeof("TOP"), 0);
    recv(sock, text, 1025, 0);
    CHECK_EQ(strcmp(text, "hello world!"), 0);

    send(sock, "EXIT", sizeof("EXIT"), 0);




    // char input[1030];
    // char text[1025];
    // while(1) {
	// 	printf("INPUT: ");
    //     fgets(input, 1030, stdin);
	// 	input[strlen(input) - 1] = 0;
	// 	if(strncmp(input, "EXIT", 4) == 0) {
	// 		if(send(sock, "EXIT", sizeof("EXIT"), 0) < 0) {
    //         	perror("ERROR: sending input");
    //     	}
	// 		break;
	// 	}
    //     if(send(sock, input, sizeof(input), 0) < 0) {
    //         perror("ERROR: sending input");
    //     }
    //     else {
    //         if(strncmp(input, "TOP", 3) == 0) {
    //             if(recv(sock, text, 1025, 0) < 0) {
    //                 perror("ERROR: recieving");
    //             }
    //             else {
    //                 printf("OUTPUT: %s\n", text);
    //             }
    //         }
    //     }
    // }

	close(sock);

}