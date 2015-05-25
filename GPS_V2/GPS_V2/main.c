#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <glib.h>
#include <gtk\gtk.h>

int main(int argc, char* argv[]){
	/* initialiser GTK+ */
	gtk_init(&argc, &argv);
	
	/*Appel de la fonction master*/
	master_window();

	/* boucle principale */
	gtk_main();

	return EXIT_SUCCESS;
}