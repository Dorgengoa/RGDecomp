/* rgp:protos */
#define RGP_SELF_MesSlot0GetState_278df0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_00278df0 {
    u8 pad0[0x4];
    s32 unk4;
} Obj_00278df0;

/*rgp*/
/*rgp*/
/*rgp*/

s32 MesSlot0GetState_278df0(void)
{
    Obj_00278df0 *o;
    s32 v;

    o = ((Obj_00278df0 *)MesMgrGetSlot_277a20(GetMesMgr_277e90(), 0));
    if (o == 0) {
        return -1;
    }
    v = o->unk4;
    if (v != 0) {
        return MesWinGetState_276a80(v);
    }
    return -1;
}
