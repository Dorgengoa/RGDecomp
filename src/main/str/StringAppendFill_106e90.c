#include "types.h"

#pragma tailcall off

struct S106E90 { u32 f00; u32 f04; };
struct B106E90 { u8 b0 : 1; u8 len : 7; };

extern void StringReplaceFill_1075d0(struct S106E90 *s, u32 n, s32 z, void *a, void *b);

void StringAppendFill_106e90(struct S106E90 *s, void *a, void *b)
{
    u32 n;

    if (s->f00 & 1) {
        n = s->f04;
    } else {
        n = ((struct B106E90 *)s)->len;
    }
    StringReplaceFill_1075d0(s, n, 0, a, b);
}
