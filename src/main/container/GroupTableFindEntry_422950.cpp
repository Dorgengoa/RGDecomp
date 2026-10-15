#include "types.h"

struct E422 { s16 key; u8 pad02[0x1E]; };
struct R422 { u8 pad00[0x14]; s32 m14; E422 *m18; };

class V422 {
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
    virtual R422 *s70(s16 id);
};

extern "C" E422 *GroupTableFindEntry_422950(V422 *a0, s32 a1, s32 a2)
{
    R422 *r;
    E422 *p;
    s32 i;
    s32 n;
    s16 key;

    r = a0->s70((s16)a1);
    if (r == 0) {
        return 0;
    }
    p = r->m18;
    if (p == 0) goto none;
    n = r->m14;
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
