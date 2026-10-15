#include "types.h"

class Node_FUN_003f9ec0 {
public:
    virtual void s08();
    virtual void s0C();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1C(void *b, s32 c, s32 d);
};

struct BigD_FUN_003f9ec0 {
    void *p;
    s32 pad[3];
};

struct Obj_FUN_003f9ec0 {
    s32 m0;
    s32 md;
    Node_FUN_003f9ec0 *n0;
    Node_FUN_003f9ec0 *n1;
    Node_FUN_003f9ec0 *n2;
    Node_FUN_003f9ec0 *n3;
};

extern BigD_FUN_003f9ec0 D_00465728;
extern BigD_FUN_003f9ec0 D_00465730;
extern BigD_FUN_003f9ec0 D_00465738;
extern BigD_FUN_003f9ec0 D_00465740;

extern "C" s32 WorldSubsysLoad_3f9ec0(Obj_FUN_003f9ec0 *o, void *b, s32 unused, s32 d)
{
    Node_FUN_003f9ec0 *x;

    if (b == 0) return 0;
    if (o->m0 == 0) return 0;
    o->md = d;
    x = o->n0;
    if (x != 0) x->s1C(b, D_00465728.p != 0, 0);
    x = o->n1;
    if (x != 0) x->s1C(b, D_00465730.p != 0, 0);
    x = o->n2;
    if (x != 0) x->s1C(b, D_00465738.p != 0, 0);
    x = o->n3;
    if (x != 0) x->s1C(b, D_00465740.p != 0, 0);
    return 1;
}
