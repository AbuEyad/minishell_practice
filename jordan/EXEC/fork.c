#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main()
{
    if(fork()) {
        printf("parent\n");
    } else {
        printf("child\n");  
    }
}