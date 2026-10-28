/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsMenuEnterConfirm_4ee850 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004EE850 -- a TAIL CALL: `j func_28EDE0` with the third argument in
 * the delay slot.  $4 is `addiu $4, $28, -0xE88`, the ADDRESS of a gp object
 * (gp - 0xE88 = 0x004842E8), so the extern is non-const and stays in the gp
 * window.  This is the pipeline's first test of whether mwcc -O4 emits a tail
 * call at all; the whole 8-member family turns on it. */
extern u8 D_004842E8;
/*rgp*/
void insmenu_InsectVsMenuEnterConfirm_4ee850(void) { StateMachineSetState_28ede0(&D_004842E8, 0x7535, 0); }
