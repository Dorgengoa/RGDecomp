/* rg-override: replaces game/src/main/model/NodeObjDrawLitThunk_187f50.c sha256 7608361ba0fd09713eae284104610c9841ed790323e646a60b07a25a7050eff9
 * why: draw-path random numbers (docs/WIDESCREEN.md "Draw-path random numbers", lane randdraw): a lit object drawn only because of the port's wider planes draws its light flicker from the private stream; the helpers are in the ViewSetPerspective_1564a0 override; no effect at 4:3 / 16:9 (no retail-plane set) */
/* rgp:protos */
#define RGP_SELF_NodeObjDrawLitThunk_187f50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 rg_cull_draw_begin(void *obj);
void rg_cull_draw_end(s32 tok);

void NodeObjDrawLitThunk_187f50(s32 p0)
{
    s32 tok = rg_cull_draw_begin((void *)(__UINTPTR_TYPE__)(u32)p0);
    NodeObjDrawLit_1947f0(p0, 1);
    rg_cull_draw_end(tok);
}
