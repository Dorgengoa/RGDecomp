#include "types.h"
//PRAGMA

typedef struct {
    u8 pad0[0x18];
    s32 unk18;
} Sys;

typedef struct {
    u8 pad0[4];
    s16 x4;
    s16 x6;
    u8 pad8[4];
    s16 xC;
    s16 xE;
    u8 pad10[0x10];
} Rect;

typedef struct {
    u8 pad0[0x16];
    s16 x16;
    s16 x18;
} Sub;

typedef struct {
    u8 pad0[4];
    s32 x4;
    u8 pad8[2];
    u8 xA;
} Flag;

typedef struct {
    u8 pad0[0x20];
    Rect *unk20;
    Sub *unk24;
    Flag *unk28;
} Res;

typedef struct {
    s32 unk0;
    s16 count;
    s16 pad6;
} Iter;

typedef struct {
    u8 pad0[0x5c];
    void *unk5C;
    u8 pad60[0x14];
    s16 unk74;
} Obj;

extern Sys *GetGameData_1fede0(void);
extern s32 PartyGetSlotChara_3c2fb0(s32, s32);
extern void CharaAbilityViewCtor_3a8180(void *, s32, s32, s32);
extern void IterInit_370170(Iter *, void *);
extern s16 *IterSeek_36fff0(Iter *, s32);
extern s16 *IterNext_370040(Iter *);
extern Res *UiFindWidget_290460(void *, u16);
extern void MenuCharaAbilityRowSetup_3408e0(s32, s16 *, Rect *, Sub *, Flag *, Rect *);
extern s32 CharaHasAbilityOrHigher_3adf10(s32, s16, s32, s32);

s32 MenuCharaAbilityPageFill_3406a0(Obj *self, s32 arg1, s32 arg2)
{
    //DECLS
    s32 h;
    s32 tmp;
    Rect *tblA;
    Rect *tblB;
    s32 n;
    s16 *cur;
    s32 i;
    Res *r;
    Rect *a;
    Sub *b;
    Flag *c;
    u8 buf[0x18];
    Iter it;
    //ENDDECLS

    tmp = PartyGetSlotChara_3c2fb0(GetGameData_1fede0()->unk18, arg1);
    h = tmp;
    if (tmp == 0) {
        return 0;
    }
    CharaAbilityViewCtor_3a8180(buf, tmp, -1, -1);
    IterInit_370170(&it, buf);
    n = it.count;
    self->unk74 = n;
    cur = IterSeek_36fff0(&it, arg2);
    r = UiFindWidget_290460(self->unk5C, 0x197);
    if (r == NULL) {
        return 0;
    }
    tblA = r->unk20;
    if (tblA == NULL) {
        return 0;
    }
    r = UiFindWidget_290460(self->unk5C, 0x198);
    if (r == NULL) {
        return 0;
    }
    tblB = r->unk20;
    if (tblB == NULL) {
        return 0;
    }
    for (i = 0; i < 6; i++) {
        r = UiFindWidget_290460(self->unk5C, i + 0x191);
        if (r == NULL) {
            return 0;
        }
        a = r->unk20;
        if (a == NULL) {
            return 0;
        }
        b = r->unk24;
        if (b == NULL) {
            return 0;
        }
        c = r->unk28;
        if (c == NULL) {
            return 0;
        }
        c->xA = 2;
        if (i < n && cur != NULL) {
            MenuCharaAbilityRowSetup_3408e0(h, cur, a, b, c, &tblA[i]);
            if (CharaHasAbilityOrHigher_3adf10(h, *cur, 1, 1) != 0) {
                tblB[(u32)i].xE = 0;
                tblB[(u32)i].x6 = 0;
                tblB[(u32)i].xC = 0;
                tblB[(u32)i].x4 = 0;
            } else {
                tblB[(u32)i].xC = 0x1C;
                tblB[(u32)i].x4 = 0x1C;
                tblB[(u32)i].xE = 0xE;
                tblB[(u32)i].x6 = 0xE;
            }
        } else {
            c->x4 = 0;
            a->xE = 0;
            a->xC = 0;
            a->x6 = 0;
            a->x4 = 0;
            b->x18 = 0;
            b->x16 = 0;
            tblA[i].xE = 0;
            tblA[i].xC = 0;
            tblA[i].x6 = 0;
            tblA[i].x4 = 0;
            tblB[(u32)i].xE = 0;
            tblB[(u32)i].x6 = 0;
            tblB[(u32)i].xC = 0;
            tblB[(u32)i].x4 = 0;
        }
        cur = IterNext_370040(&it);
    }
    return 1;
}
