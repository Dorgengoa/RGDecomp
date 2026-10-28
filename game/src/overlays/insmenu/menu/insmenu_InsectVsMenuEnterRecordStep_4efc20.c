/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsMenuEnterRecordStep_4efc20 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x4EFC20 -- TAIL CALL `j func_28EDE0`, third argument in the delay
 * slot.  $4 is the ADDRESS of a gp object (gp - offset =
 * 0x004842E8), so the extern stays non-const and keeps %gp_rel. */
extern u8 D_004842E8;
/*rgp*/
void insmenu_InsectVsMenuEnterRecordStep_4efc20(void) { StateMachineSetState_28ede0(&D_004842E8, 0x7531, 0); }
