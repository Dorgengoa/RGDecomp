/* rgp:protos */
#define RGP_SELF_insect_InsectBattleDamagePopupInit_50e2b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0050E2B0 -- 84 bytes, 21 instructions, 4 calls. */

typedef struct Obj {
    u8  pad00[0x450];
    s32 m450;                       /* +0x450 */
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleDamagePopupInit_50e2b0(Obj *o)
{
    void *h;

    h = insect_InsectGetDamagePopupList_5108c0();
    if (h != 0) {
        DamagePopupListReset_2d3230(h);
        DamagePopupListInit_2d3180(h, &o->m450);
        DamagePopupListReleaseHeap_2d2d50(h);
    }
}
