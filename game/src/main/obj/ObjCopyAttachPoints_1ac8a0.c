/* rgp:protos */
#define RGP_SELF_ObjCopyAttachPoints_1ac8a0 1
#define RGP_SELF_at 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4;

typedef struct {
    s32 unk0;
    f32 unk4;
    s32 unk8;
    s32 unkC;
    V4 v;
} Elem;

typedef struct {
    u8 pad0[0x20C];
    s32 n;
    Elem *p;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/

static inline Elem *at(Obj *o, s32 i) {
    if (o->p == 0) {
        return 0;
    }
    if (i < 0 || i >= o->n) {
        return 0;
    }
    return &o->p[i];
}

void ObjCopyAttachPoints_1ac8a0(Obj *arg0, Obj *arg1, s32 arg2) {
    s32 n;
    Elem *p;
    s32 i;
    Elem *s;
    Elem *d;

    if (arg0->n == 0) {
        arg1->n = 0;
        arg1->p = 0;
    }
    if (arg2 == 0) {
        arg1->n = arg0->n;
        arg1->p = arg0->p;
        return;
    }
    n = arg0->n;
    if (n > 0) {
        arg1->n = n;
        p = ((Elem *)ConstructNewArray_100710(MemStackNew_14e1b0((n << 5) + 0x10, arg2), ObjAttachPointCtor_1aae00, 0, 0x20, n));
        arg1->p = p;
        if (p == 0) {
            arg1->n = 0;
        } else {
            for (i = 0; i < arg1->n; i++) {
                arg1->p[i].unk0 = -1;
            }
        }
    } else {
        arg1->n = 0;
        arg1->p = 0;
    }
    if (arg0->n == arg1->n) {
        for (i = 0; i < arg0->n; i++) {
            s = at(arg0, i);
            d = at(arg1, i);
            if (d != 0 && s != 0) {
                d->unk0 = s->unk0;
                d->unk4 = s->unk4;
                d->unk8 = s->unk8;
                d->unkC = s->unkC;
                d->v = s->v;
            }
        }
    }
}
