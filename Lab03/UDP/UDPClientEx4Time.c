#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

int main(int argc,char** argv){
	int sockfd,n;
	struct sockaddr_in serverAddress;
	char* sendLine="Hi! I am a UDP client. Send time!";
	char receiveLine[1000];
	if(argc!=2){
		printf("usage: %s <IP address>\n",argv[0] );
		return -1;
	}
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	bzero(&serverAddress,sizeof(serverAddress));
	serverAddress.sin_family=AF_INET;
	serverAddress.sin_addr.s_addr=inet_addr(argv[1]);
	serverAddress.sin_port=htons(32000);
	sendto(sockfd,sendLine,strlen(sendLine),0,(struct sockaddr*)&serverAddress,sizeof(serverAddress));

	while(1){
		n=recvfrom(sockfd,receiveLine,1000,0,NULL,NULL);
		receiveLine[n]=0;
		//recieve from server and print
		printf("Received: %s\n", receiveLine);
	}
	return 0;
}