#include "types.h"

extern s32 GetActionMgr_1fdb50(void);
extern u8 *GetGameData_1fede0(void);
extern s32 CharaInvincibleTimeOver_2138b0(u8 *);
extern u8 *ActionMgrFindById_233b50(s32, s32);
extern u8 *ObjMgrFindFiltered_3bb190(s32, s32, s32, s32, s32, s32 *, s32, void *);
extern s32 D_004825D4;
extern void ObjFilterIsTargetable_3bb480();

s32 AiCollectTargetIds_2cd530(s32 *arg0)
{
    s32 sp7C;
    s32 sp78;
    u8 *g;
    s32 h;
    s32 n;
    s32 start;
    u8 *e;
    u8 *o;
    s32 ok;

    g = GetGameData_1fede0();
    h = GetActionMgr_1fdb50();
    n = 0;
    start = -1;
    D_004825D4 += 1;
    for (;;) {
        sp7C = -1;
        e = ObjMgrFindFiltered_3bb190(*(s32 *)(g + 0x1C), -1, 1, 0, start, &sp7C, 0, ObjFilterIsTargetable_3bb480);
        if (!e || sp7C < 0) {
            break;
        }
        start = sp7C + 1;
        o = ActionMgrFindById_233b50(h, *(s32 *)(e + 0xC));
        if (o == NULL || (!(*(s32 *)(o + 0xA44) & 0x40) && !(*(s32 *)(o + 0xA44) & 0x20) && CharaInvincibleTimeOver_2138b0(o) != 0)) {
            arg0[n++] = *(s32 *)(e + 0xC);
        }
    }
    if (n <= 0) {
    start = -1;
    for (;;) {
        sp78 = -1;
        e = ObjMgrFindFiltered_3bb190(*(s32 *)(g + 0x1C), -1, 1, 0, start, &sp78, 0, ObjFilterIsTargetable_3bb480);
        if (!e || sp78 < 0) {
            break;
        }
        start = sp78 + 1;
        o = ActionMgrFindById_233b50(h, *(s32 *)(e + 0xC));
        if (o == NULL || CharaInvincibleTimeOver_2138b0(o) != 0) {
            arg0[n++] = *(s32 *)(e + 0xC);
        }
    }
    }
    return n;
}
