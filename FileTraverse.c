#include "FileTraverse.h"

void printhelp(){
    printf("Hw2 [options] [target]\n");
    printf("Options:\n");
    printf("-f <string pattern> <depth>\tlist all files that satisfy string pattern and depth\n");
    printf("-s <string size>           \tlist all files with file size less than or equal to the value\n");
    printf("-S                         \tlist all files along with size, permissions, and last access time\n");
}

void FilesTraverse(char *Path, bool f_flag,bool s_flag,bool S_flag,char *f_argSubString, int depth, int fileSize){
    int i=0;
}