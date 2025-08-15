#include <stdio.h> 
#include <arpa/inet.h> //for socket functions
#include <unistd.h> //for close(), read() and write() functions

int main() {
	int sock = socket(AF_INET, SOCK_STREAM, 0); //Initialize TCP connection
	struct sockaddr_in serv = {0}; //removes any garbage value in the memory

	serv.sin_family = AF_INET; //for IPv4
	serv.sin_port = htons(5842); //port no. for the challenge
	inet_pton(AF_INET, "13.48.176.69", &serv.sin_addr); //converting IP into binary and storing into serv.sin_addr (just do "host vortex.labs.overthewire.org" to get the IP)

	connect(sock, (struct sockaddr *) &serv, sizeof(serv)); //making a connection with the server

	uint32_t nums[4], sum = 0; //creating an array to store 4 unsigned integers (uint32_t = unsigned integer of 32 bits)
	recv(sock, nums, sizeof(nums), MSG_WAITALL); //receive exact size of bytes from server and wait untill all data is received

	for (int i=0; i<4; i++) sum += nums[i]; //loop through the 4 integers and add them
	send(sock, &sum, sizeof(sum), 0); //send the sum to the server so that the server can check

	char buffer[1024] = {0}; //making a storage to store the message from the server 
	recv(sock, buffer, sizeof(buffer)-1, 0); //receive exactly 1023 bytes and leave a byte for the null terminator 
	printf("%s", buffer);

	return 0;
}

