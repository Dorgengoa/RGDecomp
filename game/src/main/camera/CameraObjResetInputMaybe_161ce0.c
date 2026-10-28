/* rgp:protos */
#define RGP_SELF_CameraObjResetInputMaybe_161ce0 1
#include "port/game_protos.h"
#line 1
/* main s27m: CLOSED by [[mwcc-const-sdata-load-hoist]]: `extern const ... section(".sdata")`
   AND the two reads written INLINE (a named `t` local is still 2 bad). */
#include "types.h"
#include "vec.h"

extern f32 D_0047D350 __attribute__((section(".sdata")));

/* 2 bad: retail creates the D_0047D350 lwc1 read and the 3.0f lui
   constant in the OPPOSITE order from us (ours: lui(3.0f), sw(0x190),
   lwc1; retail: lwc1, sw(0x190), lui(3.0f)) -- a pure vreg-creation-
   order swap between two independent, unrelated constants, inert to
   moving the `t = D_0047D350` statement (tried before/after the 0x194
   store) and to naming 3.0f as its own local at various positions.
   opt_pulloutconstants off and opt_repositioncode off are ALSO inert.
   Untried: GPR contiguity re-grouping per
   [[levers.d/mwcc-gpr-decl-order-map]]. Same class as
   ModelObjBaseInitNoMotion_186f60's 0x1c8/-1.0f residue -- likely a genuine scheduler
   tie-break, not a source-order lever. */
void CameraObjResetInputMaybe_161ce0(void *arg0) {

    *(s32 *)((u8 *)arg0 + 0x214) = 0;
    *(s32 *)((u8 *)arg0 + 0x218) = 0;
    *(s32 *)((u8 *)arg0 + 0x21C) = 0;
    *(s32 *)((u8 *)arg0 + 0x190) = 0;
    *(s32 *)((u8 *)arg0 + 0x194) = 0;
    *(s32 *)((u8 *)arg0 + 0x1D0) = 0;
    *(u128 *)((u8 *)arg0 + 0x1E0) = 0;
    *(s32 *)((u8 *)arg0 + 0x210) = 0;
    *(s32 *)((u8 *)arg0 + 0x1FC) = 0;
    *(u128 *)((u8 *)arg0 + 0x200) = 0;
    *(u128 *)((u8 *)arg0 + 0x120) = 0;
    *(f32 *)((u8 *)arg0 + 0x1F8) = -1.0f;
    *(s32 *)((u8 *)arg0 + 0x1F0) = -1;
    *(f32 *)((u8 *)arg0 + 0x1F4) = -1.0f;
    *(f32 *)((u8 *)arg0 + 0x244) = D_0047D350;
    *(f32 *)((u8 *)arg0 + 0x24C) = D_0047D350;
    *(f32 *)((u8 *)arg0 + 0x248) = 3.0f;
}
