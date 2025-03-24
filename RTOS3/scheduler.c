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
    char value[3];
    read_bus_device(value, 3, 3, 2);

    for (int i = 0; i < 3; i++) {
        uartputc_sync(value[i]);
    }
    uartputc_sync('\n');
}

void task2(char* s)
{
  char buffer[3];
  getNum(*(uint32*)s,buffer);

  write_bus_device(buffer, 3, 3, 2);
}

void task(char* s)
{
  char value[4];
  read_bus_device(value, 4, 3, 1);

  for(int i=0; i<4; i++){
    uartputc_sync(value[i]);
  }
  uartputc_sync(' ');
  sleep();

  char value2[7];
  read_bus_device(value2, 7, 3, 2);

  for(int i=0; i<7; i++){
    uartputc_sync(value2[i]);
  }
  uartputc_sync('\n');
  sleep();
}

void schedule(){
  while(1){
    sleep();
    runTask(task, 5, 0);  
  }    
}


/*  Another Implementation for scheduler  */

/*
void schedule(){
  int counter = 200;
    while(1){
        runTask(task1, 2, 0);

        runTask(task2, 2, (char*)&counter);
        counter++;
    }    
}

*/