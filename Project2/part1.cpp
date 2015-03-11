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
#include <arpa/inet.h>

using namespace std;


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
	if (getaddrinfo(NULL,"2020",&hints,&serveraddr) < 0) {
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
	int nbytes = 0;
	while(true) {
		/* Wait for a datagram. */
		size = sizeof (name);
		nbytes = recvfrom (ssocket, message, MAXMSG, 0, (sockaddr*) & name, &size);
		if (nbytes < 0) {
			perror ("recfrom (server)");
			exit (EXIT_FAILURE);
		}

		/* Give a diagnostic message. */
		fprintf (stderr, "Server: got message: %s\n", message);

		/* Bounce the message back to the sender. */
		nbytes = sendto (sock, message, nbytes, 0, (sockaddr*) & name, size);
		if (nbytes < 0) {
			perror ("sendto (server)");
			exit (EXIT_FAILURE);
		}
	}


}
