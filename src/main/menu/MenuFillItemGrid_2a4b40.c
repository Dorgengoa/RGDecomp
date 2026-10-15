#include "types.h"

typedef struct {
    u8 pad0[0x11];
    s8 m11;
    u8 pad12[2];
    s32 m14;
} Obj;

typedef struct {
    u8 pad0[0x18];
    s32 m18;
} Ctx;

extern Ctx *GetGameData_1fede0();
extern void MenuItemGridCellSetEmpty_2a4c80(Obj *, s32, s32);
extern void MenuItemGridDrawCell_2a4d30(Obj *, s32, s32, s32);
extern s32 InvFindByInvId_3c87d0(s32, s32, s32);
extern s32 InvMakeIdFromCategory_3c88b0(s32, s32, s32, s32, s32);
extern s32 D_004659F0[];
extern s32 D_004659F8[];
extern s32 D_00465B18[];
extern s32 D_00465B20[];

s32 FUN_002a4b40_e1(Obj *o, s32 arg1, s32 k);
static inline s32 isnull(s32 r) { return (r != 0) ^ 1; }

s32 MenuFillItemGrid_2a4b40(Obj *o, s32 arg1)
{
    return FUN_002a4b40_e1(o, arg1, o->m11);
}

s32 FUN_002a4b40_e1(Obj *o, s32 arg1, s32 k)
{
    s32 w;
    Ctx *c;
    s32 h;
    s32 cur;
    s32 last;
    s32 i;
    s32 r;

    c = GetGameData_1fede0();
    if (*(volatile s32 *)&o->m14 == 9) {
        k = 0;
        w = D_00465B18[0];
        h = D_00465B20[0];
    } else {
        w = D_004659F0[0];
        h = D_004659F8[0];
    }
    cur = InvMakeIdFromCategory_3c88b0(c->m18, o->m14, k, 0, 0);
    {
        s32 t = InvMakeIdFromCategory_3c88b0(c->m18, o->m14, k, w - 1, h - 1);
        last = t;
    }
    i = 0;
    for (;;) {
        r = InvFindByInvId_3c87d0(c->m18, cur, 0);
        if (!isnull(r)) {
            MenuItemGridDrawCell_2a4d30(o, arg1, r, i);
        } else {
            MenuItemGridCellSetEmpty_2a4c80(o, arg1, i);
        }
        if (cur == last) {
            break;
        }
        i++;
        cur++;
    }
    return 1;
}
