/* rg-override: replaces game/src/main/chara/UnitGetStatusBitsJustCleared_3b6be0.c sha256 c834c45ac041656dffa719fdf3a1c7669f34780bee6d198492bfaafdfc6e03e5
 * why: a unit vtable slot (D_00474B20 & co.) that returns an 8-byte status-bit set.  On the PS2 every
 *      struct return goes through a hidden pointer, so retail's bytes fit `B48 Fn(O *)`; the port's
 *      callers (UnitStatusTest*_*, VCM_FN(void, (B48 *, void *), slot)(&r, this)) pass that pointer
 *      first, but i686 / x64 return an 8-byte struct in registers: the function read its object from
 *      the caller's result and the result stayed 0 (Individer: e004_sub label 310 never saw "freeze
 *      just added", so the boss never entered its frozen state; ptbugs4, BRINGUP 2026-11-10).
 *      Same computation, explicit result pointer.  Scan: tools/census/sret_vslot_scan.py. */
/* rgp:protos */
#define RGP_SELF_UnitGetStatusBitsJustCleared_3b6be0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct B48 {
    u64 v;
} B48;

/* bits at +0x1A8 not in +0xC8 (just cleared) */
void UnitGetStatusBitsJustCleared_3b6be0(B48 *out, u8 *o)
{
    u64 keep = *(u64 *)(o + 0x1A8);
    u64 mask = *(u64 *)(o + 0xC8);
    out->v = keep & (~mask & 0xFFFFFFFFFFFFULL);
}
