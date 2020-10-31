#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <fcntl.h>

#include <dirent.h>
#include <sys/types.h>

#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <time.h>


int main(int argc, char const *argv[])
{


	DIR *dir;
	char typeFile;
	char path[255], date[100], accessUser[4], accessGroup[4], accessOther[4];
	long UID, GID, size;

	struct dirent *entry;
	struct passwd *pwd;
	struct stat statFile;
	struct group *gr;


	
	if (argv[1] == NULL) {
        getcwd(path, 255);
    	stat(path, &statFile);
    	//dir = opendir(path);
    }else{
    	stat(argv[1], &statFile);
    	//dir = opendir(argv[1]);
    }


	struct tm* timeinfo = localtime (&statFile.st_mtime);
    
    if (S_ISREG(statFile.st_mode))
    {
    	typeFile = '-';
    } else if (S_ISDIR(statFile.st_mode))
    {
    	typeFile = 'd';
    } else{
    	typeFile = '?';
    }

	UID = (long) statFile.st_uid;
	GID = (long) statFile.st_gid;
	size = statFile.st_size;
	pwd = getpwuid(UID);
	gr = getgrgid(GID);

	if (statFile.st_mode & S_IRUSR)
	{
		strcat(accessUser, "r");
	} else{
		strcat(accessUser, "-");
	}

	if (statFile.st_mode & S_IWUSR)
	{
		strcat(accessUser, "w");
	} else{
		strcat(accessUser, "-");
	}

	if (statFile.st_mode & S_IXUSR)
	{
		strcat(accessUser, "x");
	} else{
		strcat(accessUser, "-");
	}


	if (statFile.st_mode & S_IRGRP)
	{
		strcat(accessGroup, "r");
	} else{
		strcat(accessGroup, "-");
	}
	if (statFile.st_mode & S_IWGRP)
	{
		strcat(accessGroup, "w");
	} else{
		strcat(accessGroup, "-");
	}
	if (statFile.st_mode & S_IXGRP)
	{
		strcat(accessGroup, "x");
	} else{
		strcat(accessGroup, "-");
	}


	if (statFile.st_mode & S_IROTH)
	{
		strcat(accessOther, "r");
	} else{
		strcat(accessOther, "-");
	}
	if (statFile.st_mode & S_IWOTH)
	{
		strcat(accessOther, "w");
	} else{
		strcat(accessOther, "-");
	}
	if (statFile.st_mode & S_IXOTH)
	{
		strcat(accessOther, "x");
	} else{
		strcat(accessOther, "-");
	}

	
	/*while((entry = readdir(dir)) != NULL){
		printf("%s\n", entry->d_name);
	}*/

	strftime(date, 100, "%b %d %H:%M", timeinfo);
    
	printf("[%c]%s%s%s %s %s %ld %s\n", 
			typeFile,
			accessUser,
			accessGroup,
			accessOther, 
			pwd->pw_name,
			gr->gr_name,
			size,
			date);

    
	//printf("%s %u %u\n", path, S_IFDIR, statFile.st_mode);
		



    



	/*dir = opendir(path);
	if (!dir)
	{
		perror("dir doesn't open");
		exit(1);
	}else{
		while((entry = readdir(dir)) != NULL){
			switch (entry->d_type){
				case 4: 
					typeFile = 'd';
					break;
				case 8: 
					typeFile = '-';
					break;
				default: 
					typeFile = '?';
					break;
			}
			
			/*printf("%ld - %s [%d] %d\n", 
				entry->d_ino, 
				entry->d_name, 
				entry->d_type, 
				entry->d_reclen);
		}
		
	}
	*/
	closedir(dir);

	return 0;
}