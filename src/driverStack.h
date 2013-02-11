//
//  main.c
//  MacroTesting
//
//  Created by So Townsend on 2/11/13.
//  Copyright (c) 2013 So Townsend. All rights reserved.

//Driver dispatch table
//Id -> Driver Function?

#if 0
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct DRIVER_T {
    unsigned char id;  //1 Byte
    unsigned char class; //1 Byte
    unsigned char data[10]; //Do whatever
} Driver_t;

typedef struct RRPACKET_T {
    unsigned char id; //1 Byte
    unsigned char class; //1 Byte
    unsigned char data[4]; //Payload
} RRPacket_t;

//Device ID Dispatch table (Convert a device ID to it's driver functions)
typedef struct DRIVER_TABLE_ENT_T {
    unsigned char id;
    Driver_t *context;
    void (*respond)(Driver_t *, unsigned char *);
    void (*poll)(Driver_t *);
} Driver_Table_Ent_t;

#define MAX_DRIVERS 100
Driver_Table_Ent_t DriverTable[MAX_DRIVERS];
int NumberOfDrivers = 0;  //Current number of drivers

//Setup a driver on the system
//Allocate a new structure
//Load structure
//Send structure to DriverTaInit();
//Add to rrDispatchTable [id -> DriverResponder(struct, rrPacket);
//Add device to polling loop (FunctionPointer, struct)
#define AddDevice(ID, CLASS) {\
    Driver_t *context = malloc(sizeof(Driver_t)); \
    context->id = 0x##ID; \
    context->class = 0x##CLASS; \
    DriverTable[NumberOfDrivers].context = context; \
    DriverTable[NumberOfDrivers].respond = Driver##CLASS##Respond; \
    DriverTable[NumberOfDrivers].poll = Driver##CLASS##Poll; \
    ++NumberOfDrivers; \
    Driver##CLASS##Init(context); \
    } \

/********************************************************/

//Load member variables
#define LoadDriverSelf(CLASS) Driver##CLASS##Members *self = (Driver##CLASS##Members *)driver;

//Driver member setup
#define DriverMembersBegin(CLASS) \
typedef struct DRIVER##CLASS##MEMBERS { \
    unsigned char id; \
    unsigned char class; \

#define DriverMembersEnd(CLASS) } Driver##CLASS##Members;\

//Driver init
#define DriverInitBegin(CLASS) \
    void Driver##CLASS##Init(Driver_t *driver) { \
        LoadDriverSelf(CLASS);

#define DriverInitEnd(CLASS) }

//Driver response
#define DriverRespondBegin(CLASS) \
    void Driver##CLASS##Respond(Driver_t *driver, unsigned char *rcvData) { \
        LoadDriverSelf(CLASS); \

#define DriverRespondEnd(CLASS) } \

//Driver poll
#define DriverPollBegin(CLASS) \
    void Driver##CLASS##Poll(Driver_t *driver) { \
        LoadDriverSelf(CLASS); \

#define DriverPollEnd(CLASS) } \

/********************************************************/

//Setup class members
DriverMembersBegin(2F)
    int myData[2];
DriverMembersEnd(2F)

//Setup anything
DriverInitBegin(2F);
    self->myData[0] = 100;
    printf("%0x\n", self->id);
DriverInitEnd(2F)

//ARM sent us something
DriverRespondBegin(2F)
    printf("%d\n", rcvData[0]);
    //Respond to this?  I2C (Same id #)
DriverRespondEnd(2F)

//Start a poll request
DriverPollBegin(2F)
    printf("oh my...\n %0x", self->id);
DriverPollEnd(2F)

int main(int argc, const char * argv[])
{
    AddDevice(3E, 2F);
    AddDevice(3F, 2F);

    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
#endif