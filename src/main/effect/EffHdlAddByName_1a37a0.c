#include "types.h"

typedef struct { char c; } Alloc37a0;
typedef struct { s32 x; } Val37a0;

typedef struct {
    s32 flags;
    s32 len;
    char *ptr;
    s32 val;
} Entry37a0;

typedef struct {
    u8 *first;
    u8 second;
} Pair37a0;

extern char D_0045A650[];
extern char D_0045A6B0[];

extern void __assert(char *, s32, char *);
extern s32 strlen(const char *);
extern void OperatorDelete_100840(void *);
extern void StringAssignCStr_106ee0(void *, const char *);
extern void StringReplace_106f90(Entry37a0 *, s32, s32, const char *, const char *, Alloc37a0);
extern void StringReserve_107e80(Entry37a0 *, s32);
extern void EffNameMapInsertUnique_1a54f0(Pair37a0 *, void *, Entry37a0 *);
extern s32 *EffHdlSlotAlloc_1a5bf0(void *, void *);

void EffHdlAddByName_1a37a0(s32 *out, u8 *tree, char *name, s32 *val)
{
    Entry37a0 e;
    Pair37a0 r;
    volatile f32 z;
    f32 v;
    Alloc37a0 al;
    Entry37a0 *p;
    u32 i;
    s32 n;
    s32 *node;

    if (name == 0 || *name == 0) {
        __assert(D_0045A650, 0x11E, D_0045A6B0);
        *out = 0;
        return;
    }
    z = 0.0f;
    p = &e;
    v = z;
    for (i = 0; i < 3; i++) {
        ((s32 *)p)[i] = 0;
    }
    n = strlen(name);
    StringReserve_107e80(p, n);
    StringReplace_106f90(p, 0, 0, name, name + n, al);
    p->val = *(s32 *)&v;
    EffNameMapInsertUnique_1a54f0(&r, tree + 0x24, &e);
    if (e.flags & 1) {
        OperatorDelete_100840(e.ptr);
    }
    if (r.second != 0) {
        node = EffHdlSlotAlloc_1a5bf0(tree, r.first + 0x18);
        StringAssignCStr_106ee0((u8 *)node + 4, name);
        *node = *val;
        *out = *(s32 *)(r.first + 0x18);
    } else {
        *out = 0;
    }
}
