#include <stdio.h>
#include <signal.h>
void myInterruptHandler (int signum)
{ 
    printf("You pressed ctrl+c, but I don't care!\n");
}
int main()
{
    for(;;)
    {
        if(signal(SIGINT, myInterruptHandler)==SIG_IGN)
        signal(SIGINT, SIG_IGN);
    }
}