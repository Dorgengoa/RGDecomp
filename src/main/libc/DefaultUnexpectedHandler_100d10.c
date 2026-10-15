#include "types.h"

#pragma tailcall off

extern void (*D_00445E88)(void) __attribute__((section(".data")));

void DefaultUnexpectedHandler_100d10(void)
{
    D_00445E88();
}
