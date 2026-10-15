#include "types.h"
typedef struct P {
    u8 pad0[0x3A];
    s16 unk3A;
    u8 pad3C[8];
    s32 unk44;
} P;

extern s32 ConstructNewArray_100710(s32, s32, s32, s32, s32);
extern s32 MemStackNew_14e1b0(s32, s32);
extern P *MapAreaDefGetRecTable_1dcf20(s32);
extern u8 *MapBlockGetInfo_1e00b0(s32);
extern s32 ScriptArgGetInt_1ecbe0(s32);
extern s32 D_004818F8;
extern s32 D_004818FC;
extern s16 D_00481904;
extern s16 D_0048190C;

s32 MapDefCmdBlockBox2Count_1eb620(s32 arg0, s32 arg1)
{
    P *p;
    u8 *q;
    s32 n;
    s32 r;
    s32 i;

    if (arg1 != 1) {
        return 1;
    }
    if ((D_004818FC == 0) || (D_004818F8 == 0)) {
        return 1;
    }
    p = MapAreaDefGetRecTable_1dcf20(D_004818FC);
    if (p->unk44 == 0 || p->unk3A <= D_00481904) {
        return 1;
    }
    D_0048190C = 0;
    q = MapBlockGetInfo_1e00b0(p->unk44 + D_00481904 * 0xCC);
    n = ScriptArgGetInt_1ecbe0(arg0);
    r = ConstructNewArray_100710(MemStackNew_14e1b0(n * 0x4C + 0x10, D_004818F8), 0, 0, 0x4C, n);
    *(s32 *)(q + 0xC) = r;
    if (r == 0) {
        return 1;
    }
    *(s16 *)(q + 0x12) = n;
    return 1;
}
