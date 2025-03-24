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

void task1(char* s)
{
  char buffer[3];
  getNum(*(uint32*)s,buffer);

  write_bus_device(buffer, 3, 2, 3);
}

void task2(char* s)
{   
    char value[3];
    read_bus_device(value, 3, 2, 3);

    for (int i = 0; i < 3; i++) {
        uartputc_sync(value[i]);
    }
    uartputc_sync('\n');
}

void task(char* s){
  char* name = "NISHANT";

  write_bus_device(name, 7, 2, 3);
}

void schedule(){
  int counter = 0;
  while(1){
    sleep();
    runTask(task, 5, 0);
    counter++;
  }    
}

/*  Another Implementation for scheduler  */

/*
void schedule(){
  int counter = 100;
  while(1){
      runTask(task1, 2, (char*)&counter);

      runTask(task2, 2, 0);
      counter++;
  }    
}
*/