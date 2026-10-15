/* MATCH (main s22): two edits crossed -- [[mwcc-const-sdata-load-hoist]] on
   D_0047D244 (the gp lwc1 has to sit above the prologue `sq`s), and the
   0xC0 loop store is a 128-bit `sq`, not `sw`. */
#include "types.h"
#include "vec.h"

extern void EvMapObjPointReset_3644f0(void *);
extern const f32 D_0047D244 __attribute__((section(".sdata")));

void EvMapObjPartInit_364240(void *arg0) {
    s32 i;

    *(f32 *)((u8 *)arg0 + 0x12C) = D_0047D244;
    *(u128 *)((u8 *)arg0 + 0xF0) = 0;
    *(u128 *)((u8 *)arg0 + 0x100) = 0;
    *(s32 *)((u8 *)arg0 + 0x138) = 0;
    *(f32 *)((u8 *)arg0 + 0x130) = 1.0f;
    *(f32 *)((u8 *)arg0 + 0x134) = 1.0f;
    *(s32 *)((u8 *)arg0 + 0x110) = 0;
    *(f32 *)((u8 *)arg0 + 0x114) = 1.0f;
    *(s32 *)((u8 *)arg0 + 0x118) = 0;
    *(s32 *)((u8 *)arg0 + 0x11C) = 0;
    for (i = 0; i < 3; i++) {
        EvMapObjPointReset_3644f0((u8 *)arg0 + (i << 6));
        *(u128 *)((u8 *)arg0 + (i << 4) + 0xC0) = 0;
        *(s32 *)((u8 *)arg0 + (i << 2) + 0x120) = 0;
    }
}
