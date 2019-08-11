#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>


int main(int argc,char **argv){
	int sockfd,n=10;
	struct sockaddr_in serverAddress,clientAddress;
	socklen_t length;
	char message[1000];
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	serverAddress.sin_family=AF_INET;
	serverAddress.sin_addr.s_addr=htonl(INADDR_ANY);
	serverAddress.sin_port=htons(32000);
	bind(sockfd,(struct sockaddr *)&serverAddress,sizeof(serverAddress));	
	length=sizeof(clientAddress);
	recvfrom(sockfd,message,1000,0,(struct sockaddr*)&clientAddress,&length);

	time_t current_time;
	struct tm * time_info;
	char timeString[8];
	char timeOldString[8];

	while(1){

		strcpy(timeOldString,timeString);
		time(&current_time);
		time_info = localtime(&current_time);
		strftime(timeString, 9, "%H:%M:%S", time_info);
		if(timeOldString[7]!=timeString[7]){
			sendto(sockfd,timeString,n,0,(struct sockaddr*)&clientAddress,sizeof(clientAddress));	
			printf("Sent : %s\n",timeString);	
		}
	}

	return 0;
}