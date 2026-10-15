#include "types.h"


typedef struct {
    u8 pad0[0x3A];
    s16 unk3A;
    u8 pad3C[8];
    u8 *unk44;
} Entry;

extern s32 LookupNameValueNoCase_1cab50(s32, void *, s32);
extern Entry *MapAreaDefGetRecTable_1dcf20(s32);
extern void MapDataSetAttrFlags_1e74b0(u8 *, s32);
extern void MapDataSetLinkKeyMaybe_1e7b40(u8 *, s32);
extern s32 ScriptArgGetStr_1ecb80(s32);
extern void GetMapMgr_201a90(void);
extern s32 atoi(s32);
extern u8 D_0044B400[];
extern s32 D_004818F8;
extern s32 D_004818FC;
extern s16 D_00481904;

s32 MapDefCmdBlockAttr_1ebb90(s32 arg0, s32 arg1)
{
    Entry *p;
    u8 *base;
    s32 res;
    s32 i;
    s32 s;
    s32 r;

    if (arg1 == 0) {
        return 1;
    }
    if (D_004818FC == 0 || D_004818F8 == 0) {
        return 1;
    }
    p = MapAreaDefGetRecTable_1dcf20(D_004818FC);
    if (p->unk44 == NULL || !(p->unk3A > D_00481904)) {
        return 1;
    }
    GetMapMgr_201a90();
    res = 0;
    base = p->unk44 + D_00481904 * 0xCC;
    for (i = 0; i < arg1; i++) {
        s = ScriptArgGetStr_1ecb80(arg0 + i * 8);
        r = LookupNameValueNoCase_1cab50(s, D_0044B400, 0);
        if (r != 0) {
            res |= r;
        } else {
            MapDataSetLinkKeyMaybe_1e7b40(base, atoi(s));
        }
    }
    MapDataSetAttrFlags_1e74b0(base, res);
    return 1;
}
