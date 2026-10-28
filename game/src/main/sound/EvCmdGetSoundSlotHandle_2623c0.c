/* rgp:protos */
#define RGP_SELF_EvCmdGetSoundSlotHandle_2623c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Script-command handler.  Two levers in one unit:
   - the `addiu $17,$17,0x8` in the jal delay slot is the POST-INCREMENT ON A
     POINTER USED AS THE CALL ARGUMENT (EvCmdOptionsSet_240930's measured null), and it
     happens TWICE -- once at the dispatch, once inside the case-5 arm;
   - `slti $1,$16,0x2` into $at is the STRICT compare, i.e. `p1 > 1`, and
     retail FALLS THROUGH into the extra ScriptGetInt_26a2a0 call, so that is the
     `if` body.

   jtbl_0045F140 is 6 entries, identity permutation: 0 -> A, {1,2,3} -> B,
   4 -> C, 5 -> D.  The out-of-range `beql` carries `daddu $2,$0,$0` in its
   delay slot, and the same `$2 = 0; goto epilogue` block is ALSO emitted
   (dead) after the last arm -- that is the source's explicit `default:`.

   `D_004BDA1C` is addressed with a %hi/%lo pair, so it must NOT be in small
   data: `extern const s32` (the spelling src/p22d/EventStateInitMaybe_26b740.c already uses
   for the same object).  `D_00481F78` IS gp-relative and stays a plain extern.

   SHIPPING THIS UNIT NEEDS A .rodata SLOT:
       config/crodata.txt:  EvCmdGetSoundSlotHandle_2623c0  0045F140  18   # jtbl_0045F140, 6 cases */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_00481F78;
extern s32 D_004BDA1C;

struct Cmd {
    s32 a;
    s32 b;
};

s32 EvCmdGetSoundSlotHandle_2623c0(struct Cmd *p0, s32 p1)
{
    s32 r0;

    if (p1 == 1) {
        r0 = D_004BDA1C;
    } else {
        switch (ScriptGetInt_26a2a0((s32)p0++)) {
        case 0:
            r0 = GameSceneAmbientGetCurHandle_1d0550(D_00481F78);
            break;
        case 1:
        case 2:
        case 3:
            r0 = GameSceneSoundSlot1GetHandle_1d07b0(D_00481F78);
            break;
        case 4:
            r0 = GameSceneSoundSlot5GetHandle_1d0790(D_00481F78);
            break;
        case 5:
            if (p1 > 1) {
                ScriptGetInt_26a2a0((s32)p0++);
            }
            r0 = GameSceneSoundSlot4GetHandle_1d07a0(D_00481F78);
            break;
        default:
            return 0;
        }
    }
    ScriptSetRefInt_26a1e0((s32)p0, r0);
    return 1;
}
