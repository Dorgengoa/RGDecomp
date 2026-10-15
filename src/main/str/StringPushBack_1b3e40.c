#include "types.h"
#pragma tailcall off

struct S106ee0 {
    union {
        struct { u8 flag : 1; u8 len : 7; } s;
        struct { u32 cap; u32 size; } l;
    } u;
};

struct C1 { char c; };

extern s32 StringReplace_106f90(struct S106ee0 *, u32, s32, char *, char *, char);

s32 StringPushBack_1b3e40(struct S106ee0 *p, char c)
{
    struct C1 b;
    u32 n;

    if (p->u.l.cap & 1) {
        n = p->u.l.size;
    } else {
        n = p->u.s.len;
    }
    return StringReplace_106f90(p, n, 0, &c, &b.c, b.c);
}
