/* rgp:protos */
#define RGP_SELF_EhEndCatch_101010 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T101010 { void *f0; u8 pad004[0x4]; void (*f8)(void *, s32); };

void EhEndCatch_101010(struct T101010 *p)
{
    void *a;
    void (*fn)(void *, s32);

    a = p->f0;
    if (a == 0) {
        return;
    }
    fn = p->f8;
    if (fn == 0) {
        return;
    }
    fn(a, -1);
}
