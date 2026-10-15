#include "types.h"

typedef struct {
    u8 pad0[0x3A];
    s16 unk3A;
    u8 pad3c[0x44 - 0x3C];
    s32 unk44;
} Obj001EBCE0;

typedef struct {
    s32 unk0;
    s16 *unk4;
    u8 pad8[0x10 - 8];
    s8 unk10;
} Elem001EBCE0;

s16 *MemStackNew_14e1b0(s32, s32);
Obj001EBCE0 *MapAreaDefGetRecTable_1dcf20(s32);
Elem001EBCE0 *MapBlockGetInfo_1e00b0(s32);
s32 MapDataGetId_1e7bd0(s32);
s16 ScriptArgGetInt_1ecbe0(s32);
extern s32 D_004818F8;
extern s32 D_004818FC;
extern s16 D_00481904;

s32 MapDefCmdBlockLinkIds_1ebce0(s32 arg0, s32 arg1)
{
    Obj001EBCE0 *o;
    Elem001EBCE0 *e;
    s32 n;
    s32 i;

    if (arg1 == 0) {
        return 1;
    }
    if (D_004818FC == 0 || D_004818F8 == 0) {
        return 1;
    }
    o = MapAreaDefGetRecTable_1dcf20(D_004818FC);
    if (o->unk44 == 0 || o->unk3A <= D_00481904) {
        return 1;
    }

    n = arg1;
    if (MapDataGetId_1e7bd0(D_004818FC) == 0x6A4) {
        n = arg1 + 0x140;
    }
    if (n > 0x14) {
        n = 0x14;
    }
    e = MapBlockGetInfo_1e00b0(o->unk44 + D_00481904 * 0xCC);
    e->unk4 = MemStackNew_14e1b0(n * 2, D_004818F8);
    e->unk10 = 0;
    for (i = 0; i < arg1; i++) {
        e->unk4[e->unk10] = ScriptArgGetInt_1ecbe0(arg0 + i * 8);
        e->unk10++;
    }
    return 1;
}
