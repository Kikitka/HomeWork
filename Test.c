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
            printf("%s", argv[1]);
            execvp(argv[1], &argv[1]);
            exit(1);
        default:
            printf("Parent with id: %d\n", getpid());
            waitpid(pid, &rv, 0);
            printf("parant exit code %d", WEXITSTATUS(rv));
            break;
    }

    return 0;
}