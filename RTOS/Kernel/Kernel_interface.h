#ifndef KERNEL_INTERFACE_H
#define KERNEL_INTERFACE_H

uint8 Kernel_u8Createtask(uint8 Copy_u8Priority, uint16 Copy_u16Periodicity, void(*Copy_pvTaskHandler)(void);

void Kernel_u8StartScheduler(void);


#endif