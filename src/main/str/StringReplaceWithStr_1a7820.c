#include "types.h"
#pragma tailcall off

struct S106ee0 {
    union {
        struct { u8 flag : 1; u8 len : 7; } s;
        struct { u32 cap; u32 size; char *data; } l;
    } u;
};

struct C1 { char c; };

extern s32 StringReplace_106f90(s32, s32, s32, char *, char *, char);

s32 StringReplaceWithStr_1a7820(s32 a, s32 b, s32 c, struct S106ee0 *p)
{
    struct C1 t;
    char *beg;
    u32 n;

    if ((p->u.l.cap & 1) == 0) {
        beg = (char *)p + 1;
        n = p->u.s.len;
    } else {
        beg = p->u.l.data;
        n = p->u.l.size;
    }
    return StringReplace_106f90(a, b, c, beg, beg + n, t.c);
}
