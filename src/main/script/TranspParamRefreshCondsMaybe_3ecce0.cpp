#include "types.h"

typedef struct {
    s16 *id;
    s32 pad4;
    s16 idx;
    u8 padA[0x1C - 0xA];
} Ent1C;

typedef struct {
    u8 pad0[8];
    u8 *arr;
} Tab74;

typedef struct {
    u8 pad0[0xC];
    Ent1C *ents;
    u8 pad10[0x74 - 0x10];
    Tab74 *t74;
} Mgr;

typedef struct {
    u8 pad0[8];
    Mgr *mgr;
} Obj;

typedef struct {
    u8 pad0[0x38];
    s16 f38;
    s16 pad3A;
    s32 f3C;
    s32 f40;
} Elem;

struct A0 { u8 pad[0x88]; };
struct B0 { u8 x; };
struct D0 : A0, B0 { };

extern "C" {
extern s32 VariantIsZero_36ed10(s32);
extern void VariantInit_36ff00(void *);
extern Elem *IterNext_370040(void *);
extern void IterInit_370170(void *, B0 *);
extern s32 ScriptExecOpStream_3dffa0(void *, s16, s32, s32);
extern void VariantPoolReset_3e01f0(void *);
}

static inline u8 *get(Mgr *m, s32 idx) {
    Tab74 *t = m->t74;
    u8 *r;
    if (idx >= 0) {
        if (idx >= 2) {
            r = 0;
        } else {
            r = t->arr + idx * 0x98;
        }
    } else {
        r = 0;
    }
    return r;
}

extern "C" s32 TranspParamRefreshCondsMaybe_3ecce0(Obj *arg0, s32 arg1)
{
    struct {
        u8 h[8];
        u8 arr[0xE00];
        u8 t[0x10];
    } b;
    u8 it[8];
    s32 i;
    Ent1C *e;
    u8 *x;
    Elem *s;
    u8 *p;
    s32 r;

    if (arg0->mgr == 0) {
        return 0;
    }
    for (i = 0; i < 2; i++) {
        e = &arg0->mgr->ents[i];
        if (e == 0) continue;
        if (e->id == 0) continue;
        if (arg1 >= 0 && *e->id != arg1) continue;
        x = get(arg0->mgr, e->idx);
        if (x == 0) continue;
        IterInit_370170(it, (D0 *)x);
        while ((s = IterNext_370040(it)) != 0) {
            s->f40 = 1;
            if (s->f38 > 0 && s->f3C != 0) {
                p = b.arr;
                do {
                    VariantInit_36ff00(p);
                    p += 0x38;
                } while (p < b.arr + 0xE00);
                VariantPoolReset_3e01f0(&b);
                r = ScriptExecOpStream_3dffa0(&b, s->f38, s->f3C, 0);
                if (r != 0 && VariantIsZero_36ed10(r) != 0) {
                    s->f40 &= ~1;
                }
            }
        }
    }
    return 1;
}
