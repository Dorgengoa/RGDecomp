/* rgp:protos */
#define RGP_SELF_CharaEventLogGetEntry_3a62b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj0;

struct Obj0 {
    u8 pad000[0x42];
    s16 m42;
};

void *CharaEventLogGetEntry_3a62b0(struct Obj0 *p0, s32 p1)
{
    if (p1 < 0) {
        goto fail;
    }
    if (p1 < p0->m42) {
        goto ok;
    }
fail:
    return 0;
ok:
    return (void *)((u8 *)p0 + (p1 << 3) + 0x46);
}
