#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int fd;
    char buf[1000];
    int countBite = 0;
    int arrSymbol[1000];
    int positionSymbol = 1;
    int userLineNumber;
    int position;

    arrSymbol[0] = -1;
    // Открытие файла
    if((fd = open("text.txt", O_RDONLY)) == -1)
    {
        printf("File doesn't open\n");
        exit(-1);
    }
    // Нахождение символа переноса строки
    countBite = read(fd, buf, 1000);
    int i = 0;
    while(i < countBite)
    {
        if(buf[i] == '\n')
        {
            arrSymbol[positionSymbol++] = i;
        }
        i++;
    }
    printf("Enter line number: ");
    scanf("%d", &userLineNumber);

    // Установка курсора
    if(userLineNumber == 0)
    {
        exit(-1);
    }
    else if(userLineNumber > positionSymbol-1)
    {
        printf("Error: out of the file\n");
        exit(-1);
    }
    else
    {
        position = lseek(fd, arrSymbol[userLineNumber - 1] + 1, SEEK_SET);
    }
    // Очистка буфера и запись в него строки
    memset(buf, NULL, 1000);
    countBite = read(fd, buf, 1000);
    i = 0;
    while(buf[i] != '\n')
    {
        printf("%c", buf[i]);
        i++;
    }
    printf("\n");
    // Закрытие файла
    if(close(fd))
    {
        printf("Error in closing file.\n");
    }
    return 0;
}