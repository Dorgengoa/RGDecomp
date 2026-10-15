#include "types.h"
/* insmenu 0x004F6B90 -- tail call with the two parameters shifted up one slot
 * to make room for D_004FA180 in $4. */
extern const u8 D_004FA180[];
extern void func_377690(const void *a, void *b, void *c);

void insmenu_InsectVsSaveProgressWindowShow_4f6b90(void *a, void *b)
{
    func_377690(D_004FA180, a, b);
}
