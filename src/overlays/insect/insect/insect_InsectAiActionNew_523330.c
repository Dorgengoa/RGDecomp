#include "types.h"
/* insect 0x00523330 -- 100 bytes, 25 instructions. */

typedef struct Obj {
    u8  pad00[0x1C];
    s8  f1C;                        /* +0x1C */
    u8  pad1D[0x20 - 0x1D];
} Obj;

typedef struct Owner {
    void *f0;                       /* +0x00 */
} Owner;

extern void *func_14E230(s32 size, void *pool);
extern Obj  *insect_InsectAiActionCtor_523460(Obj *p);
extern void  insect_InsectAiActionReset_523410(Obj *p);

Obj *insect_InsectAiActionNew_523330(Owner *o)
{
    Obj *p;

    p = (Obj *)func_14E230(0x20, o->f0);
    if (p != 0) {
        p = insect_InsectAiActionCtor_523460(p);
    }
    if (p == 0) {
        return 0;
    }
    insect_InsectAiActionReset_523410(p);
    p->f1C = 1;
    return p;
}
