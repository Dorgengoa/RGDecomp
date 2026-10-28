/* rgp:protos */
#define RGP_SELF_EventSubNodeAddSetTexAnim_251000 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern void strcpy(void *, const void *);
extern u8 D_0045EDA0[];

struct Obj0 {
    s32 m00;
    u8 pad004[0x1C];
    s32 m20;
    u8 pad024[0x8];
    u8 m2C[0x4];
};

/* Retail FALLS THROUGH into the strcpy(p1) arm, so p1 != 0 is the if body.
   The 0x20 store is duplicated into both arms -- an if/else, not a ternary. */
void EventSubNodeAddSetTexAnim_251000(s32 p0, const void *p1, s32 p2)
{
    struct Obj0 *r0;

    r0 = PoolAllocAppendNode_251d50(p0);
    if (r0 != 0) {
        r0->m00 = 0x1F;
        if (p1 != 0) {
            strcpy(r0->m2C, p1);
            r0->m20 = p2;
        } else {
            strcpy(r0->m2C, D_0045EDA0);
            r0->m20 = p2;
        }
    }
}
