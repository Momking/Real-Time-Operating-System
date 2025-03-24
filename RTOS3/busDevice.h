#include "types.h"
#include "memlayout.h"

extern void uartputc_sync(int c);

#define BUS_DEVICE_SIZE 1024
#define sleep(); for(uint64 i=0; i<=10000000; i++){}

volatile uint8 *device_addr = (volatile uint8 *)BUS_DEVICE_BASE;

void read_bus_device(char *buffer, int size, int currBusId, int readBusId);
void write_bus_device(const char *data, int size, int C, int writeBusId);