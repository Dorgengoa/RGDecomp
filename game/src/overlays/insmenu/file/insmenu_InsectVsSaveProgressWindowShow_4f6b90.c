/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsSaveProgressWindowShow_4f6b90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004F6B90 -- tail call with the two parameters shifted up one slot
 * to make room for insmenu_D_004FA180 in $4. */
extern u8 insmenu_D_004FA180[];
/*rgp*/

void insmenu_InsectVsSaveProgressWindowShow_4f6b90(void *a, void *b)
{
    SaveProgressWindowShow_377690(insmenu_D_004FA180, a, b);
}
