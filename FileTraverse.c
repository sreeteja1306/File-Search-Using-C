#include "FileTraverse.h"

void printhelp(){
    printf("Hw2 [options] [target]\n");
    printf("Options:\n");
    printf("-f <string pattern> <depth>\tlist all files that satisfy string pattern and depth\n");
    printf("-s <string size>           \tlist all files with file size less than or equal to the value\n");
    printf("-S                         \tlist all files along with size, permissions, and last access time\n");
}
int count_tabs(char *path)
{
    int tab_count=0;
    for (int i=0;i<strlen(path);i++)
    {
        if (path[i]=='/')
        tab_count+=1;
    }
    return tab_count;
}
void FilesTraverse(char *Path, bool f_flag,bool s_flag,bool S_flag,char *f_argSubString, int depth, int fileSize,int curr_depth){
    struct dirent *FileEntries;
    char *fileLoc = malloc(100*sizeof(char));
    DIR *Folder = opendir(Path);
    long int size_of_file,access_time;
    bool ff_flag=false;
    struct stat st;
    //long int loc = telldir(Folder);
    if(Folder != NULL)
    {
        while((FileEntries = readdir(Folder) ) != NULL)
        {
            
           if(strcmp(FileEntries->d_name, ".") != 0 && strcmp(FileEntries->d_name, "..") != 0)
           {
            
            int tab_count=count_tabs(Path);
            
            strcpy(fileLoc,Path);
            strcat(fileLoc,"/");
            strcat(fileLoc,FileEntries->d_name);
            
            
            for (int i=0;i<tab_count;i++)
            printf("\t");
            
            if (s_flag || S_flag)
            {
            
            if (stat(fileLoc,&st)==-1)
            {
            size_of_file=st.st_size;
            access_time=st.st_atime; 
            }
            }
            
            if (strstr(FileEntries->d_name,f_argSubString)!=NULL && FileEntries->d_type==8 && curr_depth<depth)
            {
            ff_flag=true;
            }
            else
            {
            ff_flag=false;
            }

            if(s_flag || ff_flag)
            {
            if(fileSize<=size_of_file)
            printf("%s",FileEntries->d_name);
            }
            else
            printf("%s",FileEntries->d_name);
            if (S_flag)
            {
                if(FileEntries->d_type==4) //Folder
                {
                printf("(%d,%ld)",0 ,access_time);
                curr_depth+=1;
                }
                else if(FileEntries->d_type==8) //File
                {
                printf("(%ld,%ld)",size_of_file ,access_time);
                }
            }
            printf("\n");
            FilesTraverse(fileLoc,f_flag,s_flag,S_flag,f_argSubString,depth,fileSize,curr_depth);
           }
        }
        
    }
closedir(Folder);
}