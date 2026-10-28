/* rgp:protos */
#line 1
#include "types.h"

struct Elem {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 pad6;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
};

struct Obj {
    s16 unk0;
    u8 pad2[0x2C - 2];
    s16 unk2C;
    u8 pad2e[0x30 - 0x2e];
    f32 unk30;
    f32 unk34;
    f32 unk38;
    s16 unk3C;
    u8 pad3e[0x40 - 0x3e];
    u8 b0 : 1;
    u8 rest : 7;
};

extern "C" {
Obj * SkillActionFindById_3e0ee0(int);
extern Elem D_004E9800[0x40];
}

extern "C" s32 SkillTimerStartMaybe_3e0c70(int rgp_a0)
{
    Obj *o;
    Elem *found;
    Elem *e;
    Elem *best;
    f32 maxv;
    f32 m;
    f32 t;
    f32 t2;
    f32 b;
    s32 i;

    o = SkillActionFindById_3e0ee0((int)rgp_a0);
    if (o == 0) {
        return 0;
    }
    if (o->unk0 < 0) {
        return 0;
    }
    o->b0 = 1;
    if (o->unk30 <= 0.0f && o->unk34 <= 0.0f && o->unk38 <= 0.0f) {
        return 1;
    }
    found = 0;
    e = D_004E9800;
    best = 0;
    maxv = 0.0f;
    for (i = 0; i < 0x40; i++, e++) {
        if (e->unk0 < 0) {
            found = e;
            break;
        }
        b = e->unk8;
        t = b - e->unk10;
        t2 = b - e->unk14;
        m = b - e->unkC;
        if (m < t) {
            m = t;
        }
        if (m < t2) {
            m = t2;
        }
        if (best != 0) {
            if (!(maxv <= m)) {
                maxv = m;
                best = e;
            }
        } else {
            maxv = m;
            best = e;
        }
    }
    if (found == 0) {
        found = best;
    }
    if (found == 0) {
        return 0;
    }
    found->unk0 = o->unk0;
    found->unk2 = o->unk3C;
    found->unk4 = o->unk2C;
    found->unk8 = 0.0f;
    found->unkC = o->unk30;
    found->unk10 = o->unk34;
    found->unk14 = o->unk38;
    return 1;
}
