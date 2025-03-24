#include "memlayout.h"
#include "scheduler.h"

void getNum(long long num, char* buf) {
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

  int  y = 0;
  for (int i = pos - 1; i >= 0; i --) {
    buf[y++] = buffer[i];
  }
}

void task(char* s)
{
  write_bus_device(s, 4, 1, 3);
}

void schedule(){
    char* a = "AMAN";
    while(1){
        sleep();
        runTask(task, 5, a);
    }    
}