/* Not stdio.h */
#include <unistd.h>
 
void main()
{
    char str[100];
 
    /*Write on screen*/
    write(1,"\nType Something : ",17);
 
    /*Read at most 100 chars from console into 'str' */
    read(0,str,100);
 
    write(1,"\nYou typed :\n",13);
 
    /*write 10 chars from 'str' to screen */
    write(1,str,10);
 
    /*newline*/
    write(1,"\n",1);
}