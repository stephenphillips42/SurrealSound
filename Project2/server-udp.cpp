// Server code for electronic voting system
// Author: Stephen Phillips
// PennKey: stephi
// PennID: 14378269
#include "server.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

// Network related things
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

using namespace std;

void errorexit(const char *msg);
#define MAXSIZE 512

// Run the server
int main(int argc, char *argv[]) {
	// General idea:
	// Create socket with port 8269 (datagram, INET?)
	// Use select to wait for something to come
	// When something does come, check the packet and process it accordingly
	cout << "Hello world" << endl;

	// Get hint for the input address
	addrinfo hints;
	hints.ai_flags = AI_PASSIVE; // Whatever our current IP address is
	hints.ai_family = AF_UNSPEC; // IPv4 or IPv6, whatever it wants
	hints.ai_socktype = SOCK_DGRAM; // We are using datagrams
	hints.ai_protocol = 0; // Don't care about the protocol
	hints.ai_addrlen = 0; // Don't care about any of these
	hints.ai_addr = NULL;
	hints.ai_canonname = NULL;
	hints.ai_next = NULL;
	// Get our IP address
	addrinfo *serveraddr;
	if (getaddrinfo(NULL,"8269",&hints,&serveraddr) < 0) {
		perror("Unable to get own IP address");
		exit(EXIT_FAILURE);
	}
	// OK so technically this returns a list - I'll ignore them and just use
	// the first one returned

	// Set up the socket
	int ssocket = 0; // Server Socket
	if ((ssocket = socket(PF_INET,SOCK_DGRAM,0)) < 0) {
		perror("Socket unable to connect");
		exit(EXIT_FAILURE);
	}
	// Now get IP address and such
	if((bind(ssocket, serveraddr->ai_addr, serveraddr->ai_addrlen))<0) {
		perror("Socket unable to bind");
		exit(EXIT_FAILURE);
	}
	// Main loop
	// How many bytes we received
	int nbytes = 0;
	// Client address information
	sockaddr_storage clientaddr;
	socklen_t addrlen = 0;
	// Client message
	char message[MAXSIZE];
	while(true) { // Loop forever...
		// Wait for a datagram.
		addrlen = sizeof(clientaddr);
		if ((nbytes = recvfrom(ssocket, message, MAXSIZE, 0,
											(sockaddr*)&clientaddr, &addrlen)) < 0) {
			errorexit("Trouble receiving data");
		}

		/* Give a diagnostic message. */
		fprintf(stderr, "Server: got message: %s\n", message);

		/* Bounce the message back to the sender. */
		if (sendto(ssocket, message, nbytes, 0,
								(sockaddr*)&clientaddr, addrlen) != nbytes) {
			errorexit("Trouble sending data");
		}
	}

	close(ssocket);
}

void errorexit(const char *msg) {
	perror (msg);
	exit (EXIT_FAILURE);
}
