#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv) {

	if(argc < 2){
		printf("ERROR: Debes introducir la ruta del directorio como parametro\n");
	}

	DIR *directorio = opendir(argv[1]);

	if(directorio == NULL){
		printf("ERROR: No existe el directorio\n");
	}

	struct dirent *sig = readdir(directorio);

	int totalsize = 0;
	struct stat sb;

	while(sig != NULL){

		char path[250];                   /*Preparo la siguiente entrada...*/
		strcpy(path, argv[1]);
		strcat(path, "/");
		strcat(path, sig->d_name);

		if (stat(path, &sb) == -1) {
			closedir(directorio);
            printf("ERROR: (stat)\n");
        }


        /*Distingo entre el tipo de ficheros [OJO -> Acordarse de stat y S_IS--(sb.st_mode) ]*/
        if(S_ISREG(sb.st_mode)){
        	printf("%s (OCUPA: %i Bytes)\n", sig->d_name, sb.st_size);
        	totalsize = totalsize + sb.st_size;
        }
        else if(S_ISDIR(sb.st_mode)){
        	printf("/ %s \n", sig->d_name);
        }
        else if(S_ISLNK(sb.st_mode)){   /* Leo el link con "readLink"... */
        	char buff_name[1024];
        	ssize_t len = readlink(path, buff_name, sizeof(buff_name)-1);

        	printf("%s -> %s (OCUPA: %i Bytes)\n", sig->d_name, buff_name, sb.st_size);
        	totalsize = totalsize + sb.st_size;
        }

		sig = readdir(directorio);
	}

	printf("Tamaño total que ocupan los ficheros: %i KB.\n", totalsize/1024);

	closedir(directorio);
	return 0;
}