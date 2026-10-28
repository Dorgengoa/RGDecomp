/* rgp:protos */
#line 1
#include "types.h"
//PRAGMA

struct Item {
    u8 pad0[0x1E];
    s8 x1E;
};

class VObj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Item * get(s16 a0) { return VCM(Item *, (void *, s16), 0x70, a0); }
};

struct Holder {
    u8 pad0[8];
    VObj *obj;
};

struct Entry {
    s16 x0;
    s16 x2;
    s16 x4;
    s16 x6;
    s32 x8;
};

struct List {
    u8 pad0[0xA];
    s16 n;
    Entry *e;
};

struct Sub {
    u8 pad0[0x7C];
    s16 count;
    u8 pad7E[0xE];
    List *list;
};

struct Mgr {
    u8 pad0[0xC];
    Sub *sub;
    s16 x10;
};

struct Ctx {
    u8 pad0[0x40];
    Holder *h;
    u8 pad44[0x64];
    Mgr *mgr;
};

struct Tm {
    u8 pad0[8];
    s64 x8;
};

struct Self {
    u8 pad0[8];
    Ctx *ctx;
    Tm *tm;
    s32 x10;
    u8 pad14[4];
    s32 x18;
};

extern "C" {
void InvFreeCategory8Items_3c8d70(s32);
s32 ShopCalcProgressLevel_3e8360(Self *);
unsigned long long DoubleToU64_13ab28(double);
double U64ToDouble_100370(unsigned long long);
s32 ShopStockGet_3cbc80(s32, s32);
void *ShopRowGet_4244b0(Mgr *, s32);
s32 ItemGroupUnlockProgressGet_3cbc20(s32, s32);
double ItemGroupUnlockTimeGet_3cbbb0(s32, s32);
s32 DoubleGreaterEqual_100230(double, double);
s32 DoubleLess_1002b0(double, double);
double dpsub(double, double);
s32 ShopRowFill_3ce980(void *, Entry *, s32, s32);
}

static inline List *getList(Sub *s)
{
    if (s->count > 0) {
        return s->list;
    }
    return 0;
}

extern "C" s32 ShopListBuild_3e7e30(Self *self)
{
    //DECLS
    Sub *sub;
    List *list;
    s32 now;
    s64 d;
    Entry *e;
    s32 count;
    s32 n;
    s32 i;
    Item *item;
    s32 st;
    bool ok;
    void *tgt;
    s32 mode;
    s32 t;
    s64 rate;
    //ENDDECLS

    InvFreeCategory8Items_3c8d70(self->x18);
    if (self->x18 == 0) {
        return 0;
    }
    sub = self->ctx->mgr->sub;
    list = getList(sub);
    if (sub->count <= 0 || list == 0) {
        return 0;
    }
    now = ShopCalcProgressLevel_3e8360(self);
    d = ((s64)__builtin_bit_cast(long long, U64ToDouble_100370((unsigned long long)(DoubleToU64_13ab28(__builtin_bit_cast(double, (long long)(self->tm->x8)))))));
    count = 0;
    n = list->n;
    e = list->e;
    for (i = 0; i < n; i++, e++) {
        item = self->ctx->h->obj->get(e->x2);
        if (item == 0) {
            continue;
        }
        st = ShopStockGet_3cbc80(self->x10, e->x4);
        ok = false;
        if (st > 0 && st < 100) {
            ok = true;
        } else if (st == 0) {
            ok = true;
        } else if (st == 100) {
            ok = true;
        } else if (st == -2) {
            ok = true;
        } else if (st == -3) {
            ok = true;
        }
        if (!ok) {
            continue;
        }
        tgt = ShopRowGet_4244b0(self->ctx->mgr, count);
        if (tgt == 0) {
            continue;
        }
        mode = 1;
        if (st == -2) {
            mode = 2;
            st = 0;
        } else if (st == -3) {
            mode = 3;
            st = 0;
        }
        if (item->x1E >= 0) {
            t = ItemGroupUnlockProgressGet_3cbc20(self->x10, item->x1E);
            rate = ((s64)__builtin_bit_cast(long long, ItemGroupUnlockTimeGet_3cbbb0(self->x10, item->x1E)));
            if (t >= 0 && ((unsigned char)DoubleGreaterEqual_100230(__builtin_bit_cast(double, (long long)(rate)), __builtin_bit_cast(double, (long long)(0))))) {
                if (now - t < 0 && ((unsigned char)DoubleLess_1002b0(dpsub(__builtin_bit_cast(double, (long long)(d)), __builtin_bit_cast(double, (long long)(rate))), __builtin_bit_cast(double, (long long)(0))))) {
                    mode = 2;
                    st = 0;
                }
            } else {
                mode = 3;
                st = 0;
            }
        }
        if ((u8)ShopRowFill_3ce980(tgt, e, st, mode)) {
            count++;
        }
    }
    self->ctx->mgr->x10 = count;
    return 1;
}
