/* rgp:protos */
#define RGP_SELF_MinimapMgrTrackActiveSlot_321ea0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

typedef struct Obj {
    u8 pad000[0x510];
    s32 f510;
    s32 f514;
} Obj;

void MinimapMgrTrackActiveSlot_321ea0(Obj *arg0, void *rgp_a1)
{
    s32 t2;
    s32 t4;

    if (arg0->f510 == 0) {
        MinimapMgrSelectActive_321f60((void *)arg0, (void *)rgp_a1);
        return;
    }
    t2 = MinimapMgrFindSlotByName_322340((int)arg0, (void *)rgp_a1);
    if (t2 != 0 && t2 != arg0->f514) {
        arg0->f514 = t2;
        t4 = arg0->f510;
        if (t4 == t2) {
            arg0->f514 = 0;
            return;
        }
        if (MinimapSlotIsActive_322510(t4) != 0) {
            MinimapFadeOut_329eb0(arg0->f510, 10.0f);
        }
        if (MinimapSlotIsActive_322510(arg0->f514) != 0) {
            MinimapSetFadeAlpha_32a1d0(arg0->f514, 0.0f);
            MinimapFadeIn_329ef0(arg0->f514, 10.0f);
        }
    }
}
