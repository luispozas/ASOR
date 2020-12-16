
#include <sys/utsname.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>

int main (int argc, char *argv[]){
	uid_t id = getuid();
	printf("ID real: %d\n", id);
	printf("ID efectivo: %d\n", geteuid());

	struct passwd *p = getpwuid(id);

	printf("Nombre de usuario real: %s\n", p->pw_name);
	printf("Directorio home real: %s\n", p->pw_dir);
	printf("Descripcion del usuario real: %s\n", p->pw_gecos);

	return 0;
}
