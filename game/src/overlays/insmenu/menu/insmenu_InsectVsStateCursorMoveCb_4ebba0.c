/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsStateCursorMoveCb_4ebba0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x4EBBA0 -- forward to insmenu_InsectVsStateCallCursorMove_4ebe30 and truncate the result to a
 * byte (`andi $2, $2, 0xFF` after the epilogue's `ld $31`). */
/*rgp*/
u32 insmenu_InsectVsStateCursorMoveCb_4ebba0(void *rgp_a0, void *rgp_a1) { return (u8)((u8)insmenu_InsectVsStateCallCursorMove_4ebe30((void *)rgp_a0, (void *)rgp_a1)); }
