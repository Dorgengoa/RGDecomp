#include "types.h"

#pragma tailcall off

extern void (*D_00445E90)(void) __attribute__((section(".data")));

void Unexpected_100cb0(void)
{
    D_00445E90();
}
