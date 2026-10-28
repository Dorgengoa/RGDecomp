/* rgp:protos */
#define RGP_SELF_CharaCmdSysPlay_22ac40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Kick one of two per-kind effects for an entity.  Head of a 3-member clone
   group (208 B each) with CharaCmdBsPlay_22ab70 / CharaCmdSysPlay_22ac40, which differ only in
   which `FUN_001d07*` they call.  The first parameter is passed and never
   used.

   Three measured spellings:
   * the `kind` test is written `>= 2` with the 1.0f case in the ELSE.  As
     `< 2` with the arms the other way the compare lands in `$at` instead of
     retail's `$v0` -- [[at-compare-class]], the only GPR spelling in an
     if/else is `>=` with the tested value on the left.
   * `if (h == 0) return 1;` -- the early return has to be the FALL-THROUGH so
     that mwcc branches INTO the body with `bnel` and carries `ScriptArgGetInt_302d70`'s
     argument in the branch delay slot.  Written `if (h != 0) { ... }` the unit
     is 50 words against retail's 52.
   * SoundPlayScaledVolume_1b9520's float parameter is declared THIRD, not last.  The register
     assignment is the same either way (integers fill a0-a2, the float f12),
     but the prototype order sets the argument EMISSION order and hence which
     argument lands in the `jal` delay slot -- [[levers.d/mwcc-prototype-param-order]].
     Declared last the unit is 2 bad; declared first, 3. */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 CharaCmdSysPlay_22ac40(s32 unused, s32 a, s32 kind)
{
    f32 s;
    s32 t;
    s32 h;

    if (kind != 1 && kind != 2) {
        return 1;
    }
    h = GetCurrentScene_1f5be0();
    if (h == 0) {
        return 1;
    }
    t = ScriptArgGetInt_302d70(a);
    if (kind >= 2) {
        s = ScriptArgGetFloat_302cf0(a + 5);
    } else {
        s = 1.0f;
    }
    SoundPlayScaledVolume_1b9520(GameSceneSoundSlot0GetHandle_1d07c0(h), t, SoundNextPlayHandle_1b81c0(), s);
    return 1;
}
