/* rgp:protos */
#define RGP_SELF_insect_InsectBattleMemberListFill_4faa90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004FAA90 -- 240 bytes, 60 instructions.  A five-slot refresh loop:
 * for each slot the id is looked up, queried, and the result is pushed to two
 * widget calls.  `func_290460`'s result is the second argument of
 * `func_393760`, so it is a NESTED CALL ARGUMENT (the 0x5054 member address is
 * materialised after the inner call returns).  The last argument of
 * `func_291250` arrives through `dsll32/dsra32 ..,0`, i.e. the callee's
 * parameter is s64 and the s32 result is sign-extended into it.
 * insect_InsectBattleGetPoolEntry_50dc90 writes 0x00..0x17 through its fourth argument, so the
 * out-parameter is a SIX-WORD block and the frame is 0x70, not 0x60. */

typedef struct Obj {
    u8  pad0000[0x878];
    s32 m878;                       /* +0x0878 */
    u8  pad087C[0x5054 - 0x87C];
    u8  m5054[0x5EF1 - 0x5054];     /* +0x5054 */
    u8  m5EF1;                      /* +0x5EF1 */
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleMemberListFill_4faa90(Obj *o, s32 h)
{
    s32 i;
    s32 f;
    s32 e;
    s32 out[6] __attribute__((aligned(16)));

    for (i = 0; i < 5; i++) {
        f = 2;
        e = insect_InsectTeamSlotGetMember_513eb0(h, i);
        out[0] = 0;
        if (e != -1) {
            if (insect_InsectBattleGetPoolEntry_50dc90(o, e, o->m5EF1, out) != 0) {
                f = 0;
                if (o->m5EF1 == 1) {
                    f = 1;
                }
            }
        }
        UiSetTextString_28f510(o->m878, 0x7545, out[0], i);
        InsectUiMemberIconSetTypeMaybe_393760(o->m5054, ((s32)UiFindWidget_290460(o->m878, 0x7545)), i, f);
    }
    UiSetWidgetSubItemValue_291250(o->m878, 0x753D, 0, insect_InsectTeamSlotCountMembers_513e10(h));
}
