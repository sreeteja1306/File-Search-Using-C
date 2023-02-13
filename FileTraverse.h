#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>

void printhelp();
int count_tabs(char *path);
void FilesTraverse(char *Path, bool f_flag,bool s_flag,bool S_flag,char *f_argSubString, int depth, int fileSize,int curr_depth);