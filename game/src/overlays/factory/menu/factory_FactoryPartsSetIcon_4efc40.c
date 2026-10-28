/* rgp:protos */
#define RGP_SELF_factory_FactoryPartsSetIcon_4efc40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004EFC40 -- 60 B / 15 words.  CROSS-IMAGE PROBE for
   `#pragma divbyzerocheck on`, measured in main on src/wf/main/DebugItemIconGridSetScrollThumbs_29a7e0.c
   this same lane.  The div-trap family is 267 functions across four images
   (main 228, insect 20, normal 13, factory 6) and NONE was converted before
   this lane; this unit asks whether the key is main-only.

   Everything else here is settled spelling:
     * `dsll32 $5,16 / dsra32 $5,16` is an explicit `(s16)` cast on an s32
       parameter ([[normal-s16-cast-sign-extension]]).
     * ONE `%` and ONE `/` by the same 5 emit TWO `div` instructions (mfhi then
       mflo) -- mwcc does not share them -- and only the SECOND carries the
       `bnez $3 / break 0,7` pair.
     * `j func_28F970` is the frameless tail call.
     * `func_28F970`'s id parameter is `u16`, the spelling used by the
       byte-identical factory_FactoryPartsListBuild_4efe90 / factory_FactoryMaterialReqListLayout_4f2d50.  */

#pragma divbyzerocheck on

typedef struct Ctx4EFC40 {
    u8 pad00[0x8C];
    void *m8C;               /* +0x8C */
} Ctx4EFC40;

/*rgp*/

void factory_FactoryPartsSetIcon_4efc40(Ctx4EFC40 *w, s32 v, s32 n)
{
    UiSetSpriteUv_28f970(w->m8C, 0x4A, ((s16)v % 5) << 6, ((s16)v / 5) << 6, n);
}
