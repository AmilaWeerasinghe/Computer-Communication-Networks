/* 	Ex-3 UDP Client
	CO323
	E/14/158 gihanchanaka@gmail.com
	15-02-2018
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc,char** argv){
	int sockfd,n;
	struct sockaddr_in serverAddress;
	char* sendLine="Hello UDP Server! This is a client";
	char receiveLine[1000];
	if(argc!=3){
		printf("usage: %s <IP address> <NoOfLines>\n",argv[0] );
		return -1;
	}
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	bzero(&serverAddress,sizeof(serverAddress));
	serverAddress.sin_family=AF_INET;
	serverAddress.sin_addr.s_addr=inet_addr(argv[1]);
	serverAddress.sin_port=htons(32000);
	
	sendto(sockfd,argv[2],strlen(sendLine),0,(struct sockaddr*)&serverAddress,sizeof(serverAddress));
	n=recvfrom(sockfd,receiveLine,1000,0,NULL,NULL);
	receiveLine[n]=0;
	printf("Received: %s\n", receiveLine);	
	int i;
	char* inputLine;size_t len = 0;

	for(i=0;i<atoi(argv[2]);i++){
		getline(&inputLine, &len, stdin);
		//scanf("%[^\n]",inputLine);
		sendto(sockfd,inputLine,strlen(sendLine),0,(struct sockaddr*)&serverAddress,sizeof(serverAddress));
		n=recvfrom(sockfd,receiveLine,1000,0,NULL,NULL);
		receiveLine[n]=0;
		printf("Received: %s", receiveLine);
	}
	return 0;
}