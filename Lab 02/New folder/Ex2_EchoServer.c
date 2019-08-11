/* 	Ex-2 Server
	CO323
	E/14/158 gihanchanaka@gmail.com
	15-02-2018
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdio.h>

int main(int argc,char **argv){
	int sockfd,n;
	struct sockaddr_in serverAddress,clientAddress;
	socklen_t length;
	char message[1000];
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	serverAddress.sin_family=AF_INET;
	serverAddress.sin_addr.s_addr=htonl(INADDR_ANY);
	serverAddress.sin_port=htons(32000);
	bind(sockfd,(struct sockaddr *)&serverAddress,sizeof(serverAddress));	
	length=sizeof(clientAddress);
	while(1){
		n=recvfrom(sockfd,message,1000,0,(struct sockaddr*)&clientAddress,&length);
		message[n]=0;
		sendto(sockfd,message,n,0,(struct sockaddr*)&clientAddress,sizeof(clientAddress));	
		printf("Recieved and echoed: %s\n",message);
	}
	return 0;
}