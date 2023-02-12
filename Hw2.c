#include "Hw2.h"

int main (int argc, char **argv)
{
    bool f_flag=false,s_flag=false,S_flag=false;
    int Searchdepth,fileSize,argIndex=0;
    char *SearchSubString,*RootDrectory;
    char argParse;
    struct stat dir_state;

    for ( int index = 1; index < argc; index++)
    {
        if (stat(argv[index], &dir_state) != 0){
            if (S_ISDIR(dir_state.st_mode)){
                RootDrectory = argv[index];
            }
        }
    }

    while((argParse = getopt (argc, argv, "s:Sf:h")) != -1){
        switch(argParse){
            case 'f':
                f_flag = true;
                SearchSubString = argv[optind-1];
                if(argv[optind] == 0||atoi(argv[optind])==0){
                    printf("depth of the search not specified\n");
                    printhelp();
                    return 0;
                }
                if(atoi(argv[optind])==0){
                    printf("depth of the search not specified\n");
                    printhelp();
                    return 0;
                }
                Searchdepth = atoi(argv[optind]);
                break;
            case 's':
                s_flag = true;
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
}