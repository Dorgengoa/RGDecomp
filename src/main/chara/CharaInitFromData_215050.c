#include "types.h"

typedef struct S_00215050 {
    u8 pad0[0x420];
    void *f420;
    s16 f424;
    s16 f426;
} S_00215050;

extern void CharaInit_2150c0(S_00215050 *);

s32 CharaInitFromData_215050(S_00215050 *a, void *b, S_00215050 *c)
{
    CharaInit_2150c0(a);
    if (b == 0) goto zero;
    if (c != 0) goto ok;
zero:
    return 0;
ok:
    a->f420 = b;
    a->f424 = c->f424;
    a->f426 = c->f426;
    return 1;
}
