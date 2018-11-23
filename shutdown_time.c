#include "types.h"
#include "stat.h"
#include "user.h"
#include "date.h"

int main(int argc, char *argv[]) {
	int loop = 0;
	struct rtcdate data;

	if(argc < 5){
		printf(2, "Numero de parametros eh incompativel! \n\n\n");
		exit();
	}    	

	data.year = atoi(argv[1]);
	data.month = atoi(argv[2]);
	data.day = atoi(argv[3]);
	data.hour = atoi(argv[4]);
	data.minute = atoi(argv[5]);
	data.second = 0;
	
    	do {	
		printf(2, "Chamando a funcao que desliga o computador.. \n\n\n");
		loop = shutdown_time_call(&data);
		sleep(1000);
	} while(loop == 1);//se a data não tiver passado continuo tentando desligar

	exit();
}
