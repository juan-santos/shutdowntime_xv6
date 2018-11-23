#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int sys_shutdown_time_call(void) {
	struct rtcdate atual;
        struct rtcdate *desligamento;

	if(argptr(0, (void*)&desligamento, sizeof(*desligamento)) < 0){
		return -1;
	}

	cmostime(&atual);
	cprintf("Horario atual: %d/%d/%d %d:%d:%d\n", atual.day, atual.month, atual.year, atual.hour, atual.minute, atual.second);

	cprintf("Horario desligamento: %d/%d/%d %d:%d:%d\n", desligamento->day, desligamento->month, desligamento->year, desligamento->hour, desligamento->minute, desligamento->second);

	if((atual.year == desligamento->year) && (atual.month == desligamento->month) && (atual.day == desligamento->day) && (atual.hour == desligamento->hour) && (atual.minute ==  desligamento->minute)) {
		
		//desligamento
		cprintf("Horario de desligamento chegou..\n\n");
		outb(0xf4,0x00);
		return 0;
	}

	if(
	(atual.year > desligamento->year) ||	
	((atual.year >= desligamento->year) && (atual.month > desligamento->month)) || 
	((atual.year >= desligamento->year) && (atual.month >= desligamento->month) && (atual.day > desligamento->day)) ||
	((atual.year >= desligamento->year) && (atual.month >= desligamento->month) && (atual.day >= desligamento->day) && (atual.hour > desligamento->hour)) ||
	((atual.year >= desligamento->year) && (atual.month >= desligamento->month) && (atual.day >= desligamento->day) && (atual.hour >= desligamento->hour) && (atual.minute > desligamento->minute))
	){

		cprintf("Data de desligamento ja passou... \n\n");
		return -1;
	}

	return 1;
}
