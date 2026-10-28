#include "types.h"



struct Item {
    u8 pad[0x16];
    s16 h16;
    u8 pad18[2];
    s16 h1A;
    s16 h1C;
    s16 h1E;
    s8 c20[5];
    s8 c25[5];
    s8 c2A[8];
};
struct S16p { s16 v; s16 pad; };
class ItemTbl {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Item * Get(s16 a0) { return VCM(Item *, (void *, s16), 0x70, a0); }
};
struct G58 { u8 pad[8]; ItemTbl *f8; };
struct G { u8 pad[0x58]; G58 *f58; };
class Unit {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 Has(s32 a0) { return VCM(s32, (void *, s32), 0x19C, a0); }
    u8 pad4[0x18];
    u32 f1C;
    s32 f20;
    u8 pad24[6];
    s16 h2A;
    u16 h2C;
    u16 h2E;
    u8 pad30[0x26];
    S16p x56[5];
    S16p x6A[8];
    u8 pad8A[0x1DA - 0x8A];
    s16 h1DA;
    u8 pad1DC[0x23C - 0x1DC];
    s16 h23C;
    s16 h23E;
    u8 pad240[0x266 - 0x240];
    S16p a266[5];
};

extern "C" s32 UnitBaseApplyStatMods_3b82a0(void);
extern "C" volatile s32 D_00465C38[];
extern "C" s32 D_00465C40[];
extern "C" volatile s32 D_00465C48[];
extern "C" volatile s32 D_00465C50[];
extern "C" volatile s32 D_00465C58[];
extern "C" volatile s32 D_00465C60[];
extern "C" volatile s32 D_00465C68[];
extern "C" volatile s32 D_00465C70[];
extern "C" volatile s32 D_00465C78[];
extern "C" G *D_0048381C;

static inline Item *GetItem(s32 i) {
    ItemTbl *t = D_0048381C->f58->f8;
    Item *r;
    if (t != 0) r = t->Get(i);
    else r = 0;
    return r;
}
static inline s32 AddMax(s32 v, s32 d, s32 max) {
    if (d < 0) {
        v += d;
        if (v < 0) return 0;
        return v;
    } else if (d > 0) {
        v += d;
        if (v > max) v = max;
    }
    return v;
}
static inline s32 AddMinMax(s32 v, s32 d, s32 min, s32 max) {
    if (d < 0) {
        v += d;
        if (v < min) v = min;
    } else if (d > 0) {
        v += d;
        if (v > max) v = max;
    }
    return v;
}

extern "C" s32 UnitApplyStatusStatMods_3be050(Unit *u) {
    s32 i;
    s32 max20;
    s32 max23E;
    s32 max2E;
    s32 max266;
    s32 min56;
    s32 max56;
    s32 min6A;
    s32 max6A;
    s32 j;
    Item *it;
    s32 v;
    s16 *p;

    if ((UnitBaseApplyStatMods_3b82a0() & 0xFF) == 0) return 0;
    i = 2;
    max20 = D_00465C38[0];
    max23E = D_00465C48[0];
    max2E = D_00465C50[0];
    max266 = D_00465C58[0];
    min56 = D_00465C68[0];
    max56 = D_00465C60[0];
    min6A = D_00465C78[0];
    max6A = D_00465C70[0];
    for (; i < 0x30; i++) {
        if (u->Has(i) == 0) continue;
        it = GetItem(i);
        if (it == 0) continue;
        v = u->f20;
        v = AddMax(v, (s32)((f32)u->f1C * (it->h16 / 100.0f)), max20);
        u->f20 = v;
        v = u->h2A;
        v = AddMax(v, it->h1A, 100);
        u->h2A = v;
        v = u->h23E;
        v = AddMax(v, (s32)((f32)u->h23C * (it->h1C / 100.0f)), max23E);
        u->h23E = v;
        v = u->h2E;
        v = AddMax(v, (s32)((f32)(u32)u->h2C * (it->h1E / 100.0f)), max2E);
        u->h2E = v;
        j = 0;
        do {
            p = &u->a266[j].v;
            v = AddMax(*p, it->c20[j], max266);
            j++;
            *p = v;
        } while (j < 5);
        j = 0;
        do {
            p = &u->x56[j].v;
            v = AddMinMax(*p, it->c25[j], min56, max56);
            j++;
            *p = v;
        } while (j < 5);
        j = 0;
        do {
            p = &u->x6A[j].v;
            v = AddMinMax(*p, it->c2A[j], min6A, max6A);
            j++;
            *p = v;
        } while (j < 8);
    }
    u->h1DA = 0;
    if (u->f20 > (u32)max20) u->f20 = max20;
    if (u->h2A > D_00465C40[0]) u->h2A = D_00465C40[0];
    if (u->h23E > max23E) u->h23E = max23E;
    if (u->h2E > max2E) u->h2E = max2E;
    for (j = 0; j < 5; j++) {
        if (u->a266[j].v > max266) u->a266[j].v = max266;
    }
    for (j = 0; j < 5; j++) {
        if (u->x56[j].v >= max56) u->x56[j].v = max56;
        else if (u->x56[j].v < min56) u->x56[j].v = min56;
    }
    for (j = 0; j < 8; j++) {
        if (u->x6A[j].v >= max6A) u->x6A[j].v = max6A;
        else if (u->x6A[j].v < min6A) u->x6A[j].v = min6A;
    }
    return 1;
}
