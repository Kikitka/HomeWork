#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int pid;
    int rv;
    switch(pid = fork())
    {
        case -1:
            printf("Was't created");
            exit(-1);
            break;
        case 0:
            //char *args[]={"./file. c",NULL);
            printf("%s", argv[1]);
            execvp(argv[1], argv);
            exit(0);
            break;
        default:
            printf("Parent with id: %d\n", getpid());
            // wait(rv);
            printf("parant exit code %d", WEXITSTATUS(rv));
            waitpid(pid, &rv, 0);
            break;
    }

    return 0;
}