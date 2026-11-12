/* rg-override: replaces game/src/main/chara/UnitGetStatusBitsPrevJustCleared_3b6b40.c sha256 b3a985a38a28436f4b4dd19df20480d63de92eef06dfaf852ec098f3e8e73db7
 * why: a unit vtable slot (D_00474B20 & co.) that returns an 8-byte status-bit set.  On the PS2 every
 *      struct return goes through a hidden pointer, so retail's bytes fit `B48 Fn(O *)`; the port's
 *      callers (UnitStatusTest*_*, VCM_FN(void, (B48 *, void *), slot)(&r, this)) pass that pointer
 *      first, but i686 / x64 return an 8-byte struct in registers: the function read its object from
 *      the caller's result and the result stayed 0 (Individer: e004_sub label 310 never saw "freeze
 *      just added", so the boss never entered its frozen state; ptbugs4, BRINGUP 2026-11-10).
 *      Same computation, explicit result pointer.  Scan: tools/census/sret_vslot_scan.py. */
/* rgp:protos */
#define RGP_SELF_UnitGetStatusBitsPrevJustCleared_3b6b40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct B48 {
    u64 v;
} B48;

/* bits at +0x1B8 not in +0x1A8 (cleared one tick ago) */
void UnitGetStatusBitsPrevJustCleared_3b6b40(B48 *out, u8 *o)
{
    u64 keep = *(u64 *)(o + 0x1B8);
    u64 mask = *(u64 *)(o + 0x1A8);
    out->v = keep & (~mask & 0xFFFFFFFFFFFFULL);
}
