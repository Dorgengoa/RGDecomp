#include "types.h"

class V {
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
    virtual s32 f(s16);
};

struct A64 { u8 pad[0xc]; V *mC; };
struct A40 { u8 pad[8]; V *m8; };
struct Ctx {
    u8 pad0[0x40];
    A40 *m40;
    u8 pad44[0x20];
    A64 *m64;
};
struct EA { u8 padA[0xc]; };
struct EB { s32 x; };
struct Elem : EA, EB {
    u8 pad10[0x6d];
    s8 lo : 2;
    s8 bf : 6;
    u8 pad7e[0xa];
    s32 *m88;
};
struct DA { u8 padA[0x88]; };
struct DB { s32 x; };
struct Dv : DA, DB { };
struct Iter { s32 a; s32 b; };

extern "C" void IterInit_370170(Iter *, void *);
extern "C" void *IterNext_370040(Iter *);

extern "C" s32 WorldSubsysLinkIds_402870(Dv *a0, Ctx *c)
{
    Iter it1;
    Iter it2;
    Elem *e;
    s32 *p;
    s32 n;
    s32 i;

    if (c == 0) {
        return 0;
    }
    IterInit_370170(&it1, (DB *)a0);
    goto next;
    do {
        IterInit_370170(&it2, (EB *)e);
        while ((p = (s32 *)IterNext_370040(&it2)) != 0) {
            *p = c->m64->mC->f(*p);
        }
        p = e->m88;
        n = e->bf;
        if (p != 0 && n > 0) {
            for (i = 0; i < n; i++) {
                *p = c->m40->m8->f(*p);
                p++;
            }
        }
    next:
        e = (Elem *)IterNext_370040(&it1);
    } while (e != 0);
    return 1;
}
