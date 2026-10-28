/* rgp:protos */
#define RGP_SELF_StringAssignRange_107e30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma tailcall off

struct S106ee0 {
    union {
        struct { u8 flag : 1; u8 len : 7; } s;
        struct { u32 cap; u32 size; } l;
    } u;
};

struct C1 { char c; };

/*rgp*/

s32 StringAssignRange_107e30(struct S106ee0 *p, s32 a, s32 b)
{
    struct C1 t __attribute__((aligned(16)));
    u32 n;

    if (p->u.l.cap & 1) {
        n = p->u.l.size;
    } else {
        n = p->u.s.len;
    }
    return ((s32)StringReplace_106f90(p, 0, n, a, b, t.c));
}
