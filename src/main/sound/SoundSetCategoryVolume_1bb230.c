#pragma optimization_level 3
#include "types.h"
#pragma divbyzerocheck on

typedef struct {
    void *p;
    s32 m4;
    s32 m8;
    u8 mC;
    u8 mD;
    u8 padE[6];
    s32 m14;
} Out;

extern u8 D_0049E884[];
extern u8 D_0049E88C[];
extern u8 D_0049E898[];
extern u8 D_0049E89E[];
extern u8 D_0049E89F[];
extern u8 D_0049E8A0[];
extern u8 D_0049E8A4[];
extern u8 D_0049E8A8[];
extern u8 D_004A1B90[];
extern u8 D_004A1BC0[];

#define R32(t, i) (*(s32 *)((t) + (i) * 0x24))

static s32 SoundCategoryGetChanMapMaybe_1bab00(s32 id, Out *o)
{
    s32 *p4;
    s32 *p8;
    s32 n;

    o->mC = 0;
    o->mD = 0;
    p4 = &o->m4;
    p8 = &o->m8;
    if (D_0049E884[0] != 0) {
        if (id < 0 || id >= 0x10) {
            return 0;
        }
        o->m4 = R32(D_0049E8A4, id);
        o->m8 = R32(D_0049E8A8, id);
        o->mC = D_0049E89E[id * 0x24];
        o->mD = D_0049E89F[id * 0x24];
    } else {
        switch (id) {
        case 0:
            *p4 = 0;
            *p8 = 0;
            o->mC = 1;
            break;
        case 11:
            *p4 = 3;
            *p8 = 3;
            o->mC = 1;
            break;
        case 1:
            *p4 = 0xC;
            *p8 = -1;
            break;
        case 2:
            *p4 = 1;
            *p8 = 1;
            break;
        case 3:
            *p4 = 6;
            *p8 = -1;
            break;
        case 4:
            *p4 = 0xB;
            *p8 = 2;
            break;
        case 5:
            *p4 = 0xA;
            *p8 = -1;
            break;
        case 6:
            *p4 = 9;
            *p8 = -1;
            break;
        case 7:
            *p4 = 5;
            *p8 = -1;
            break;
        case 8:
            *p4 = 8;
            *p8 = 0xD;
            o->mC = 1;
            break;
        case 9:
            *p4 = 4;
            *p8 = -1;
            break;
        case 10:
            *p4 = 7;
            *p8 = -1;
            o->mD = 1;
            o->m14 = 0;
            break;
        default:
            return 0;
        }
    }
    o->m14 = R32(D_0049E88C, id);
    n = R32(D_0049E898, id);
    if (n >= 0) {
        id = n;
    }
    if (R32(D_0049E8A0, id) > 0) {
        o->p = D_004A1BC0 + id * 0x28;
    } else {
        o->p = D_004A1B90;
    }
    return 1;
}

typedef struct Info {
    Out o;
    u8 pad18[0x148];
} Info;

typedef struct Slot {
    s16 id;
    s16 pad2;
    s32 pad4;
} Slot;

typedef struct Chan {
    u8 pad0[8];
    s32 unk8;
    u8 padC[0x14C];
    s32 unk158;
    u8 pad15C[0x84];
} Chan;

extern f32 D_004A1B10[];
extern f32 D_004A1B50[];
extern s32 D_004A1E40[];
extern Chan D_0049EB10[];
extern void SoundSendCmd_1b6cc0(s32, s32, s32, s32);

static inline Chan *get_chan(s32 i)
{
    if (i < 0 || i > 16) {
        return NULL;
    }
    return &D_0049EB10[i];
}

void SoundSetCategoryVolume_1bb230(s32 idx, f32 vol)
{
    Slot slots[16];
    Info info;
    Slot *p;
    s32 v;
    s32 k;
    Chan *c;
    s32 w;
    Out *o;

    if (idx < 0 || idx >= 16) {
        return;
    }
    p = slots;
    do {
        p->id = -1;
        p++;
    } while (p < &slots[16]);
    SoundCategoryGetChanMapMaybe_1bab00(idx, &info.o);
    o = &info.o;
    if (vol < 0.0f) {
        vol = 0.0f;
    }
    if (!(vol <= 1.0f)) {
        vol = 1.0f;
    }
    D_004A1B10[idx] = vol;
    v = (s32)(127.0f * (vol * D_004A1B50[idx]));
    if (o->m4 >= 0 && (u32)o->m4 < 16) {
        D_004A1E40[o->m4] = v;
    }
    k = o->m8;
    if (k < 0) {
        return;
    }
    if ((u32)k >= 16) {
        return;
    }
    D_004A1E40[k] = v;
    c = get_chan(idx);
    if (c == NULL) {
        return;
    }
    k = c->unk8;
    w = c->unk158;
    if (k >= 0 && (u32)k < 16) {
        w = w * D_004A1E40[k] / 127;
    }
    SoundSendCmd_1b6cc0(0x12, 2, k, w);
}
