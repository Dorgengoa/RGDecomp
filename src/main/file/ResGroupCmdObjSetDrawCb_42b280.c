#include "types.h"

typedef struct SArg {
    s32 w[2];
} SArg;

extern void * ResGroupListCurElem_42a5d0(void);
extern s32 VariantGetInt_15f780(SArg *);

struct Pair;

struct Pair {
    s32 k;
    s32 v;
};

extern struct Pair D_00468380[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x2C];
    s32 m2C;
};

s32 ResGroupCmdObjSetDrawCb_42b280(SArg *p0)
{
    struct Obj0 *r0;
    struct Pair *e;
    s32 r1;

    r0 = ResGroupListCurElem_42a5d0();
    if (r0 == 0) {
        return 1;
    }
    r1 = VariantGetInt_15f780(p0);
    e = D_00468380;
    for (;;) {
        if (e->k < 0) {
            break;
        }
        if (e->k == r1) {
            r0->m2C = e->v;
            break;
        }
        e++;
    }
    return 1;
}
