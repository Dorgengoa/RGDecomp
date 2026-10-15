/* MATCH (main s22): [[mwcc-const-sdata-load-hoist]] -- the gp float load
   retail schedules ABOVE the prologue's `sq $sN,K($sp)` stores.  Fires on a
   READ-ONLY extern (the barrier is the $sp stores, not a write), and it is
   PER-EXTERN: const the symbol whose load is misplaced, not every gp float
   the unit reads. */
#include "types.h"

extern f32 WrapAngle_13c050(f32 arg0);
extern const f32 D_0047D3FC __attribute__((section(".sdata")));

/* 4 bad, right length: retail orders [global lwc1][sq s0][arg lwc1 via
   $4][move s0=$4]; ours orders [sq s0][arg lwc1 via $4][move s0][global
   lwc1] -- a 4-word scheduling shuffle among the prologue sq and two
   independent loads. Several statement-order and add-operand-order
   permutations tried, all INERT or worse (5-6 bad). Same
   prologue/independent-load scheduling family as CameraObjResetInputMaybe_161ce0 et al. */
void StatusEffectOrbitIconsSpin_33d040(void *arg0) {
    f32 *p = (f32 *)arg0;
    p[0x24] = WrapAngle_13c050(D_0047D3FC + p[0x24]);
}
