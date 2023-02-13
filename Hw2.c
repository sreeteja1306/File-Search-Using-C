#include "FileTraverse.h"

int main (int argc, char **argv)
{
    bool f_flag=false,s_flag=false,S_flag=false;
    int depth,fileSize;
    char *SubString,*RootDrectory= "..";
    char argParse;
    struct stat dir_state;
    int curr_depth=0;
    for ( int index = 1; index < argc; index++)
    {
        if (stat(argv[index], &dir_state) == 0){
            if (S_ISDIR(dir_state.st_mode)){
                RootDrectory = argv[index];
            }
        }
    }
    while((argParse = getopt (argc, argv, "s:Sf:h")) != -1){
        switch(argParse){
            case 'f':
                f_flag = true;
                SubString = argv[optind-1];
                if(argv[optind] == 0||atoi(argv[optind])==0){
                    printf("*** invalid optional argument specified for -- \"f\" ****\n");
                    printhelp();
                    return 0;
                }
                depth = atoi(argv[optind]);
                break;
            case 's':
                s_flag = true;
                if(atoi(optarg)==0){
                    printf("*** invalid optional argument specified for -- \"s\" ****\n");
                    printhelp();
                    return 0;
                }
                fileSize=atoi(optarg);
                break;
            case 'S':
                S_flag = true;
                break;
            case 'h':
                printhelp();
                break;
            case '?':
                printhelp();
        }
    }
    FilesTraverse(RootDrectory, f_flag, s_flag, S_flag, SubString, depth, fileSize,curr_depth);
}