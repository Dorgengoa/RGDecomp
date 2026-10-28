/* rgp:protos */
#define RGP_SELF_Unexpected_100cb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

#pragma tailcall off

extern void (*D_00445E90)(void) __attribute__((section(".data")));

void Unexpected_100cb0(void)
{
    D_00445E90();
}
