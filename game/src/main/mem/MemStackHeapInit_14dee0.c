/* rgp:protos */
#define RGP_SELF_MemStackHeapInit_14dee0 1
#define RGP_SELF_dvclear 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* A pool set-up whose fourteen-store RESET block appears twice, once on entry
   and once on the failure path -- that is a `static inline` helper, the same
   shape as ResGroupRunScript_42be50.

   The guard is an `||`, not an `&&`, and the listing says so: the first test
   branches TO the shared reset block and the second branches AWAY from it, to
   the work.  An `&&` would send both the same way.  `sltiu $1, ..., 0x10`
   landing in $at is the matching half -- the branch's taken condition is
   `>= 0x10`, not a bare `<`. */

static inline void dvclear(u8 *p)
{
    *(u32 *)(p + 0x10) = 0;
    *(void **)(p + 0x14) = 0;
    *(void **)(p + 0x18) = 0;
    *(s32 *)(p + 0x28) = 0;
    *(s32 *)(p + 0x2C) = 0;
    *(s32 *)(p + 0x34) = 0;
    *(s32 *)(p + 0x20) = 0;
    *(s32 *)(p + 0x4C) = 0;
    *(s32 *)(p + 0x48) = 0;
    *(s32 *)(p + 0x44) = 0;
    *(s32 *)(p + 0x40) = 0;
    *(s32 *)(p + 0x24) = 0;
    *(s32 *)(p + 0x30) = -1;
    *(s32 *)(p + 0x3C) = 0;
}

void MemStackHeapInit_14dee0(u8 *p, u8 **buf, u32 n)
{
    u8 *q;

    dvclear(p);
    *(u8 ***)(p + 0x14) = buf;
    *(u32 *)(p + 0x10) = n;
    if (buf == 0 || *(u32 *)(p + 0x10) < 0x10) {
        dvclear(p);
    } else {
        *(u8 ***)(p + 0x18) = buf;
        *buf = *(u8 **)(p + 0x14) + *(u32 *)(p + 0x10) * 0x10 - 0x10;
        *(s32 *)(*(u8 **)(p + 0x18) + 0x4) = 0;
        *(s32 *)(*(u8 **)(p + 0x18) + 0x8) = 1;
        *(s32 *)(*(u8 **)(p + 0x18) + 0xC) = 0;
        q = *(u8 **)(*(u8 **)(p + 0x18) + 0x0);
        *(u8 **)(p + 0x1C) = q;
        *(u8 **)(q + 0x4) = *(u8 **)(p + 0x18);
        *(s32 *)(*(u8 **)(p + 0x1C) + 0x0) = 0;
        *(s32 *)(*(u8 **)(p + 0x1C) + 0x8) = 1;
        *(s32 *)(*(u8 **)(p + 0x1C) + 0xC) = 0;
        *(s32 *)(p + 0x24) = 0;
    }
}
