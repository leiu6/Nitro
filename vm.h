#ifndef _NITRO_VM_H
#define _NITRO_VM_H

#include "object.h"

typedef struct {
	Nitro_FunctionObject *fcn;
	u8 *ip;
	
} CallFrame;

void vm_init();

void vm_free();

bool vm_run(

#endif // _NITRO_VM_H
