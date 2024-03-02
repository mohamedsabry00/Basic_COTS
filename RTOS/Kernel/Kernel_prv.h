#ifndef KERNEL_PRV_H
#define KERNEL_PRV_H

typedef struct
{
	uint16 Periodicity;
	void(*TaskHandler)(void);	
	
}Task_t;


#endif