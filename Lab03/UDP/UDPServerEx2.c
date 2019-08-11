/*
Comment are made by E/15/385 
to make the code more understandable
*/
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdio.h>

int main(int argc, char**argv)
{
int sockfd,n;
struct sockaddr_in servaddr, cliaddr;
socklen_t len;
char mesg[1000];
char* banner = "Hello UDP client! This is UDP server";


sockfd=socket(AF_INET,SOCK_DGRAM,0);//create unbound socket in the specified domain. REturns socket file descriptor
/*
Arguments :
domain – Specifies the communication
domain ( AF_INET for IPv4/ AF_INET6 for IPv6 )
type – Type of socket to be created
( SOCK_STREAM for TCP / SOCK_DGRAM for UDP )
protocol – Protocol to be used by socket.
0 means use default protocol for the address family
*/
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
servaddr.sin_port=htons(32000);
bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
//Assigns address to the unbound socket.
/*
sockfd – File descriptor of socket to be binded
addr – Structure in which address to be binded to is specified
addrlen – Size of addr structure
*/
//to make the server infinite
while(1){
len = sizeof(cliaddr);
n = recvfrom(sockfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&len);
///Receive a message from the socket./
/*

sockfd – File descriptor of socket
buf – Application buffer in which to receive data
len – Size of buf application buffer
flags – Bitwise OR of flags to modify socket behaviour
src_addr – Structure containing source address is returned
addrlen – Variable in which size of src_addr structure is returned
*/


//////////////////////////EX2 ANSWER/////////////////////////////////////////
/*
MAKE THIS MESG RECIVED FROM THE CLIENT INTO THE SEND TO 
SO THAT MESG WILL BE SENT BACK TO THE CLIENT
*/
mesg[n] = '\0';
sendto(sockfd,mesg,n,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
//Send a message on the socket
/*
Arguments :
sockfd – File descriptor of socket
buf – Application buffer containing the data to be sent
len – Size of buf application buffer
flags – Bitwise OR of flags to modify socket behaviour
dest_addr – Structure containing address of destination
addrlen – Size of dest_addr structure
*/

printf("Received: %s\n",mesg);

}//end of while
return 0;
}