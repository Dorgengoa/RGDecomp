#include "types.h"

struct VObj {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(u8 *, s32);
    virtual void v5();
    virtual void v6(u8 *, s32);
};

typedef struct Bits {
    u8 b0 : 1;
    u8 rest : 7;
} Bits;

typedef struct Loader {
    u8 pad000[0x2C];
    s16 x2C;
    Bits x2E;
    u8 pad02F;
    s16 x30;
    s16 x32;
    s16 x34;
    s16 x36;
    u8 pad038[0xE0];
    s64 x118;
    s32 x120;
    s32 x124;
    f32 x128;
    f32 x12C;
    f32 x130;
    f32 x134;
    f32 x138;
    s16 x13C;
    u8 pad13E[2];
    s32 x140;
    u8 pad144[0xC];
    s32 x150;
    s32 x154;
    s32 x158;
    s32 x15C;
    u8 pad160[8];
    void *x168;
    u8 pad16C[8];
    void *x174;
    u8 pad178[4];
    void *x17C;
    u8 pad180[0x4B20];
    s16 x4CA0;
} Loader;

extern "C" {
s32 UnpackWordTriple_370d70(u8 *, s32, s32 *, s32 *, s32 *);
void PoolClear_36ade0(void *);
VObj *InvObjCreateByKind_3c75c0(Loader *, s32);
void *InvFindByRecKey_3c8140(Loader *, s32, s32, s32, s32);
void PartyResetZoneListsMaybe_3cb210(Loader *, s32);
void *InvObjCastToCage_3d3c80(void *);
void InsectRecSlotsResolve_3cfbd0(void *);
void *memcpy(void *, const void *, u32);
extern s32 D_004658F8[];
extern f32 D_00465940[];
extern s32 D_00465B50[];
extern s32 D_00465B70[];
s32 PartyDeserialize_3bf4f0(Loader *self, u8 *p, s32 rem);
}

static inline void *find(Loader *self, s32 i) {
    void *o = InvFindByRecKey_3c8140(self, 12, 0x4B1, i, 0);
    if (o == 0) {
        o = InvFindByRecKey_3c8140(self, 12, 0x4B1, i, 9);
        if (o == 0) {
            return 0;
        }
    }
    return InvObjCastToCage_3d3c80(o);
}

s32 PartyDeserialize_3bf4f0(Loader *self, u8 *arg1, s32 arg2) {
    u8 *p;
    s32 rem;
    s32 type;
    s32 id;
    s32 len;
    s32 type2;
    s32 id2;
    s32 len2;
    s32 total;
    s32 n;
    s32 on;
    f32 fv;
    s32 i;
    u8 *q;
    s32 r;
    s32 max;
    s32 m;
    VObj *o;
    void *x;


    if (arg1 == 0 || arg2 <= 0) {
        return 0;
    }
    p = arg1;
    rem = arg2;
    total = 0;
    if (D_004658F8[0] < rem) {
        return 0;
    }
    fv = D_00465940[0];
    on = D_00465B50[0];
    max = D_00465B70[0] * 4;
    while (rem > 0) {
        type = 0;
        id = 0;
        len = 0;
        n = UnpackWordTriple_370d70(p, rem, &type, &id, &len);
        if (n <= 0) {
            break;
        }
        total += n;
        rem -= n;
        p += n;
        switch (type) {
        case 9:
            ((VObj *)self)->v6(p, len);
            self->x2C = -1;
            self->x2E.b0 = 0;
            self->x30 = -1;
            self->x4CA0 = -1;
            self->x32 = -1;
            self->x34 = 1;
            self->x36 = 1;
            PartyResetZoneListsMaybe_3cb210(self, 0);
            self->x118 = 0;
            self->x120 = 0;
            self->x124 = 0;
            self->x128 = fv;
            self->x12C = fv;
            self->x130 = fv;
            self->x134 = fv;
            self->x138 = 11.0f;
            self->x13C = 0;
            self->x140 = 0;
            self->x150 = 0;
            self->x154 = 0;
            self->x158 = 0;
            self->x15C = 0;
            break;
        case 12:
            n = 0x33C0;
            if (rem < 0x33C0) {
                n = rem;
            }
            memcpy(self->x174, p, n);
            break;
        case 10:
            PoolClear_36ade0(self->x168);
            r = len;
            q = p;
            while (r > 0) {
                type2 = 0;
                id2 = 0;
                len2 = 0;
                m = UnpackWordTriple_370d70(q, r, &type2, &id2, &len2);
                if (m <= 0) {
                    break;
                }
                r -= m;
                q += m;
                if (type2 == 11 && on > 0) {
                    o = InvObjCreateByKind_3c75c0(self, id2);
                    if (o != 0) {
                        o->v4(q, len2);
                    }
                }
                r -= len2;
                q += len2;
            }
            break;
        case 13:
            n = max;
            if (rem < max) {
                n = rem;
            }
            memcpy(self->x17C, p, n);
            break;
        }
        total += len;
        rem -= len;
        p += len;
    }
    for (i = 0; i < 3; i++) {
        x = find(self, i);
        if (x != 0) {
            InsectRecSlotsResolve_3cfbd0(x);
        }
    }
    return total;
}
