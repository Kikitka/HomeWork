#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int userLineNumber;
    int fd;

    if((fd = open("text.txt", O_RDONLY)) == -1)
    {
        printf("File doesn't open\n");
        exit(-1);
    }
    
    // Размер файла
    struct stat statbuf; 
    if ( fstat(fd, &statbuf) < 0 )
    {
        printf("fstat error"); 
    }
    // int len = lseek(fd, 0, SEEK_END);
    // Отображение в память
    void *fileMemory;
    if((fileMemory = mmap (0, statbuf.st_size, PROT_READ, MAP_SHARED, fd, 0))== MAP_FAILED)
    {
        perror("mmap error");
    }

    char *str;
    str = fileMemory;
    munmap (fileMemory, statbuf.st_size);
    printf(str);

    // printf("i'm here");

    int i = 0, j = 0;
    int positionSymbol = 1;
	int *arrSymbol = NULL;
    
    // Поиск конца строк
    while(str[j] != 0)
    {
        printf("i'm here");
    	if (str[j] == '\n')
    	{
            arrSymbol[i] = -1;
    		i++;
    		positionSymbol = j + 1;
    		arrSymbol = (int*)realloc(arrSymbol, (i + 1) * sizeof(int));
    		arrSymbol[i] = positionSymbol;
    	}
    	j++;
        printf("i'm here");
    }

int k = 0;
    do
    {
        printf("Enter line number: ");
        scanf("%d", &userLineNumber);
		if(userLineNumber > i + 1)
        {
			printf("В файле всего %d строк(и), введите номер строки из этого диапазона\n", i+1);
		}
        else if(userLineNumber > 0)
        {
			int lineLength = arrSymbol[userLineNumber] - arrSymbol[userLineNumber - 1];
			k = 0;
			while(k < lineLength){
				printf("%c", str[arrSymbol[userLineNumber - 1] + k]);
				k++;
			}
		}

	} 
    while(userLineNumber != 0);

    // Очистка
    // munmap (fileMemory, statbuf.st_size);  

    return 0;
}