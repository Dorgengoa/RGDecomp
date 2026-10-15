#include "types.h"

class Node_FUN_003f6700 {
public:
    virtual void s08();
    virtual void s0C();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1C(void *b, s32 c, s32 d);
};

struct BigD_FUN_003f6700 {
    void *p;
    s32 pad[3];
};

struct Obj_FUN_003f6700 {
    s32 m0;
    s32 pad004;
    s32 md;
    Node_FUN_003f6700 *n0;
    Node_FUN_003f6700 *n1;
    Node_FUN_003f6700 *n2;
    Node_FUN_003f6700 *n3;
};

extern BigD_FUN_003f6700 D_00465878;
extern BigD_FUN_003f6700 D_00465880;
extern BigD_FUN_003f6700 D_00465888;
extern BigD_FUN_003f6700 D_00465890;

extern "C" s32 WorldSubsysPurposeLoad_3f6700(Obj_FUN_003f6700 *o, void *b, s32 unused, s32 d)
{
    Node_FUN_003f6700 *x;

    if (b == 0) return 0;
    if (o->m0 == 0) return 0;
    o->md = d;
    x = o->n0;
    if (x != 0) x->s1C(b, D_00465878.p != 0, 0);
    x = o->n1;
    if (x != 0) x->s1C(b, D_00465880.p != 0, 0);
    x = o->n2;
    if (x != 0) x->s1C(b, D_00465888.p != 0, 0);
    x = o->n3;
    if (x != 0) x->s1C(b, D_00465890.p != 0, 0);
    return 1;
}
