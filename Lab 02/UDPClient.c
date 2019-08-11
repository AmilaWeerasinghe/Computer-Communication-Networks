/* Sample UDP client */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char**argv)
{
int sockfd,n;
struct sockaddr_in servaddr;
char sendline[] = "";//make sendline null initial
char recvline[1000];
//send data to client we need to receive a message from terminal
//also the loop should exist to communicate between server and client
if (argc != 2)
{
printf("usage: ./%s <IP address>\n",argv[0]);
return -1;
}
sockfd=socket(AF_INET,SOCK_DGRAM,0);
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr=inet_addr(argv[1]);
servaddr.sin_port=htons(32000);
sendto(sockfd,sendline,strlen(sendline),0,(struct sockaddr

*)&servaddr,sizeof(servaddr));

//keep echoing message from server we need a loop
while(1){
	bzero(sendline,100);//clear sendline in each loop
	bzero(recvline,100);//clear recvline in each loopp
	fgets(sendline,100,stdin);//recive input to sendline from terminal using stdin
n=recvfrom(sockfd,recvline,10000,0,NULL,NULL);
//write the sendline to send to client
write(1,sendline,strlen(sendline)+1);//length should be length of sendline
recvline[n]=0;
printf("Received: %s\n",recvline);

}
return 0;
}
