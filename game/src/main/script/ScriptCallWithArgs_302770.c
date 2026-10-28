/* rgp:protos */
#define RGP_SELF_ScriptCallWithArgs_302770 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef s32 (*FP_00302770)(void *, u8 *, s32);

typedef struct S_00302770 {
    FP_00302770 f0;
    u8 *f4;
    s32 f8;
} S_00302770;

s32 ScriptCallWithArgs_302770(S_00302770 *self, void *b, s32 c)
{
    FP_00302770 f __attribute__((aligned(16))) = self->f0;
    if (f == 0) goto zero;
    if (b != 0) goto ok;
zero:
    return 0;
ok:
    return f(b, self->f4 + c * 5, self->f8 - c);
}
