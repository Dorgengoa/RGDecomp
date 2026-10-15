#include "types.h"

struct S8 { s32 a; s32 b; };

extern s32 ScriptGetCodeAddr_249050(struct S8 *);
extern s32 ScriptGetInt_2490f0(struct S8 *);
extern s32 GetMapMgr_201a90(void);
extern s32 MapSlotsFindBlockByName_1e4910(s32, s32, s32);
extern s32 MapBlockGetEntry_1deb10(s32, s32);
extern s32 MapEntryAsObjRelated_1e1230(s32);
extern s32 MotionListResetAll_171e00(s32);
extern void ModelObjPlayMotionByName_1867a0(s32, s32, s32);

s32 EvCmdMapBlockEntryPlayMotion_247ae0(struct S8 *p0, s32 p1)
{
    s32 r0;
    s32 rv4;
    s32 rv7;
    s32 r8;
    s32 r9;
    s32 r10;
    s32 r11;

    r0 = ScriptGetCodeAddr_249050(p0++);
    rv4 = 0;
    if (p1 >= 2) {
        rv4 = ScriptGetCodeAddr_249050(p0++);
    }
    rv7 = 0;
    if (p1 >= 3) {
        rv7 = ScriptGetInt_2490f0(p0);
    }
    r8 = GetMapMgr_201a90();
    r9 = MapSlotsFindBlockByName_1e4910(r8, r0, 0);
    if (r9 == 0) {
        return 0;
    }
    r10 = MapBlockGetEntry_1deb10(r9, 0);
    if (r10 == 0) {
        return 0;
    }
    r11 = MapEntryAsObjRelated_1e1230(r10);
    if (r11 == 0) {
        return 0;
    }
    MotionListResetAll_171e00(r11 + 0x1F0);
    if (rv4 != 0) {
        ModelObjPlayMotionByName_1867a0(r11, rv4, rv7);
    }
    return 1;
}
