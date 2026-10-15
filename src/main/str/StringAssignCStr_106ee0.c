#include "types.h"
#pragma tailcall off

struct S106ee0 {
    union {
        struct { u8 flag : 1; u8 len : 7; } s;
        struct { u32 cap; u32 size; } l;
    } u;
};

extern s32 StringReplaceCStr_106f20(struct S106ee0 *, s32, u32, s32);

s32 StringAssignCStr_106ee0(struct S106ee0 *p, s32 a)
{
    u32 n;

    if (p->u.l.cap & 1) {
        n = p->u.l.size;
    } else {
        n = p->u.s.len;
    }
    return StringReplaceCStr_106f20(p, 0, n, a);
}
