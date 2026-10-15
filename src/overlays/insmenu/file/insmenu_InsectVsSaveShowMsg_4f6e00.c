#include "types.h"
/* insmenu 0x004F6E00 -- tail call; $4 passes straight through and the other
 * two parameters shift up one slot for D_004FA180 in $5. */
extern const u8 D_004FA180[];
extern void func_376B60(s32 a, const void *b, s32 c, s32 d);

void insmenu_InsectVsSaveShowMsg_4f6e00(s32 a, s32 b, s32 c)
{
    func_376B60(a, D_004FA180, b, c);
}
