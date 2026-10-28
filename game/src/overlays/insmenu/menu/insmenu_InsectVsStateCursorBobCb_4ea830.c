/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsStateCursorBobCb_4ea830 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x4EA830 -- forward to insmenu_InsectVsStateCallCursorBob_4ebec0 and truncate the result to a
 * byte (`andi $2, $2, 0xFF` after the epilogue's `ld $31`). */
/*rgp*/
u32 insmenu_InsectVsStateCursorBobCb_4ea830(void *rgp_a0, void *rgp_a1) { return (u8)((u8)insmenu_InsectVsStateCallCursorBob_4ebec0((void *)rgp_a0, (void *)rgp_a1)); }
