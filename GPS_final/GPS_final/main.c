#include "Common.h"
#include "generalMenu.h"

int main(int argc, char **argv)
{
	/*Initialize GTK*/
	gtk_init(&argc, &argv);

	/*Start main window (menu)*/
	call_main_menu();

	/*launch GTK*/
	gtk_main();
	return 0;
}