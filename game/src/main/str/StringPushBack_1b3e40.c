/* rgp:protos */
#define RGP_SELF_StringPushBack_1b3e40 1
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

s32 StringPushBack_1b3e40(struct S106ee0 *p, char c)
{
    struct C1 b __attribute__((aligned(16)));
    u32 n;

    if (p->u.l.cap & 1) {
        n = p->u.l.size;
    } else {
        n = p->u.s.len;
    }
    return ((s32)StringReplace_106f90(p, n, 0, &c, &b.c, b.c));
}
