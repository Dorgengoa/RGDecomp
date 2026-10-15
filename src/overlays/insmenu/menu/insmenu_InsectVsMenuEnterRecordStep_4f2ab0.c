#include "types.h"
/* insmenu 0x4F2AB0 -- TAIL CALL `j func_28EDE0`, third argument in the delay
 * slot.  $4 is the ADDRESS of a gp object (gp - offset =
 * 0x004842E8), so the extern stays non-const and keeps %gp_rel. */
extern u8 D_004842E8;
extern void func_28EDE0(void *a, s32 b, s32 c);
void insmenu_InsectVsMenuEnterRecordStep_4f2ab0(void) { func_28EDE0(&D_004842E8, 0x7531, 0); }
