/* MATCH (main s22): [[mwcc-const-sdata-load-hoist]] -- `const` +
   __attribute__((section(".sdata"))) on the gp float extern lets its load
   schedule above the prologue's register saves, which is where retail has
   it.  Found by a STATIC screen of retail's own listing (a %gp_rel load
   interleaved with the `sq $sN,K($sp)` stores), not by reading a residue. */
#include "types.h"

typedef unsigned __int128 u128;

typedef struct Obj00167050 {
    u8 pad0[0x11C];
    f32 unk11C;
    u8 pad120[0x140 - 0x120];
} Obj00167050;

extern void MtxIdentity_13d2e0(void *p);
extern const f32 D_0047D278 __attribute__((section(".sdata")));

void DynColliderEllipsoidInit_167050(Obj00167050 *self)
{
    f32 t;
    u8 *base;

    t = D_0047D278;
    base = (u8 *)self;
    *(u128 *)(base + 0x120) = 0;
    *(u128 *)(base + 0x130) = 0;
    self->unk11C = t;
    MtxIdentity_13d2e0(base + 0x90);
    MtxIdentity_13d2e0(base + 0x10);
    MtxIdentity_13d2e0(base + 0xD0);
    MtxIdentity_13d2e0(base + 0x50);
}
