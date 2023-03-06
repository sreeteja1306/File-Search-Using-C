#include "FileTraverse.h"

void ecmdParser(char *opt,char *path,char **cmd){
    int count = 0;
    char *commandLine = strdup(opt);
    commandLine = strtok(commandLine," ");
    while (commandLine != NULL){
        cmd[count++]=commandLine;
        commandLine = strtok(NULL, " ");}
    cmd[count++]=path;
    cmd[count++]=NULL;
}

char **EcmdParser(char *opt,bool get){
    static int count = 0;
    static char *cmd[1000];
    if(get){
        cmd[count++]=NULL;
        return cmd;
    }
    char *commandLine = strdup(opt);
    commandLine = strtok(commandLine," ");
    while (commandLine != NULL){
        cmd[count++]=commandLine;
        commandLine = strtok(NULL, " ");}
    return cmd;
}

void executeCmd(char **cmd){
    int forkid = fork();//printf("%s\n",fileLoc);
    if (forkid == 0){
        int status = execvp(cmd[0],cmd);
        if (status == -1)
        printf("error");
    }
    else if (forkid > 0) wait(NULL);
}

void printhelp(){
    printf("Hw2 [options] [target]\n");
    printf("Options:\n");
    printf("-f <string pattern> <depth>\tlist all files that satisfy string pattern and depth\n");
    printf("-s <string size>           \tlist all files with file size less than or equal to the value\n");
    printf("-S                         \tlist all files along with size, permissions, and last access time\n");
    printf("-e <UNIX CMD>              \tExecute the cmd on every file that match search criteria\n");
    printf("-E <UNIX CMD>              \tExecute the cmd on all the files that match search criteria\n");
}


const char* printFormat(bool show,int curr_depth){
    for(int i=0;i<curr_depth;i++) printf("\t");
    if(show) return "%s : (%d , %jo , %s)\n";
    else return "%s\n";
}

bool printfile(char *file,struct dirent *FileEntries,struct searchArgs *Args,int curr_depth,bool Show){
    bool printfile = true,printDiscription=false;
    struct stat st;
    int size=0;
    if (stat(file, &st) == -1)
    {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    if(Args->S_flag) printDiscription = true;

    if(Args->f_flag){
            if(!strstr(FileEntries->d_name,Args->SubString)) printfile = false;}
    
    if(FileEntries->d_type != DT_DIR){
        size = st.st_size;
        if(Args->s_flag){
            if(!(size<=Args->MaxSize)) printfile = false;}
    }
    
    if(Args->t_flag){
        switch(Args->t_arg){
            case 'f':
                if(FileEntries->d_type != DT_REG)printfile = false;
                break;
            case 'd':
                if(FileEntries->d_type != DT_DIR)printfile = false;
                break;
        }
    }


    if(printfile && Show){
        printf(printFormat(printDiscription,curr_depth),FileEntries->d_name,size,(uintmax_t) st.st_mode,strtok(ctime(&st.st_atime),"\n"));
    }

    return printfile;
}

void FilesTraverse(char *Path,struct searchArgs *Args,int curr_depth){
    struct dirent *FileEntries;
    char *fileLoc = malloc(100*sizeof(char));
    DIR *Folder = opendir(Path);
    

    if(Folder != NULL){
        while((FileEntries = readdir(Folder) ) != NULL){
            
           if(strcmp(FileEntries->d_name, ".") != 0 && strcmp(FileEntries->d_name, "..") != 0){
            
                strcpy(fileLoc,Path);
                strcat(fileLoc,"/");
                strcat(fileLoc,FileEntries->d_name);
                
                
                bool temp = printfile(fileLoc,FileEntries,Args,curr_depth,(Args->S_flag || !(Args->e_flag || Args->E_flag)));
                if(FileEntries->d_type != DT_DIR && temp){
                    if(Args->e_flag){
                        char *cmd[100];
                        ecmdParser(Args->e_cmd,fileLoc,cmd);
                        executeCmd(cmd);
                    }
                    if(Args->E_flag){
                        EcmdParser(fileLoc,false);
                    }
                }
                
                if(FileEntries->d_type == DT_DIR && Args->depth > curr_depth){
                    FilesTraverse(fileLoc,Args,curr_depth+1);
                }
           }
            
        }
    }
closedir(Folder);
}