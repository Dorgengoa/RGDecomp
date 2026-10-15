#include "types.h"

typedef struct Obj {
    u32 type;       /* 0x00 */
    u8 pad4[4];
    union {
        s8 c;
        s16 h;
        s32 w;
        s64 d;
        f32 f;
    } u;            /* 0x08 */
    u8 pad10[0x10];
    void (*cb)(struct Obj *, void *, s32, s32);  /* 0x20 */
    u8 pad24[4];
    u8 buf[1];      /* 0x28 */
} Obj;

extern s64 litodp(s32);
extern void VariantPromoteTypes_36e510(Obj *, u32, s32);

static inline void notify(Obj *o)
{
    if (o->cb != 0) {
        o->cb(o, o->buf, 0, 0);
    }
}

void VariantSetS32_36f040(Obj *o, s32 v, s32 force)
{
    VariantPromoteTypes_36e510(o, o->type, 5);
    switch (o->type) {
    case 1:
        o->type = 1;
        o->u.c = (s8)v;
        notify(o);
        break;
    case 2:
        o->type = 2;
        o->u.c = (s8)v;
        notify(o);
        break;
    case 3:
        o->type = 3;
        o->u.h = (s16)v;
        notify(o);
        break;
    case 4:
        o->type = 4;
        o->u.h = (s16)v;
        notify(o);
        break;
    case 5:
        o->type = 5;
        o->u.w = v;
        notify(o);
        break;
    case 6:
        o->type = 6;
        o->u.w = v;
        notify(o);
        break;
    case 7:
        o->type = 7;
        o->u.d = (s64)v;
        notify(o);
        break;
    case 8:
        o->type = 8;
        o->u.d = (s64)v;
        notify(o);
        break;
    case 9:
        o->type = 9;
        o->u.f = (f32)v;
        notify(o);
        break;
    case 10:
        o->type = 10;
        o->u.d = litodp(v);
        notify(o);
        break;
    }
    if (force != 0) {
        notify(o);
    }
}
