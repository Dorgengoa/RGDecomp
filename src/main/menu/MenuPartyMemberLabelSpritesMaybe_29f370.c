#include "types.h"

typedef struct {
    s16 key;
    s16 a;
    s16 b;
} Entry;

typedef struct {
    Entry e[11];
} Tbl;

typedef struct {
    s16 x0;
    s16 x2;
    s16 x4;
    s16 x6;
    s16 x8;
    s16 xA;
    s16 xC;
    s16 xE;
} Elem;

typedef struct {
    u8 pad0[0x18];
    s32 unk18;
} Ctx;

typedef struct {
    u8 pad0[0x2C];
    s16 unk2C;
} Obj3;

typedef struct {
    u8 pad0[0x4C4];
    s32 unk4C4;
} Obj;

Ctx *GetGameData_1fede0();
Elem *UiGetWidgetSprite_28fe10(s32, s32, s32);
Obj3 *CharaGetIconRecMaybe_3ae3e0(s32);
s32 PartyCountMembers_3c2010(s32, s32, s32);
s32 PartyGetMemberChara_3c2420(s32, s32);
extern Tbl D_00450870;

s32 MenuPartyMemberLabelSpritesMaybe_29f370(Obj *arg0, s32 arg1)
{
    Tbl t;
    Ctx *ctx;
    s32 id;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 key;
    s32 h;
    Elem *e2;
    Elem *e;

    {
        s16 *s = (s16 *)&D_00450870;
        s16 *d = (s16 *)&t;
        s32 c = 0x21;
        do {
            *d++ = *s++;
        } while (--c > 0);
    }
    ctx = GetGameData_1fede0();
    id = arg1;
    id &= 0xFFFF;
    n = PartyCountMembers_3c2010(ctx->unk18, 1, 1);
    n = (s32)(u32)n;
    for (i = 0; i < 3; i++) {
        e = UiGetWidgetSprite_28fe10(arg0->unk4C4, (id + i) & 0xFFFF, 0);
        if (e == NULL) {
            return 0;
        }
        e->xC = 0;
        e->x4 = 0;
    }
    for (j = 0; j < n; j++) {
        e2 = UiGetWidgetSprite_28fe10(arg0->unk4C4, (id + j) & 0xFFFF, 0);
        if (e2 == NULL) {
            return 0;
        }
        h = PartyGetMemberChara_3c2420(ctx->unk18, j);
        if (h == 0) {
            return 0;
        }
        key = CharaGetIconRecMaybe_3ae3e0(h)->unk2C;
        e2->xA = 0;
        e2->x8 = 0;
        for (k = 0; k < 10; k++) {
            if (key == t.e[k].key) {
                e2->x8 = t.e[k].a;
                e2->xA = t.e[k].b;
            }
        }
        e2->xC = 0x4C;
        e2->x4 = 0x4C;
        e2->xE = 0x12;
        e2->x6 = 0x12;
    }
    return 1;
}
