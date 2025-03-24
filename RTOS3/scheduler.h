#include "types.h"

#define sleep(); for(uint64 i=0; i<=10000000; i++){}

extern void uartputc_sync(int c);

void runTask(void (*f)(char*), uint64 t, char* arg);
void delay(uint64 t);
void read_bus_device(char *buffer, int size, int currBusId, int writeBusId);
void write_bus_device(const char *data, int size, int currBusId, int writeBusId);

void schedule();