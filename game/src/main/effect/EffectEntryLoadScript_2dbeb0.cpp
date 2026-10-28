#include "types.h"

typedef struct H2dbeb0 {
    u8 pad0[0x28];
    s32 w28;
    s32 w2C;
    u8 pad30[4];
    s32 w34;
} H2dbeb0;

typedef struct A2dbeb0 {
    u8 pad0[0x88];
    s32 w88;
    s32 w8C;
    s32 w90;
    u8 pad94[0xC];
    s32 wA0;
    H2dbeb0 *pA4;
    u8 padA8[0xC];
    s16 hB4;
} A2dbeb0;

extern "C" s32 MemStackAllocAligned64_14da10(H2dbeb0 *, s32);
extern "C" void MemStackReturnToOwnerMaybe_14dad0(H2dbeb0 *);
extern "C" s32 MemStackHeapAlloc_14db10(H2dbeb0 *, s32, u32, s32);
extern "C" s32 MemStackNew_14e230(s32, H2dbeb0 *);
extern "C" s32 ScriptVmCtor_176be0(s32);
extern "C" s32 GetEffectMgr_2d9040(void);
extern "C" void *memcpy(void *, const void *, u32);
extern "C" volatile f32 D_0047D7A4;

static inline u32 blocks2dbeb0(u32 x)
{
    if (x & 0xF) {
        return (x >> 4) + 1;
    }
    return x >> 4;
}

static inline s32 busy2dbeb0(H2dbeb0 *h)
{
    return h->w28 != 0;
}

static inline bool bbusy2dbeb0(H2dbeb0 *h)
{
    return busy2dbeb0(h);
}

extern "C" s32 EffectEntryLoadScript_2dbeb0(A2dbeb0 *arg0, u8 *arg1, u32 arg2)
{
    H2dbeb0 *h;
    bool lk;
    bool b;
    f32 fb;
    s32 sz;
    s32 v;

    if (GetEffectMgr_2d9040() == 0) {
        return 1;
    }
    h = arg0->pA4;
    lk = !(bool)busy2dbeb0(h);
    if (lk) {
        arg0->w8C = MemStackHeapAlloc_14db10(h, 3, blocks2dbeb0(arg2), 0x40);
    } else {
        arg0->w8C = 0;
    }
    h = arg0->pA4;
    sz = h->w34 - h->w2C;
    fb = (f32)blocks2dbeb0(arg2 + 0x54);
    if (!(D_0047D7A4 * fb < (f32)sz)) {
        if (lk) {
            MemStackReturnToOwnerMaybe_14dad0(h);
        }
        return 1;
    }
    fb = (f32)blocks2dbeb0(arg2 + 0x54);
    arg0->wA0 = (s32)(D_0047D7A4 * fb);
    v = MemStackNew_14e230(0x54, arg0->pA4);
    if (v != 0) {
        v = ScriptVmCtor_176be0(v);
    }
    arg0->w88 = v;
    arg0->w90 = MemStackAllocAligned64_14da10(arg0->pA4, (s32)arg2 / 16 + 1);
    memcpy((void *)arg0->w90, arg1, arg2);
    if (lk) {
        MemStackReturnToOwnerMaybe_14dad0(arg0->pA4);
    }
    arg0->hB4 |= 2;
    return 0;
}
