#include "types.h"

/* Zero the small-data u8 D_004821B8. */

extern u8 D_004821B8;

void ClearInBattle_288400(void)
{
    D_004821B8 = 0;
}
