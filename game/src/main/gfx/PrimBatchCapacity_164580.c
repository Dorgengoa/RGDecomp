/* rgp:protos */
#define RGP_SELF_PrimBatchCapacity_164580 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN PrimBatchCapacity_164580 -- 36 B / 9 words.  DIV-TRAP GENERALISATION PROBE.
   Not a window unit: it is here to prove that `#pragma divbyzerocheck on`
   (measured on src/wf/main/DebugItemIconGridSetScrollThumbs_29a7e0.c) is a FAMILY key and not a
   one-function accident.  Different divisor (13, not 30), different shape
   (leaf, no calls, no frame), same `addiu $2,$0,K / bnez $2 / div / break 0,7
   / mflo` pair.  Without the pragma mwcc folds the check away and the object
   is TWO WORDS SHORT.  */

#pragma divbyzerocheck on

typedef struct Ctx164580 {
    u8 pad00[0xC];
    s32 m0C;                 /* +0x0C */
} Ctx164580;

s32 PrimBatchCapacity_164580(Ctx164580 *p)
{
    return (p->m0C - 4) / 13 - 1;
}
