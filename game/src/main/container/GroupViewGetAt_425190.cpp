#include "types.h"

struct Sub00425190 {
    u8 pad0[0x44];
};

struct Elem00425190 {
    u8 pad0[0x7C];
    s16 unk7C;
    u8 pad7E[0x8C - 0x7E];
    Sub00425190 *unk8C;
    u8 pad90[0x94 - 0x90];
    s32 unk94;
};

struct Tbl00425190 {
    u8 pad0[8];
    Elem00425190 *unk8;
    Elem00425190 *get(s32 i) {
        Elem00425190 *r;
        if (i >= 0) {
            if (i >= 2) {
                r = 0;
            } else {
                r = &unk8[i];
            }
        } else {
            r = 0;
        }
        return r;
    }
};

struct Obj00425190 {
    u8 pad0[4];
    Tbl00425190 *unk4;
    s16 unk8;
    s32 unkC;
};

extern "C" {
extern s32 GroupEntryMatchesKey_3f41b0(s32, s32);
extern s32 SavePointIsActivated_426510(Sub00425190 *);
}

extern "C" Sub00425190 *GroupViewGetAt_425190(Obj00425190 *arg0, s32 arg1)
{
    s32 count;
    s32 i;
    Elem00425190 *e;
    s32 n;
    s32 j;
    Sub00425190 *p;
    bool ok;

    if (arg0->unk4 == 0) {
        return 0;
    }
    count = 0;
    for (i = 0; i < 2; i++) {
        e = arg0->unk4->get(i);
        if (e == 0) {
            continue;
        }
        if (e->unk94 == 0) {
            continue;
        }
        if (GroupEntryMatchesKey_3f41b0(e->unk94, arg0->unk8) == 0) {
            continue;
        }
        n = e->unk7C;
        for (j = 0; j < n; j++) {
            p = &e->unk8C[j];
            if (p == 0) {
                break;
            }
            ok = true;
            if (arg0->unkC == 1 && SavePointIsActivated_426510(p) == 0) {
                ok = false;
            }
            if (!ok) {
                continue;
            }
            if (count == arg1) {
                return p;
            }
            count++;
        }
    }
    return 0;
}
