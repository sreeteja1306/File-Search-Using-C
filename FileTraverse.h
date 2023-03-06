#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

#define DEFAULT_SEARCHARGS(X) {\
                            X = (struct searchArgs *) malloc(sizeof( struct searchArgs));\
                            X->f_flag = false;\
                            X->s_flag = false;\
                            X->S_flag = false;\
                            X->t_flag = false;\
                            X->e_flag = false;\
                            X->E_flag = false;\
                            X->t_arg = 0;\
                            X->e_cmd = "";\
                            X->E_cmd = "";\
                            X->SubString = "";\
                            X->depth = 100;\
                            X->MaxSize = -1;\
                            }

struct searchArgs{
    bool f_flag; 
    bool s_flag;
    bool t_flag;
    bool S_flag;
    bool e_flag;
    bool E_flag;
    int t_arg;
    char *e_cmd;
    char *E_cmd;
    char *SubString;
    unsigned int depth;
    int MaxSize;
};

void printhelp();
void FilesTraverse(char *Path,struct searchArgs *Args,int curr_depth);
char **EcmdParser(char *opt,bool get);
void executeCmd(char **cmd);