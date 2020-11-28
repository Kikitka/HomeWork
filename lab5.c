#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char const *argv[])
{
	int pipefd[2]; //элементы указывают на канал чтения (pipefd[0]) и на канал записи (pipefd[1])
    pid_t p1, p2; 
    char buf[] = "HeLlO wOrLd!"; //пишет первый дочерний процесс
    char buf2[2]; //читает второй

    //если не удалось создать канал
    if (pipe(pipefd) == -1) 
    { 
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    //выполнение первого дочернего процесса
    if ((p1 = fork()) == 0) 
    {
    	close(pipefd[0]);  //закрытие канал чтения
    	write(pipefd[1], buf, sizeof(buf)); //запись из буфера количество байтов, равное размеру буфера
    	exit(0);
    }

    if (p1 > 0 && (p2 = fork() == 0)) //создать из родителя второго потомка
    {
        //это выполняет второй дочерний процесс
    	close(pipefd[1]); //закрыть канал записи
    	while(read(pipefd[0], buf2, 1) != 0)
        { 
            //посимвольно считать,
    		printf("%c", toupper(buf2[0])); //перевести в верхний регистр и вывести
    	}
    	exit(0);
    }

	return 0;
}