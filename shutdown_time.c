//A program which prints something on screen
#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {

	printf(1,"Desligando o computador.. \n");

	shutdown_time_call();
	exit();
}
