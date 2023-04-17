#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

#include "./manipulate_string.h"

#define ANSI_RESET  "\x1b[0m"

#define ANSI_RED    "\x1b[31m"
#define ANSI_GREEN  "\x1b[32m"

#define ANSI_BOLD   "\x1b[1m"

int __size(char **);

int main(int argc, char **argv){
    int i, pid;
    char *args[5];
    char *file;
    char *commmit_msg = (char *) malloc(sizeof(char) * 44);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
  
    sprintf(commmit_msg, "Update dotfiles, date: %02d-%02d-%d %02d:%02d:%02d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);

    args[3] = NULL;
    args[4] = NULL;

    for(i = 1; i < argc; i++){
        file = split(argv[i], '/')[__size(split(argv[i], '/')) - 1];

        if(access(argv[i], 0) == 0){
            if(!(access(file, 0) == 0)){
                args[0] = "ln";
                args[1] = argv[i];
                args[2] = ".";
                
                pid = fork();

                if(pid == 0){
                    fprintf(stderr, "Link %s in the repo directory.\n", file);
                    execv("/usr/bin/ln", args);
                }

                wait(NULL);
            }else{
                fprintf(stderr, ANSI_RED ANSI_BOLD "X " ANSI_RESET);
                fprintf(stderr, "File ./%s already exists.\n", file);
            }
        }else{    
            fprintf(stderr, ANSI_RED ANSI_BOLD "X " ANSI_RESET);
            fprintf(stderr, "File %s not exists.\n", argv[i]);
        }       
    }

    args[0] = "git";
    args[1] = "add";
    args[2] = "-A";
            
    pid = fork();
            
    if(pid == 0){
        fprintf(stderr, ANSI_GREEN ANSI_BOLD "\xE2\x9C\x94 " ANSI_RESET);
        fprintf(stderr, "Exec: git add -A.\n");
        execv("/usr/bin/git", args);
    }

    wait(NULL);

    args[1] = "commit";
    args[2] = "-m";
    args[3] =  commmit_msg;

    pid = fork();

    if(pid == 0){
        fprintf(stderr, ANSI_GREEN ANSI_BOLD "\xE2\x9C\x94 " ANSI_RESET);
        fprintf(stderr, "Exec: git commit -m \"%s\".\n", commmit_msg);
        execv("/usr/bin/git", args);
    }

    wait(NULL);

    args[1] = "push";
    args[2] = NULL;

    pid = fork();

    if(pid == 0){
        fprintf(stderr, ANSI_GREEN ANSI_BOLD "\xE2\x9C\x94 " ANSI_RESET);
        fprintf(stderr, "Exec: git push.\n");
        execv("/usr/bin/git", args);
    }

    wait(NULL);

    return 0;
}

int __size(char **str_a){
    int l = 0;

    while(str_a[l]){
        l++;
    }    

    return l;
}
