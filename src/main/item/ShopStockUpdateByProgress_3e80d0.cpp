#include "types.h"
#pragma optimization_level 3

class VObj {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25();
    virtual s32 check(s16);
};

struct Ent {
    s16 m0;
    s16 m2;
    s16 m4;
    u8 f : 1;
    u8 n : 7;
    u8 pad7;
    s16 *m8;
};

struct Head {
    u8 pad0[8];
    s16 m8;
    s16 mA;
    Ent *mC;
};

extern "C" {
extern s32 ShopCalcProgressLevel_3e8360(u8 *);
extern s32 ShopLevelGet_3cbce0(u8 *, s32);
extern void ShopLevelSet_3cbcb0(u8 *, s32, s32);
extern s32 ShopStockGet_3cbc80(u8 *, s32);
extern void ShopStockSet_3cbc50(u8 *, s32, s32);
}

static inline void clamp(s32 &x) {
    if (x < 0) {
        x = 0;
    } else if (x > 99) {
        x = 99;
    }
}

extern "C" s32 ShopStockUpdateByProgress_3e80d0(u8 *arg0) {
    u8 *o;
    s32 cur;
    s32 prev;
    bool changed;
    Head *h;
    Ent *e;
    s32 i;
    s32 n;
    s32 r;

    if (*(s32 *)(arg0 + 0x18) == 0) {
        return 0;
    }
    o = *(u8 **)(*(u8 **)(*(u8 **)(arg0 + 8) + 0xA8) + 0xC);
    h = (*(s16 *)(o + 0x7C) > 0) ? *(Head **)(o + 0x8C) : 0;
    if (*(s16 *)(o + 0x7C) <= 0 || h == 0) {
        return 0;
    }
    cur = ShopCalcProgressLevel_3e8360(arg0);
    r = ShopLevelGet_3cbce0(*(u8 **)(arg0 + 0x10), h->m8);
    prev = r;
    if (r < 0) {
        prev = -1;
    }
    changed = true;
    if (cur == prev) {
        changed = false;
    } else if (cur < prev) {
        prev = -1;
    }
    if (changed) {
    ShopLevelSet_3cbcb0(*(u8 **)(arg0 + 0x10), h->m8, cur);
    n = h->mA;
    e = h->mC;
    for (i = 0; i < n; i++, e++) {
        s32 v;
        s32 j;
        if ((*(VObj **)(*(u8 **)(*(u8 **)(arg0 + 8) + 0x40) + 8))->check(e->m2) == 0) {
            continue;
        }
        v = ShopStockGet_3cbc80(*(u8 **)(arg0 + 0x10), e->m4);
        clamp(v);
        for (j = prev + 1; j <= cur; j++) {
            s32 k;
            if (j < 0) {
                continue;
            }
            if (j >= e->n) {
                continue;
            }
            k = e->m8[j];
            if (k == -1) {
                v = -1;
            } else if (k == 0) {
                v = 0;
            } else if (k == 100) {
                v = 100;
            } else if (k == -2) {
                v = -2;
            } else if (k == -3) {
                v = -3;
            } else if (k != 0x7F) {
                if (k > 1000) {
                    v += k % 1000;
                    clamp(v);
                } else if (k > 0) {
                    v = k;
                    clamp(v);
                }
            }
        }
        ShopStockSet_3cbc50(*(u8 **)(arg0 + 0x10), e->m4, v);
    }
    }
    return 1;
}
