#include "types.h"
#pragma opt_propagation off

struct P8 {
    s32 a;
    s32 b;
};

struct Arr8 {
    P8 e[8];
};

struct Hit {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xC;
    Arr8 arr;
    s32 x50;
    s32 x54;
    u8 pad58[0x14];
};

struct Rec {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xC;
    Arr8 arr;
    s32 x50;
    s32 x54;
    u8 pad58[8];
};

struct Item {
    u8 pad0[0x34];
    void *x34;
    s32 x38;
};

struct Owner {
    u8 pad0[0x32];
    s16 x32;
    u8 pad34[0x38];
    s8 x6C;
    u8 pad6D[0xA7];
    s32 x114;
};

struct Self {
    u8 pad0[0x51C];
    s32 x51C;
    Owner **x520;
    u8 pad524[0x113C];
    s32 x1660;
    s32 x1664;
};

extern "C" {
void FuncDataTableIterBegin_1908e0(void *, s32);
Item *FuncDataTableIterNext_1908b0(void *);
void FuncDataTableIterEnd_1908a0(void *);
s32 FuncDataRecVolumeContainsPointMaybe_187080(Item *, s32, s32, Hit *, s32 *);
void NodeCalcWorldMatrixThunk_186130(Owner *, void *);
void MtxIdentity_13d2e0(void *);
}

static inline void setRec(Rec *r, Hit *h)
{
    r->x0 = h->x0;
    r->x4 = h->x4;
    r->arr = h->arr;
    r->x50 = h->x50;
    r->x54 = h->x54;
}

extern "C" s32 MapAreaModelQueryVolumesAtPointMaybe_187740(Self *self, s32 arg1, s32 arg2, Item **out, Rec *recs, s32 max)
{
    //DECLS
    s32 extra;
    Hit hit __attribute__((aligned(16)));
    u8 buf110[0x40] __attribute__((aligned(16)));
    u8 bufD0[0x40] __attribute__((aligned(16)));
    s32 count;
    Item *it;
    s32 n;
    Owner **arr;
    s32 i;
    Owner *o;
    s32 *cont;
    s32 r;
    Rec *rec;
    //ENDDECLS

    count = 0;
    FuncDataTableIterBegin_1908e0(&self->x1664, 6);
    while ((it = FuncDataTableIterNext_1908b0(&self->x1664)) != 0) {
        if (count >= max) {
            break;
        }
        if (FuncDataRecVolumeContainsPointMaybe_187080(it, arg1, arg2, &hit, &extra)) {
            out[count] = it;
            rec = &recs[count];
            setRec(rec, &hit);
            count++;
        }
    }
    FuncDataTableIterEnd_1908a0(&self->x1664);
    n = self->x51C;
    arr = self->x520;
    if (self->x1660 != 0) {
        for (i = 0; i < n; i++) {
            o = arr[i];
            if (o == 0) {
                continue;
            }
            cont = &o->x114;
            if (!(o->x114 & 0x100)) {
                continue;
            }
            {
                bool z = o->x6C == 0;
                if (z) {
                    continue;
                }
            }
            if (o->x32 == 0) {
                continue;
            }
            NodeCalcWorldMatrixThunk_186130(o, buf110);
            MtxIdentity_13d2e0(bufD0);
            FuncDataTableIterBegin_1908e0(cont, 6);
            while ((it = FuncDataTableIterNext_1908b0(cont)) != 0) {
                it->x34 = o;
                it->x38 = 0;
                r = FuncDataRecVolumeContainsPointMaybe_187080(it, arg1, arg2, &hit, &extra);
                it->x34 = 0;
                it->x38 = 0;
                if (count >= max) {
                    break;
                }
                if (r) {
                    out[count] = it;
                    rec = &recs[count];
                    setRec(rec, &hit);
                    count++;
                    rec->x50 = i;
                }
            }
            FuncDataTableIterEnd_1908a0(cont);
        }
    }
    return count;
}
