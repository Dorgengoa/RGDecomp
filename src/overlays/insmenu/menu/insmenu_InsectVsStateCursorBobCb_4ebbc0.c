#include "types.h"
/* insmenu 0x4EBBC0 -- forward to insmenu_InsectVsStateCallCursorBob_4ebec0 and truncate the result to a
 * byte (`andi $2, $2, 0xFF` after the epilogue's `ld $31`). */
extern s32 insmenu_InsectVsStateCallCursorBob_4ebec0(void);
u8 insmenu_InsectVsStateCursorBobCb_4ebbc0(void) { return (u8)insmenu_InsectVsStateCallCursorBob_4ebec0(); }
