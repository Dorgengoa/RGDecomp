#include "types.h"

class VA87 {
public:
    virtual void s08();
    virtual void s0C();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1C();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual void s2C();
    virtual void s30();
    virtual void s34();
    virtual void s38();
    virtual void s3C();
    virtual void s40();
    virtual void s44();
    virtual void s48();
    virtual void s4C();
    virtual void s50();
    virtual void s54();
    virtual void s58();
    virtual void s5C();
    virtual void s60();
    virtual void s64();
    virtual void s68();
    virtual void s6C();
    virtual void s70();
    virtual void s74();
    virtual void s78();
    virtual void s7C();
    virtual void s80();
    virtual void s84();
    virtual void s88();
    virtual void s8C();
    virtual void s90();
    virtual void s94();
    virtual void s98();
    virtual void s9C();
    virtual void sA0();
    virtual void sA4();
    virtual void sA8();
    virtual void sAC();
    virtual void sB0();
    virtual void sB4();
    virtual void sB8();
    virtual void sBC();
    virtual void sC0();
    virtual void sC4();
    virtual void sC8(void *p);
};

struct G20 { u8 pad00[0x24C]; u8 m24C; };
struct G87 { u8 pad00[0x20]; G20 *m20; };
struct A87 { u8 pad00[0x8]; void *m8; };

extern G87 *D_004837E8;
extern struct BigD87 { s32 v; s32 pad[3]; } D_004659B8;
extern "C" VA87 *PoolGetUsedElem_36acb0(void *, s32);

extern "C" s32 CharaMgrPoolBroadcastPhase_3a87f0(A87 *a0, void *arg)
{
    G87 *g;
    VA87 *e;
    s32 i;
    s32 n;

    g = D_004837E8;
    if (g == 0) {
        return 0;
    }
    if ((g->m20->m24C & 1) == 0) {
        return 0;
    }
    if (a0->m8 == 0) {
        return 0;
    }
    n = D_004659B8.v;
    for (i = 0; i < n; i++) {
        e = PoolGetUsedElem_36acb0(a0->m8, i);
        if (e != 0) {
            e->sC8(arg);
        }
    }
    return 1;
}
