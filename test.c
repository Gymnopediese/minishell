#include <stdio.h>

int main(int argc, char **argv){
	dprintf(2, "Mon message d'erreur\n");
	dprintf(1, "Mon Message normal\n");
	return (argc - 1);
}
