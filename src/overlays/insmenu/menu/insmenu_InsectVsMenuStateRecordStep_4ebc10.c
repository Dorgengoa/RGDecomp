#include "types.h"
/* insmenu 0x004EBC10 -- forward, turning the second argument into a 0/1 flag.
 * `sltu $5, $0, $5` in the jal's delay slot is `b != 0`; $4 passes straight
 * through.  The `andi $2, $2, 0xFF` after the epilogue load says the return is
 * u8, the mirror of the s32 predicate rule (see insmenu_FUN_004EE8A0). */
extern s32 insmenu_InsectVsStateCallStep_4ebf50(void *a, s32 b);
u8 insmenu_InsectVsMenuStateRecordStep_4ebc10(void *a, s32 b) { return (u8)insmenu_InsectVsStateCallStep_4ebf50(a, b != 0); }
