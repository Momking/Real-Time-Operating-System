#include <scheduler.h>
#include <types.h>
#include <csr.h>
#include "memlayout.h"

char kstack[4096];


// void (*saved_ra)();
// void (*saved_sp)();
uint64 saved_ra;
uint64 saved_sp;
uint64 TRAPFRAME[32];



extern void uartputc_sync(int c);
void timer_interrupt();


void kernelvec();
void kernelvec2();



void print(){
  char* s = "Hello World\n";
  while(*s){
    uartputc_sync(*s++);
  }
}


#define MIE_STIE (1L << 5)  // supervisor timer
int kmain() {

  unsigned long x = r_mstatus();
  w_mstatus(x | (1<<3)); // mie bit is at index 3

  // w_mtvec((uint64)kernelvec);

  w_mtvec((uint64)kernelvec2);

  volatile uint8 *device_addr = (volatile uint8 *)BUS_DEVICE_BASE;

  device_addr[2] = 1;

  if(device_addr[0] != 1 || device_addr[1] != 1){
    sleep();
  }


  schedule();

	return 0;
}

void printNum(long long num) {
  char buffer[65];
  int pos = 0;
  short isneg = 0;
  if (num < 0 ) {
    num = -num;
    isneg = 1;
  }
  if (num == 0) {
    buffer[pos ++] = '0';
  }

  while (num > 0) {
    buffer[pos ++ ] = '0' + num % 10;
    num /= 10;
  }
  if (isneg == 1) {
    buffer[pos ++ ] = '-';
  }
  for (int i = pos - 1; i >= 0; i --) {
    uartputc_sync(buffer[i]);
  }
  uartputc_sync('\n');
}


#define MSTATUS_SIE (1L << 1)  // Supervisor Interrupt Enable
#define MSTATUS_MIE (1L << 3)  

// Supervisor Trap Cause
uint64
r_mcause()
{
  uint64 x;
  asm volatile("csrr %0, mcause" : "=r" (x) );
  return x;
}

// enable device interrupts
static inline void
intr_on()
{
  w_mstatus(r_mstatus() | MSTATUS_SIE);
  w_mstatus(r_mstatus() | MSTATUS_MIE);
}

// disable device interrupts
// static inline 
void
intr_off()
{
  w_mstatus(r_mstatus() & ~MSTATUS_SIE);
  w_mstatus(r_mstatus() & ~MSTATUS_MIE);
}



void enable_timer_interrupt(){
  w_mie(r_mie() | MIE_STIE);
}

void disable_timer_interrupt(){
  w_mie(r_mie() & ~MIE_STIE);
}




void
set_timer_interrupt_at(uint64 x)
{
  intr_off();
  enable_timer_interrupt();

  w_stimecmp(r_time() + (10000000*x));
  // w_stimecmp(r_time() + x);
  intr_on();
}

void
timer_interrupt_handler()
{
  
  intr_off();
  print();

  disable_timer_interrupt();
  intr_on();
  
  // w_stimecmp(r_time() + 10000000);
  // asm volatile("wfi");
}






