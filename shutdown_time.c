//A program which prints something on screen
#include "types.h"
#include "stat.h"
#include "user.h"
#include "date.h"

int main(int argc, char *argv[]) {
	
	struct rtcdate data;
	
	printf(1,"Desligando o computador.. \n");
    	shutdown_time_call(&data);
	
	printf(1, "Current RTC date/time is %02d-%02d-%d, %02d:%02d:%02d.\n\n",   
    	data.day, data.month, data.year,   
    	data.hour, data.minute, data.second);   
	
	exit();
}
