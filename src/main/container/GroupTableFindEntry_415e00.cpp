#include "types.h"

struct E415 { s16 key; u8 pad02[0x12]; };
struct R415 { u8 pad00[0x1C]; s32 m1C; E415 *m20; };

class V415 {
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
    virtual R415 *s70(s16 id);
};

extern "C" E415 *GroupTableFindEntry_415e00(V415 *a0, s32 a1, s32 a2)
{
    R415 *r;
    E415 *p;
    s32 i;
    s32 n;
    s16 key;

    r = a0->s70((s16)a1);
    if (r == 0) {
        return 0;
    }
    p = r->m20;
    if (p == 0) goto none;
    n = r->m1C;
    if (n > 0) goto ok;
none:
    return 0;
ok:
    key = (s16)a2;
    for (i = 0; i < n; i++, p++) {
        if (p->key == key) {
            return p;
        }
    }
    return 0;
}
