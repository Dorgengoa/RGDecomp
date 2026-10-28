/* rgp:protos */
#define RGP_SELF_Terminate_100ce0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

#pragma tailcall off

extern void (*D_00445E88)(void) __attribute__((section(".data")));

void Terminate_100ce0(void)
{
    D_00445E88();
}
