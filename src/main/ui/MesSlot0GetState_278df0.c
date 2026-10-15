#include "types.h"

typedef struct Obj_00278df0 {
    u8 pad0[0x4];
    s32 unk4;
} Obj_00278df0;

extern void *GetMesMgr_277e90(void);
extern Obj_00278df0 *MesMgrGetSlot_277a20(void *o, s32 index);
extern s32 MesWinGetState_276a80(s32 arg0);

s32 MesSlot0GetState_278df0(void)
{
    Obj_00278df0 *o;
    s32 v;

    o = MesMgrGetSlot_277a20(GetMesMgr_277e90(), 0);
    if (o == 0) {
        return -1;
    }
    v = o->unk4;
    if (v != 0) {
        return MesWinGetState_276a80(v);
    }
    return -1;
}
