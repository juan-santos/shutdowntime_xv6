//A program which prints something on screen
#include "types.h"
#include "stat.h"
#include "user.h"
#include "date.h"

int main(int argc, char *argv[]) {
	int loop = 0;
	struct rtcdate data;
    	
	data.year = 2018;
	data.month = 11;
	data.day = 23;
	data.hour = 11;
	data.minute = 10;
	data.second = 0;

	
    	do {	
		printf(2, "Chamando a funcao que desliga o computador.. \n\n\n");
		loop = shutdown_time_call(&data);
		sleep(1000);
	} while(loop == 1);//se a data não tiver passado continuo tentando desligar

	exit();
}
