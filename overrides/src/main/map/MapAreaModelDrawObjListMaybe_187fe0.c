/* rg-override: replaces game/src/main/map/MapAreaModelDrawObjListMaybe_187fe0.c sha256 66c137d5111bd12164a0c9f9c1796cab5466a5a1038c768fd70a423d3b6e289e
 * why: draw-path random numbers (docs/WIDESCREEN.md "Draw-path random numbers", lane randdraw): an object drawn only because of the port's wider planes (and its children) draws with the private stream; the helpers are in the ViewSetPerspective_1564a0 override; no effect at 4:3 / 16:9 (no retail-plane set) */
/* rgp:protos */
#define RGP_SELF_MapAreaModelDrawObjListMaybe_187fe0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x32];
    s16 unk32;
} Elem00187FE0;

/*rgp*/
/*rgp*/

s32 rg_cull_draw_begin(void *obj);
void rg_cull_draw_end(s32 tok);

void MapAreaModelDrawObjListMaybe_187fe0(s32 arg0, s32 arg1, s32 arg2) {
    s32 tok;
    s32 i;
    Elem00187FE0 *p;

    for (i = 0; i < arg2; i++) {
        p = *(Elem00187FE0 **)(arg1 + i * 4);
        if (p != NULL && p->unk32 != 0) {
            NodeObjIsInView_194200(p);
            tok = rg_cull_draw_begin(p);
            NodeObjDrawChildren_194700(p);
            rg_cull_draw_end(tok);
        }
    }
}
