#include "types.h"
/* insmenu 0x004F50A0 -- jr $31 / daddu $2, $5, $0: return the SECOND
 * argument.  The first is never read and its type is unconstrained. */
s32 insmenu_InsectVsStateNop_4f50a0(s32 a, s32 b) { return b; }
