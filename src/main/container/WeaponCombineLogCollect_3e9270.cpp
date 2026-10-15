#include "types.h"
#pragma optimization_level 3
#pragma opt_propagation off
#pragma opt_repositioncode off
#pragma opt_common_subs off
#undef NULL
#define NULL 0
struct E6 {
    u8 x0;
    u8 x1;
    u8 x2;
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
    u8 b4 : 1;
    s16 x4;
};
struct H8 {
    u8 x0;
    u8 n;
    u8 pad[2];
    E6 *e;
};
extern "C" {
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
    virtual s32 f(s32);
};
s32 WeaponCombineLogFind_3cbf10(s32, s16, s32);
s32 WeaponCombineFillRowMaybe_3cd910(s32, s32, void *);
H8 *ListFindByKey_407ee0(s32, s32);

#define G90(a) (*(u8 **)(*(u8 **)((u8 *)(a) + 0x8) + 0x90))

s32 WeaponCombineLogCollect_3e9270(void *arg0, s16 arg1, s32 arg2) {
    s32 t;
    H8 *h;
    s32 cnt;
    s32 n;
    s32 q;
    E6 *e;
    s32 i;
    s32 r;
    s16 k;

    *(u16 *)(G90(arg0) + 0x14) = 0;
    t = (*(VC_0 **)(G90(arg0) + 0xC))->f(arg1);
    if (t == 0) {
        return 0;
    }
    h = ListFindByKey_407ee0(t, arg2);
    if (h == NULL) {
        return 0;
    }
    cnt = 0;
    n = h->n;
    e = h->e;
    q = *(s32 *)(G90(arg0) + 0x18);
    for (i = 0; i < n; i++, e++) {
        k = e->x4;
        r = WeaponCombineLogFind_3cbf10(*(s32 *)((u8 *)arg0 + 0x10), k, e->b4 != 0);
        if (r != 0) {
            WeaponCombineFillRowMaybe_3cd910(r, q, h);
            cnt++;
            q += 0x1C;
        }
    }
    *(u16 *)(G90(arg0) + 0x14) = cnt;
    return cnt;
}
}
