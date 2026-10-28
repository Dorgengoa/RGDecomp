/* rgp:protos */
#define RGP_SELF_EffectInstanceReset_2dd410 1
#include "port/game_protos.h"
#line 1
/* PARK 2/3: RIGHT LENGTH (66w), was 11 bad, now 8. Three of the words were
   a real WIDTH bug: arg0+0, arg0+4 and arg0+0x20 are `s16` fields (retail
   `sh`), not `s32` (fixed here). The remaining 8 are the float
   load/store SCHEDULING for the sp40/sp30 vector setup -- source statement
   order ALREADY matches retail's exactly (checked against the .s listing
   line by line); the residue is mwcc's own $f0/$f1/$f2 register rotation
   choice, not reachable by reordering. Same family as EvMapObjPartInitFromFrame_363f90's
   remaining 7. */
#include "types.h"
typedef struct { f32 w[4]; } SD4_0047EF10;
extern SD4_0047EF10 D_0047EF10 __attribute__((section(".sdata")));
typedef struct { f32 w[4]; } SD4_0047EF20;
extern SD4_0047EF20 D_0047EF20 __attribute__((section(".sdata")));

void *memset(void *, s32, s32);
/*rgp*/

void EffectInstanceReset_2dd410(u8 *arg0) {
    f32 sp40[4] __attribute__((aligned(16)));
    f32 sp30[4] __attribute__((aligned(16)));
    s32 var_17;

    *(SD4_0047EF10 *)sp40 = D_0047EF10;
    *(SD4_0047EF20 *)sp30 = D_0047EF20;
    sceVu0CopyVector(arg0 + 0x40, sp40);
    sceVu0CopyVector(arg0 + 0x50, sp40);
    sceVu0CopyVector(arg0 + 0x60, sp30);
    *(s16 *)(arg0 + 0) = -1;
    *(s16 *)(arg0 + 4) = -1;
    *(s32 *)(arg0 + 8) = -1;
    *(s32 *)(arg0 + 0x10) = -1;
    *(s16 *)(arg0 + 2) = -1;
    *(s16 *)(arg0 + 6) = 0;
    memset(arg0 + 0x170, 0, 0x20);
    memset(arg0 + 0xF0, 0, 0x40);
    var_17 = 0;
    do {
        sceVu0CopyVector(arg0 + (var_17 * 0x10) + 0x70, sp40);
        var_17 += 1;
    } while (var_17 < 4);
    *(s32 *)(arg0 + 0x1C) = 0;
    *(s32 *)(arg0 + 0x28) = -1;
    *(s32 *)(arg0 + 0x2C) = 0;
    *(s16 *)(arg0 + 0x20) = 0;
    *(s32 *)(arg0 + 0x30) = -1;
}
