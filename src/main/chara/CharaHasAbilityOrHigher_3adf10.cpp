#include "types.h"

class Getter {
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4C();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5C();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6C();
    virtual s32 get(s16);
};

struct Inner003ADF10 {
    s16 unk0;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
};

struct Elem003ADF10 {
    u8 pad0[4];
    Inner003ADF10 *unk4;
};

struct Sub44 {
    u8 pad0[0xC];
    Getter *unkC;
};

struct Obj0048381C_003ADF10 {
    u8 pad0[0x44];
    Sub44 *unk44;
};

struct Obj00449858_003ADF10 {
    u8 pad0[0xC];
    s32 unkC;
};

struct Obj003ADF10 {
    u8 pad0[0x230];
    s16 *unk230;
    u8 pad234[0x2E0 - 0x234];
    s64 unk2E0[1];
};

extern "C" {
void Abort_12de80();
void Fprintf_12f9a0(s32, void *);
Elem003ADF10 *AbilityListFindById_3f5780(s32, s32, s64 *);
extern Obj00449858_003ADF10 *D_00449858[];
extern u8 D_00465ED0[];
extern Obj0048381C_003ADF10 *D_0048381C;
}

typedef struct {
    s64 *volatile p;
    volatile u32 n;
} BitRef;

extern "C" bool CharaHasAbilityOrHigher_3adf10(Obj003ADF10 *arg0, s32 arg1, s32 arg2, u8 arg3)
{
    bool found;
    bool bit;
    Inner003ADF10 *last;
    s32 i;
    s32 h;
    Inner003ADF10 *in;
    Elem003ADF10 *e;
    BitRef r;

    if ((D_0048381C == 0) || (arg0->unk230 == 0)) return false;
    if ((h = D_0048381C->unk44->unkC->get(*arg0->unk230)) == 0) {
        return false;
    }
    found = false;
    last = 0;
    for (i = 0; i < 0x40; i++) {
        r.p = &arg0->unk2E0[arg3];
        r.n = i;
        if ((u32)i >= 0x40) {
            Fprintf_12f9a0(D_00449858[0]->unkC, D_00465ED0);
            Abort_12de80();
        }
        {
            s64 *q = r.p;
            bit = (*q & ((s64)1 << i)) != 0;
            e = AbilityListFindById_3f5780(h, i + 1, q);
        }
        if (e == 0) {
            continue;
        }
        in = e->unk4;
        if (in == 0) {
            continue;
        }
        if (in->unk0 == arg1) {
            last = in;
            if (bit) {
                found = true;
                break;
            }
            if (arg2 == 0) {
                break;
            }
        } else if (arg2 != 0 && last != 0 && bit && last->unk2 == in->unk2 &&
                   last->unk3 == in->unk3 && last->unk4 == in->unk4 && last->unk5 < in->unk5) {
            found = true;
            break;
        }
    }
    return found;
}
