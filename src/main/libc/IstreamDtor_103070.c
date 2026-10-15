#include "types.h"

extern const u8 D_0046FE90[];
extern const u8 D_0046FE9C[];
extern const u8 D_0046FEA8[];
extern void *IosBaseDtor_102970(void *, s16);
extern void OperatorDelete_100840(void *);

struct Obj_FUN_00103070 {
    u8 *m00;
    u8 pad004[0xC];
    const u8 *m10;
    u8 pad014[0x4];
    const u8 *m18;
};

void *IstreamDtor_103070(struct Obj_FUN_00103070 *o, s32 flag)
{
    void *p;
    u8 *b;

    if (o != 0) {
        o->m10 = D_0046FE90;
        p = (u8 *)o + 0x18;
        *(const u8 **)o->m00 = D_0046FE9C;
        b = o->m00;
        *(s32 *)(b + 0x48) = (s32)((u8 *)p - b);
        if (flag != 0) {
            if (p != 0) {
                o->m18 = D_0046FEA8;
                IosBaseDtor_102970(p, 0);
            }
        }
        if ((s16)flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
