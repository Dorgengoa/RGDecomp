#include "types.h"

extern s32 GetGameData_1fede0(void);
extern s32 GetMapMgr_201a90(void);
extern s32 MapMgrSlotsFindEntryByKeyMaybe_1e15f0(s32, s32);
extern s32 MesSlot0Close_278e40(void);
extern s32 MapEntryAsObjRelated_1e1230(s32);
extern s32 MotionListResetAll_171e00(s32);
extern s32 ModelObjPlayMotionByName_1867a0(s32, void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045BFF0[];
extern s32 D_00481B2C;
extern u8 D_00481B30;
extern u8 D_00481B34;

void FuncPointDeactivate_2000e0(s32 p0, s32 p1)
{
    s32 t0;
    s32 r0;
    s32 r1;
    s32 t1;
    s32 r2;
    s32 rv7;
    s32 r3;
    s32 r4;
    s32 r5;
    s32 r6;

    t0 = D_00481B2C;
    if (t0 >= 0) {
        r0 = GetGameData_1fede0();
        r1 = GetMapMgr_201a90();
        t1 = D_00481B2C;
        r2 = MapMgrSlotsFindEntryByKeyMaybe_1e15f0(r1, t1);
        if (p1 == 0) {
            D_00481B2C = -1;
        }
        D_00481B30 = 0;
        D_00481B34 = 0;
        rv7 = r2;
        if (r2 != 0) {
            r3 = MesSlot0Close_278e40();
            if (p0 == 0) {
                return;
            }
            r4 = MapEntryAsObjRelated_1e1230(r2);
            r5 = MotionListResetAll_171e00((r4 + 0x1F0));
            r6 = ModelObjPlayMotionByName_1867a0(r4, D_0045BFF0, 6);
            rv7 = r6;
        }
        return;
    }
}
