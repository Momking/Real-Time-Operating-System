#include "busDevice.h"
#include "memlayout.h"

void read_bus_device(char *buffer, int size, int currBusId, int writerBusId)
{
    if (size > BUS_DEVICE_SIZE)
    {
        size = BUS_DEVICE_SIZE;  // Check for the size of buffer
    }

    int startAddr = 5;
    int j = 0;

    while(device_addr[4] != currBusId)
    {
        // loop till writer did not finish
        sleep();
    }

    for (int i = startAddr; i < startAddr+size; i++)
    {
        buffer[j++] = device_addr[i];   // Read the data value from the Data bus
        if(device_addr[i] == 0) break;
    }

    device_addr[3] = 0;  // Make the writer flags 0
    device_addr[4] = 0;  // Make the reader flags 0
}

void write_bus_device(const char *data, int size, int currBusId, int readerBusId)
{
    if (size > BUS_DEVICE_SIZE)
    {
        size = BUS_DEVICE_SIZE;   // Check for the size of buffer
    }

    int startAddr = 5;
    int j = 0;

    while(1){
        if(device_addr[3] == 0)
        {
            device_addr[3] = currBusId;
            sleep();
            if(device_addr[3] == currBusId) break;
        }
        else if(device_addr[3] == currBusId) break;
    }

    int i = startAddr;

    for(; i < startAddr+size; i++)
    {
        device_addr[i] = data[j++];   // Write the data value to the Data bus
    }

    device_addr[i] = 0;

    device_addr[4] = readerBusId;  // Reader Flag is set to specific reader BusID
    
}