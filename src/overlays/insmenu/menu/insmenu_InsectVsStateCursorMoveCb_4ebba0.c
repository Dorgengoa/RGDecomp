#include "types.h"
/* insmenu 0x4EBBA0 -- forward to insmenu_InsectVsStateCallCursorMove_4ebe30 and truncate the result to a
 * byte (`andi $2, $2, 0xFF` after the epilogue's `ld $31`). */
extern s32 insmenu_InsectVsStateCallCursorMove_4ebe30(void);
u8 insmenu_InsectVsStateCursorMoveCb_4ebba0(void) { return (u8)insmenu_InsectVsStateCallCursorMove_4ebe30(); }
