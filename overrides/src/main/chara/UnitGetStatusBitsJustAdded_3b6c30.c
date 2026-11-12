/* rg-override: replaces game/src/main/chara/UnitGetStatusBitsJustAdded_3b6c30.c sha256 5f908abec3ca05198660b6690d0e2ce300a8522e5af3af8ca9dd2810fd94b135
 * why: a unit vtable slot (D_00474B20 & co.) that returns an 8-byte status-bit set.  On the PS2 every
 *      struct return goes through a hidden pointer, so retail's bytes fit `M Fn(O *)`; the port's
 *      callers (UnitStatusTest*_*, VCM_FN(void, (M *, void *), slot)(&r, this)) pass that pointer
 *      first, but i686 / x64 return an 8-byte struct in registers: the function read its object from
 *      the caller's result and the result stayed 0 (Individer: e004_sub label 310 never saw "freeze
 *      just added", so the boss never entered its frozen state; ptbugs4, BRINGUP 2026-11-10).
 *      Same computation, explicit result pointer.  Scan: tools/census/sret_vslot_scan.py. */
/* rgp:protos */
#define RGP_SELF_UnitGetStatusBitsJustAdded_3b6c30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct M {
    u64 v;
} M;

/* bits at +0xC8 not in +0x1A8 (this tick vs prev: just added) */
void UnitGetStatusBitsJustAdded_3b6c30(M *out, u8 *o)
{
    u64 keep = *(u64 *)(o + 0xC8);
    u64 mask = *(u64 *)(o + 0x1A8);
    out->v = keep & (~mask & 0xFFFFFFFFFFFFULL);
}
