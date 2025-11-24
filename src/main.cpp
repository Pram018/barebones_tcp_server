/*
 * Reference
 * Sloan kelly @ youtube
 */


#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>


int main() {
	
	// create a socket
	int listening = socket(AF_INET, SOCK_STREAM, 0);
	if(listening == -1) 
	{
		std::cerr << "Can't create a socket";
		return -1;
	}


	// bind the socket to the ip port
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	inet_pton(AF_INET,"127.0.0.1", &hint.sin_addr);

	if(bind(listening, (sockaddr*)&hint, sizeof(hint)) == -1) 
	{
		std::cerr << "Can,t bind to the IP/Port";
		return -2;
	}





	// mark the socket for listening in
	if(listen(listening, SOMAXCONN) == -1)	
	{
		std::cerr << "Can't listen";
		return -3;
	}

	// accept a call
	sockaddr_in client;
	socklen_t clientSize;
	char host[NI_MAXHOST]; //size of NI_MAXHOST = 1025
	char svc[NI_MAXSERV];

	int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
	if(clientSocket == -1) 
	{
		std::cerr << "Problem with client connecting";
		return -4;
	}
	
	// close the listening socket
	close(listening);
	
	memset(host, 0, NI_MAXHOST);
	memset(svc, 0, NI_MAXSERV);

	int result = getnameinfo((sockaddr*)&client, sizeof(client), host,NI_MAXHOST, svc, NI_MAXSERV, 0);

	if(result)
	{
		std::cout << host << "Connected on" << svc << std::endl;
	}
	else
	{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		std::cout << host << " connecting on" << ntohs(client.sin_port) << std::endl;
	}
	
	// while recieving display message, echo message
	char buf[4096];
	while(true)
	{
		// clear the buffer
		memset(buf, 0, 4096);
		
		// wait for message
		int bytesRecv = recv(clientSocket, buf, 4096, 0);
		if(bytesRecv == -1)
		{
			std::cerr << "There was a connection error" << std::endl;
			break;
		}

		if(bytesRecv == 0)
		{
			std::cout << "the client disconnected" << std::endl;
			break;
		}	

		// Display message	
		std::cout << "Recieved" << std::string(buf, 0, bytesRecv) << std::endl;

		// Resend message
		send(clientSocket, buf, bytesRecv + 1, 0);		

	}
	close(clientSocket);



	return 0;
} 
