#include "types.h"

struct Ent {
    u8 pad0[0xA];
    u8 b0 : 1;
    u8 b1 : 1;
};

struct Info {
    u8 pad0[0x14];
    s8 m14;
    s8 m15;
};

class VC_0 {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual Info *f(s16 id);
};

struct Holder {
    u8 pad0[8];
    VC_0 *m8;
};

struct Mgr {
    u8 pad0[0x40];
    Holder *m40;
};

struct Self {
    u8 pad0[0x168];
    s32 m168;
};

extern "C" {
Ent *InvFindByInvId_3c87d0(Self *, s32, s32);
extern s32 D_00465A08[];
extern s32 D_00465A10[];
extern s32 D_00465A38[];
extern s32 D_00465A40[];
extern s32 D_00465A58[];
extern s32 D_00465A60[];
extern s32 D_00465A70[];
extern s32 D_00465A78[];
extern s32 D_00465A88[];
extern s32 D_00465A90[];
extern s32 D_00465AA8[];
extern s32 D_00465AB0[];
extern s32 D_00465AC8[];
extern s32 D_00465AD0[];
extern s32 D_00465AE8[];
extern s32 D_00465AF0[];
extern s32 D_00465B00[];
extern s32 D_00465B08[];
extern s32 D_00465B30[];
extern s32 D_00465B38[];
extern s32 D_00465B40[];
extern s32 D_00465B48[];
extern Mgr *D_00483894;
s32 InvFindFreeSlotId_3c4900(Self *self, s32 id, s32 kind);
}

s32 InvFindFreeSlotId_3c4900(Self *self, s32 id, s32 kind)
{
    Info *info;
    s32 start;
    s32 end;
    s32 result;
    s32 s;
    Ent *e;

    if (self->m168 == 0) {
        return -1;
    }
    if (D_00483894 == 0) {
        return -1;
    }
    if (id < 0) {
        return -1;
    }
    info = D_00483894->m40->m8->f(id);
    if (info == 0) {
        return -1;
    }
    if (kind != 8) {
        if (info->m14 >= 0) {
            kind = info->m14;
        }
    }
    start = -1;
    end = -1;
    switch (kind) {
    case 0:
        start = D_00465A08[0];
        end = D_00465A10[0];
        break;
    case 1:
        start = D_00465A38[0];
        end = D_00465A40[0];
        break;
    case 10:
        start = D_00465B40[0];
        end = D_00465B48[0];
        break;
    case 2:
        if (info->m14 == kind) {
            s = info->m15;
            if (s >= 0 && s < D_00465A58[0]) {
                start = D_00465A60[0] + s;
                end = start;
            }
        }
        break;
    case 3:
        if (info->m14 == kind) {
            s = info->m15;
            if (s >= 0 && s < D_00465A70[0]) {
                start = D_00465A78[0] + s;
                end = start;
            }
        }
        break;
    case 4:
        if (info->m14 == kind) {
            s = info->m15;
            if (s >= 0 && s < D_00465A88[0]) {
                start = D_00465A90[0] + s;
                end = start;
            }
        }
        break;
    case 5:
        start = D_00465AA8[0];
        end = D_00465AB0[0];
        break;
    case 6:
        if (info->m14 == kind) {
            s = info->m15;
            if (s >= 0 && s < D_00465AC8[0]) {
                start = D_00465AD0[0] + s;
                end = start;
            }
        }
        break;
    case 7:
        start = D_00465AE8[0];
        end = D_00465AF0[0];
        break;
    case 8:
        start = D_00465B00[0];
        end = D_00465B08[0];
        break;
    case 9:
        start = D_00465B30[0];
        end = D_00465B38[0];
        break;
    default:
        return -1;
    }
    result = -1;
    if (start >= 0 && end >= 0) {
        for (; start <= end; start++) {
            e = InvFindByInvId_3c87d0(self, start, 0);
            if (e == 0) {
                result = start;
                break;
            }
            if (e->b1) {
                if (result < 0) {
                    result = start;
                }
            }
        }
    }
    return result;
}
