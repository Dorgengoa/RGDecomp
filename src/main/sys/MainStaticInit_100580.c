#pragma opt_common_subs off
#include "types.h"
extern u8 D_0046F9C0[];
extern u8 D_0046FD64[];
extern u8 D_0047D130[];
extern void RunStaticCtors_100df0(void *a, void *b, void *c, void *d);
void MainStaticInit_100580(void)
{
    RunStaticCtors_100df0(D_0046F9C0, D_0046FD64, D_0047D130, D_0047D130);
}
