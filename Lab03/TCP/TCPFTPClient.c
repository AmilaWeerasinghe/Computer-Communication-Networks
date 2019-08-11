/* Sample TCP client */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char**argv)
{
int sockfd,n;
struct sockaddr_in servaddr;
//char banner[] = "Hello TCP server! This is TCP client";//we dont need banner,because testing has been done


//to store 1000 words at a time  we need char buffer[1001] for 1000 characters expec the null terminatiom
//buffer to get 1000 chars from server 
char inBuffer[1000];

//we need another buffer to write request to server
char outBuffer[1000];//given large size for larger requests

//we need file size
int fileSize=0;

if (argc != 2)
{
printf("usage: ./%s <IP address>\n",argv[0]);
return -1;
}


/* socket to connect *///for tcp sock stream is used
sockfd=socket(AF_INET,SOCK_STREAM,0);


/* IP address information of the server to connect to */
servaddr.sin_family = AF_INET;//ip V4
servaddr.sin_addr.s_addr=inet_addr(argv[1]);//address trnaslated to socket input
servaddr.sin_port=htons(32000);

//trying to connect to server
printf("Request to connect to server is sent by client..\n");
connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

//connection was accepted by server
printf("Connection was accepted by the server..\n");

//now send the request string
printf("request to serverFile.txt is sending..\n");
//outBuffer is used and for only given file request was sent as string named request
sprintf(outBuffer, "%s","request");

sendto(sockfd,outBuffer,strlen(outBuffer),0, (struct sockaddr *)&servaddr,sizeof(servaddr));



//first we need the size of file
printf("Waiting for the size of the file from the server..");
//take the input size from inbuffer
n=recvfrom(sockfd,inBuffer,10000,0,NULL,NULL);
//convert to int and store as file size
fileSize=atoi(inBuffer);

printf("file size is %d",fileSize);

while(fileSize>0){

//take input to inBuffer 
n=recvfrom(sockfd,inBuffer,10000,0,NULL,NULL);
inBuffer[n]=0;
//print inBuffer
printf("block size recieved  = %d\n",n );
printf("%s  \n",inBuffer);




fileSize -= n; //reduce fileSize by the amount recieved

// send a recieval confirmation to server in each step 
        sprintf(outBuffer, "%s", "done");
        sendto(sockfd,outBuffer,strlen(outBuffer),0, (struct sockaddr *)&servaddr,sizeof(servaddr));

}



return 0 ;
}
