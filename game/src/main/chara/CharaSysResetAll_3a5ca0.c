/* rgp:protos */
#define RGP_SELF_CharaSysResetAll_3a5ca0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x250];
    s32 m250;
};

void CharaSysResetAll_3a5ca0(struct Obj0 *p0)
{
    CharaSysEncounterResetMaybe_3a5b10(p0, 1, 1, 1);
    CharaSysBattleHistoryReset_3a5bf0(p0);
    CharaSysDeactivateMaybe_3a3760(p0);
    CharaSysClearTable23C_3a3630(p0);
    CharaSysBattleResultReset_3a31b0(p0);
    p0->m250 = 0;
    CharaSysClearTables_3a5c00(p0);
    CharaSysStatusTableReset_3a17d0(p0);
}
