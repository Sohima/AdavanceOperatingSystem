#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc, char **argv) {

    int status = 0;
    pid_t pid = fork();
    FILE *fp = fopen("my_file.txt","r");
    char buff[256]="";
    char buff1[256]="";

    if (pid == 0)
    {
        // child process
        if ((fgets(buff, sizeof(buff), fp)) != NULL)
            printf ("Read a line in child:\t%s\n", buff);
        else
            printf ("read failed!\n");
        exit(1);
    }
    else if (pid > 0)
    {
        // parent process
        waitpid (pid, &status, 0);
        while ( (char)fgetc( fp ) != '\n' );
        memset(buff1,0, sizeof(buff1));
        if ((fgets(buff1, sizeof(buff1), fp)) != NULL)
            printf ("Read a line in parent:\t%s\n", buff1);
        else
            printf ("read failed!\n");
    }
    else
    {
        // fork failed
        printf("fork() failed!\n");
        return 1;
    }
    return 0;
}