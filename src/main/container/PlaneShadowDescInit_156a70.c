/* main s27m: CLOSED -- the three zeroed words are u128 stores (sq $zero). */
#include "types.h"
#include "vec.h"

extern void NameTableNodeReset_15ada0(void *);
extern const f32 D_0047D1D8 __attribute__((section(".sdata")));
extern const f32 D_0047D1DC __attribute__((section(".sdata")));

void PlaneShadowDescInit_156a70(void *arg0)
{
    *(u128 *)((u8 *)arg0 + 0x0) = 0;
    *(u128 *)((u8 *)arg0 + 0x10) = 0;
    *(f32 *)((u8 *)arg0 + 0x14) = D_0047D1D8;
    *(u128 *)((u8 *)arg0 + 0x20) = 0;
    *(u32 *)((u8 *)arg0 + 0x24) = 0x3F800000;
    NameTableNodeReset_15ada0((u8 *)arg0 + 0x30);
    *(u32 *)((u8 *)arg0 + 0x178) = 0x3E800000;
    *(s32 *)((u8 *)arg0 + 0x100) = 0;
    *(s32 *)((u8 *)arg0 + 0x104) = 1;
    *(s32 *)((u8 *)arg0 + 0x108) = 0;
    NameTableNodeReset_15ada0((u8 *)arg0 + 0x110);
    *(f32 *)((u8 *)arg0 + 0x188) = D_0047D1DC;
    *(f32 *)((u8 *)arg0 + 0x184) = D_0047D1DC;
    *(f32 *)((u8 *)arg0 + 0x180) = D_0047D1DC;
    *(s32 *)((u8 *)arg0 + 0x18C) = 0;
}
