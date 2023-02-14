#include "FileTraverse.h"

void printhelp(){
    printf("Hw2 [options] [target]\n");
    printf("Options:\n");
    printf("-f <string pattern> <depth>\tlist all files that satisfy string pattern and depth\n");
    printf("-s <string size>           \tlist all files with file size less than or equal to the value\n");
    printf("-S                         \tlist all files along with size, permissions, and last access time\n");
}


const char* printFormat(bool show,int curr_depth){
    for(int i=0;i<curr_depth;i++) printf("\t");
    if(show) return "%s : (%d , %jo , %s)\n";
    else return "%s\n";
}

void printfile(char *file,struct dirent *FileEntries,struct searchArgs *Args,int curr_depth){
    bool printfile = true,printDiscription=false;
    struct stat st;
    int size=0;
    if (stat(file, &st) == -1)
    {
        perror("stat");
        exit(EXIT_FAILURE);
    }
    if(Args->S_flag) printDiscription = true;
    if(FileEntries->d_type != DT_DIR){
        size = st.st_size;
        if(Args->f_flag){
            if(!strstr(FileEntries->d_name,Args->SubString)) printfile = false;}
        if(Args->s_flag){
            if(!(size<=Args->MaxSize)) printfile = false;}
        }
    
    if(Args->t_flag){
        switch(Args->t_arg){
            case 'f':
                if(FileEntries->d_type != DT_REG&&FileEntries->d_type != DT_DIR)printfile = false;
                break;
            case 'd':
                if(FileEntries->d_type != DT_DIR)printfile = false;
                break;
        }
    }
    if(printfile){
        printf(printFormat(printDiscription,curr_depth),FileEntries->d_name,size,(uintmax_t) st.st_mode,strtok(ctime(&st.st_atime),"\n"));
    }
    else if(printfile) printf(printFormat(printDiscription,curr_depth),FileEntries->d_name);
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
                
                printfile(fileLoc,FileEntries,Args,curr_depth);
                
                if(FileEntries->d_type == DT_DIR && Args->depth > curr_depth){
                    FilesTraverse(fileLoc,Args,curr_depth+1);
                }
           }
            
        }
    }
closedir(Folder);
}