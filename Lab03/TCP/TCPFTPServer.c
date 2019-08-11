/* Sample TCP server */

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char**argv)
{
int listenfd,connfd,n;
struct sockaddr_in servaddr,cliaddr;
socklen_t clilen;
//char* banner = "Hello TCP client! This is TCP server";// we dont need banner

//step size should be 1000
int stepSize=1000;

//to send file to Client we need an buffer
char outBuffer[1000];

//to tkae inputs from clients we need a buffer
char inBuffer[1000];

//read the file into a buffer
int fileSize=0;
char file[1000000];//bigger buffer to store the file
char letter,symbol;

//create file pointer and read the file to buffer

FILE *fp = fopen("serverFile.txt", "r");
    if(fp != NULL){
        while((symbol = getc(fp)) != EOF){
            file[fileSize]= symbol;
            fileSize++;
        }
        fclose(fp);
    }

//now we know the size of the file as FileSize and we have stored it in file buffer





/* one socket is dedicated to listening */
//stream for TCP is used
listenfd=socket(AF_INET,SOCK_STREAM,0);


/* initialize a sockaddr_in struct with our own address information for
binding the socket */
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
servaddr.sin_port=htons(32000);


/* binding */
/*basically registers that the socket is
using that IP address. Since the server is the initial receiver of the data, this is an essential step
*/
bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
listen(listenfd,0);
clilen=sizeof(cliaddr);


/* accept the client with a different socket. */
connfd = accept(listenfd,(struct sockaddr *) &cliaddr, &clilen); // the uninitialized cliaddr variable is filled in with the

printf("waits till client requests for file...");

//server should wait infinitely so use loop

while(1){

n = recvfrom(connfd,inBuffer,1000,0,(struct sockaddr *)&cliaddr,&clilen);//information of the client by recvfrom function
//check what is requested .Here only one file. So check the pre determined word is there

if(strcmp("request",inBuffer)==0){
          //now serverFile.txt is requested which is on file buffer
    //first we should send file size
    printf("sending file size measure to the client...");
     //use another buffer
    sprintf(outBuffer,"%d \n",fileSize);
    sendto(connfd,outBuffer,strlen(outBuffer),0,(struct sockaddr
*)&cliaddr,sizeof(cliaddr));

    int a=0,b=0;

//we should send blocks of 1000

  while(a<fileSize){
     for(b=0;b<stepSize && a<fileSize;b++){
         //assign outbuffer from characters in file we read
         outBuffer[b]=file[a++];//increment i
         }
      //close buffer with termination
    outBuffer[b]=0;

   printf("Sending block : %s \n",outBuffer);
   sendto(connfd,outBuffer,strlen(outBuffer),0,(struct sockaddr
*)&cliaddr,sizeof(cliaddr));

   //confirm of recieval

   n = recvfrom(connfd,inBuffer,1000,0,(struct sockaddr *)&cliaddr,&clilen);//information of the client by recvfrom function
inBuffer[n] = 0;
printf("Received:%s\n",inBuffer); 

    
   }//end of sending
   return 0;//if successfully reached here return 0 to close the server


                                  }

}//end of while


/*n = recvfrom(connfd,buffer,1000,0,(struct sockaddr *)&cliaddr,&clilen);//information of the client by recvfrom function
buffer[n] = 0;
sendto(connfd,banner,strlen(banner),0,(struct sockaddr
*)&cliaddr,sizeof(cliaddr));
printf("Received:%s\n",buffer);*/
return 0;
}
