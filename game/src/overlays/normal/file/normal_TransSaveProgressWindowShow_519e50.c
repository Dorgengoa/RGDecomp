/* rgp:protos */
#define RGP_SELF_normal_TransSaveProgressWindowShow_519e50 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00519E50 -- leaf tail call, the gp handle is inserted as the FIRST
 * argument so both incoming registers shift up one slot. */

extern void *D_00484714;          /* gp - 0xA5C */

/*rgp*/

void normal_TransSaveProgressWindowShow_519e50(void *a, void *b)
{
    SaveProgressWindowShow_377690(D_00484714, a, b);
}
