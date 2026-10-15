#include "types.h"

typedef struct DtorEnt {
    void (*fn)(s32, void *, void *);
    void *arg;
} DtorEnt;

typedef struct Obj {
    const u8 *vt;
    DtorEnt *list;
    s32 n;
    s32 pad;
    void *p10;
    s32 pad2;
    void *p18;
} Obj;

extern const u8 D_0046FDA0[];
extern void Free_130e30(void *);
extern void OperatorDelete_100840(void *);

void *IosBaseDtor_102970(Obj *o, s16 flag)
{
    s32 n;

    if (o != 0) {
        o->vt = D_0046FDA0;
        n = o->n;
        while (n != 0) {
            DtorEnt *e = &o->list[--n];
            e->fn(0, o, e->arg);
        }
        Free_130e30(o->p18);
        Free_130e30(o->p10);
        Free_130e30(o->list);
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
