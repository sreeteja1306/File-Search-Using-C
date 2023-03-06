#include "FileTraverse.h"

int main (int argc, char **argv)
{
    struct searchArgs *ParsedArgs;
    char *RootDrectory= ".";
    char argParse;
    struct stat dir_state;

    DEFAULT_SEARCHARGS(ParsedArgs);

    for ( int index = 1; index < argc; index++)
    {
        if (stat(argv[index], &dir_state) == 0){
            if (S_ISDIR(dir_state.st_mode)){
                RootDrectory = argv[index];
            }
        }
    }


    while((argParse = getopt(argc, argv, "s:Sf:e:E:t:h")) != -1){
        switch(argParse){
            case 'f':
                ParsedArgs->f_flag = true;
                ParsedArgs->SubString = argv[optind-1];
                if(argv[optind] == 0 || atoi(argv[optind])==0){
                    printf("*** invalid optional argument specified for -- \"f\" ****\n");
                    printhelp();
                    return 0;
                }
                ParsedArgs->depth = atoi(argv[optind]);
                break;
            case 's':
                ParsedArgs->s_flag = true;
                if(atoi(optarg)==0){
                    printf("*** invalid optional argument specified for -- \"s\" ****\n");
                    printhelp();
                    return 0;
                }
                ParsedArgs->MaxSize=atoi(optarg);
                break;
            case 't':
                ParsedArgs->t_flag = true;
                ParsedArgs->t_arg=optarg[0];
                break;
            case 'S':
                ParsedArgs->S_flag = true;
                break;
            case 'e':
                ParsedArgs->e_flag = true;
                ParsedArgs->e_cmd=optarg;
                break;
            case 'E':
                ParsedArgs->E_flag = true;
                ParsedArgs->E_cmd=optarg;
                EcmdParser(ParsedArgs->E_cmd,false);
                break;
            case 'h':
                printhelp();
                break;
            case '?':
                printhelp();
            default:
                abort();
        }
    }
    FilesTraverse(RootDrectory,ParsedArgs,0);
    if(ParsedArgs->E_flag){
        char **cmd;
        cmd = EcmdParser("",true);
        executeCmd(cmd);
    }
    free(ParsedArgs);
}