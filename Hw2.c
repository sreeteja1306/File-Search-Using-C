#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>

int main (int argc, char **argv)
{
    int c;
    while((c = getopt (argc, argv, "sSf:")) != -1){
        printf("%s",c);
    }
}