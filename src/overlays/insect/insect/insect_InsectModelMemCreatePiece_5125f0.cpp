#include "types.h"
/* insect 0x005125F0 -- C++ virtual dispatch, vptr at +0x1B0, slot 0x5C =
 * virtual #21.  [[jalr-is-cpp-virtual]]  The 0x790-byte allocation, the
 * inlined vptr store of D_00470F50 and the 0x88-byte descriptor handed to
 * func_1AFD00 are the same shape as factory 0x00504250. */

class VE {
public:
    u8 pad000[0x1B0];
    virtual void s00(); virtual void s01(); virtual void s02();
    virtual void s03(); virtual void s04(); virtual void s05();
    virtual void s06(); virtual void s07(); virtual void s08();
    virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18(); virtual void s19(); virtual void s20();
    virtual void s21();               /* slot 0x5C */
};

struct Ent {
    u8  pad000[0x58];
    s32 f58;
};

struct A {
    void *f000;
    u8    f004[0x64 - 4];
    Ent   ent[10];
    u8    pad3FC[4];
    s16   w400[1];
};

struct W {
    u8   pad000[0x1E4];
    char f1E4[1];
};

struct Desc {
    void *f00;
    void *f04;
    void *f08;
    void *f0C;
    void *f10;
    s32   f14;
    s32   f18;
    u8    pad1C[0x2C - 0x1C];
    void *f2C;
    s32   f30;
    u8    pad34[4];
    void *f38;
    s32   f3C;
    u8    b40[0x20];
    u8    b60[0x28];
    u8    b88[0x14];
};

extern "C" u8 D_00470F50[];
extern "C" char D_00525238[];
extern "C" char D_00525248[];
extern "C" u8 D_00525250[];
extern "C" s32 insect_InsectModelMemFindFreeIndex_5128b0(void);
extern "C" void insect_ModelObjExCtor_4f78f0(void *o);
extern "C" void *func_14DB10(void *p, s32 a, s32 b, s32 c);
extern "C" void func_14DFF0(Ent *e);
extern "C" void *func_14D950(void *p, s32 n);
extern "C" void func_14DEE0(Ent *e, void *p, s32 n);
extern "C" void func_14DAD0(void *p);
extern "C" void func_14DE90(Ent *e);
extern "C" u32 func_134BB0(const char *s);
extern "C" void func_134A98(void *d, const char *s);
extern "C" void *func_14E230(s32 size, void *pool);
extern "C" void func_1343B8(char *d, const char *f, s32 n);
extern "C" W *func_15DE40(void);
extern "C" void func_131B60(void *d, s32 c, s32 n);
extern "C" void func_1AFD00(VE *o, Desc *d);
extern "C" void func_1CFCD0(void *h, s32 id, VE *o, s32 n);

extern "C" s32 insect_InsectModelMemCreatePiece_5125f0(A *a, void *b)
{
    Desc d;
    char nm[4];
    s32  idx;
    s32  id;
    Ent *e;
    VE  *m;
    W   *w;
    void *r;

    if (b == 0) {
        return -1;
    }
    idx = insect_InsectModelMemFindFreeIndex_5128b0();
    id = idx + 0x80;
    a->w400[idx] = id;
    r = func_14DB10(a->f004, 2, 0, 0x40);
    if (r != 0) {
        /* ix18e LEVER: the STORE must come FIRST.  With `e = &a->ent[idx];`
         * first, mwcc emits `addu base,index`; with the store first it emits
         * retail's `addu index,base`.  Four other spellings of the pointer
         * (`idx + a->ent`, `a->ent + idx`, both-sides, `e->f58`) are ONE
         * object d596cd0e. */
        a->ent[idx].f58 = (s32)r;
        e = &a->ent[idx];
        func_14DFF0(e);
        func_14DEE0(e, func_14D950(a->f004, 0x2580), 0x2580);
        func_14DAD0(a->f004);
        func_14DE90(e);
        if (func_134BB0(D_00525238) < 0x10) {
            func_134A98(e, D_00525238);
        }
        func_14DB10(e, 2, 0, 0x40);
        m = (VE *)func_14E230(0x790, e);
        if (m != 0) {
            insect_ModelObjExCtor_4f78f0(m);
            *(void **)((u8 *)m + 0x1B0) = D_00470F50;
        }
        func_1343B8(nm, D_00525248, idx);
        w = func_15DE40();
        func_134A98(w->f1E4, nm);
        func_131B60(&d, 0, 0x88);
        d.f30 = 8;
        d.f2C = d.b40;
        d.f3C = 8;
        d.f38 = d.b60;
        d.f00 = b;
        d.f04 = D_00525250;
        d.f08 = e;
        d.f0C = e;
        d.f10 = e;
        d.f14 = idx + 0x243;
        d.f18 = 1;
        m->s21();
        func_1AFD00(m, &d);
        w->f1E4[0] = 0;
        func_14DAD0(e);
        func_1CFCD0(a->f000, id, m, 0);
    }
    return a->w400[idx];
}
