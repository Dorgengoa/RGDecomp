/* rg-override: replaces game/src/main/map/InsectronRewardLookupMaybe_3e84f0.cpp sha256 45c170f96f59dff96a5aad2a2e576bea033b7b6fa292078990f891dab1cddd9a
 * why: virtual tail through a base-class method the stages could not type (PROTOS.md abi2 "1 BUG-pass"): retail forwards $a1 (the team key) to slot 0x70 and returns its record pointer */
#include "types.h"

/* asm 003E84F0: $a0 = p->+8->+0xA0->+0xC; j *(vptr + 0x70) with $a1-$a3 untouched.
 * Slot 0x70 of that table object is the keyed record lookup TableFindFloorByKey_40b230
 * calls as method26(key, rank, team) (same object, (GetGameData()+8)->+0xA0); the caller
 * InsectBattleMatchUpdateMaybe_319800 passes key = *(s16 *)(e + 0x5EFC) and reads the
 * reward pairs at +2/+4 + 4k of the record (its override). Extra cdecl arguments are
 * harmless; the lookup reads the key only in the paths seen. */
struct A3E84F0 { u8 pad000[0xC]; void *f0C; };
struct S3E84F0 { u8 pad000[0xA0]; struct A3E84F0 *fA0; };
struct T3E84F0 { u8 pad000[0x8]; struct S3E84F0 *f08; };

extern "C" void *InsectronRewardLookupMaybe_3e84f0(struct T3E84F0 *p, s32 key)
{
    void *o = p->f08->fA0->f0C;
    return VCALL(o, 0x0, 0x70, void *, (void *, int, int, int), (int)key, 0, 0);
}
