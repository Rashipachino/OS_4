// #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <assert.h>
#define PORT 3490

int main() {
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
    send(sock, "TOP", sizeof("TOP"), 0); //top should be "hello world"
    recv(sock, text, 1025, 0);
    assert(strcmp(text, "hello world!") == 0);
    send(sock, "PUSH second line in stack", sizeof("PUSH second line in stack"), 0); 
    send(sock, "TOP", sizeof("TOP"), 0); //top should be "second line in stack"
    recv(sock, text, 1025, 0);
    assert(strcmp(text, "second line in stack") == 0);
    send(sock, "POP", sizeof("POP"), 0); 
    send(sock, "TOP", sizeof("TOP"), 0); //top should be "hello world"
    recv(sock, text, 1025, 0);
    assert(strcmp(text, "hello world!") == 0);
    send(sock, "POP", sizeof("POP"), 0);   //nothing should be in stack
    send (sock, "TOP", sizeof("TOP"), 0); //should return error
    recv(sock, text, 1025, 0);
    assert(strcmp(text, "ERROR: cant top when stack is empty!") == 0);
    send(sock, "POP", sizeof("POP"), 0); //should return error
    recv(sock, text, 1025, 0);
    assert(strcmp(text, "ERROR: cant pop empty stack!") == 0);  
    send(sock, "PUSH she sells seashells by the sea shore", sizeof("PUSH she sells seashells by the sea shore"), 0);
    send(sock, "PUSH three smart fellows, they felt smart", sizeof("PUSH three smart fellows, they felt smart"), 0);
    send(sock, "PUSH the itsy bitsy spider", sizeof("PUSH the itsy bitsy spider"), 0);    
    send(sock, "TOP", sizeof("TOP"), 0); //top should  be "the itspy bitsy spider"
    recv(sock, text, 1025, 0);
    assert(strcmp(text, "the itsy bitsy spider") == 0);
    send(sock, "POP", sizeof("POP"), 0); 
    send(sock, "TOP", sizeof("TOP"), 0); //top should be "three smart fellows, they felt smart"
    recv(sock, text, 1025, 0);
    assert(strcmp(text, "three smart fellows, they felt smart") == 0);    
    send(sock, "POP", sizeof("POP"), 0); 
    send(sock, "TOP", sizeof("TOP"), 0); //top should be "she sells seashells by the sea shore"
    recv(sock, text, 1025, 0);
    assert(strcmp(text, "she sells seashells by the sea shore") == 0);
    send(sock, "EXIT", sizeof("EXIT"), 0);
    close(sock);

    return 0;


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

}
