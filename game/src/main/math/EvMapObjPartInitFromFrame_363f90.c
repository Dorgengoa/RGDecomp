/* rgp:protos */
#define RGP_SELF_EvMapObjPartInitFromFrame_363f90 1
#include "port/game_protos.h"
#line 1
/* PARK 2/3: RIGHT LENGTH (65w), was 13 bad, now 7. Six of the words were
   a real WIDTH bug: the three `*(u32 *)(arg0+X) = *(u32 *)spNN;` tail
   copies only moved the FIRST float of each 4-float array -- retail uses
   `lq`/`sq` (128-bit) because it copies the WHOLE vector, so they need to
   be `u128` (from vec.h), not `u32` (fixed here). The remaining 7 are the
   float load/store SCHEDULING for the sp30/sp60/sp50/sp40 setup, same
   family and same "source order already matches, register rotation
   differs" residue as EffectInstanceReset_2dd410's remaining 8. */
#include "types.h"
typedef struct { f32 w[4]; } SD4_0047F920;
extern SD4_0047F920 D_0047F920 __attribute__((section(".sdata")));
#include "vec.h"

/*rgp*/
/*rgp*/

void EvMapObjPartInitFromFrame_363f90(u8 *arg0, s32 arg1) {
    f32 sp60[4] __attribute__((aligned(16)));
    f32 sp50[4] __attribute__((aligned(16)));
    f32 sp40[4] __attribute__((aligned(16)));
    f32 sp30[4] __attribute__((aligned(16)));

    *(SD4_0047F920 *)sp30 = D_0047F920;
    FrameTransformPoint_148f60(arg1, sp30, sp30);
    FrameTransformPoint_148f60(arg1, sp60, (f32 *)(arg0 + 0xC0));
    FrameTransformPoint_148f60(arg1, sp50, (f32 *)(arg0 + 0xD0));
    FrameTransformPoint_148f60(arg1, sp40, (f32 *)(arg0 + 0xE0));
    *(f32 *)(arg0 + 0x20) = sp60[0];
    *(f32 *)(arg0 + 0x24) = sp60[1];
    *(f32 *)(arg0 + 0x28) = sp60[2];
    *(f32 *)(arg0 + 0x60) = sp50[0];
    *(f32 *)(arg0 + 0x64) = sp50[1];
    *(f32 *)(arg0 + 0x68) = sp50[2];
    *(f32 *)(arg0 + 0xA0) = sp40[0];
    *(f32 *)(arg0 + 0xA4) = sp40[1];
    *(f32 *)(arg0 + 0xA8) = sp40[2];
    *(u128 *)(arg0 + 0) = *(u128 *)sp60;
    *(u128 *)(arg0 + 0x40) = *(u128 *)sp50;
    *(u128 *)(arg0 + 0x80) = *(u128 *)sp40;
    sceVu0CopyVector(arg0 + 0x100, sp30);
    sceVu0CopyVector(arg0 + 0xF0, sp30);
}
