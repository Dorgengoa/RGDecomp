/* rgp:protos */
#define RGP_SELF_insect_InsectCmdMenuClear_4efd40 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004EFD40 -- 56 bytes, 14 instructions. */

typedef struct Obj {
    void *f00;                      /* +0x00 */
    s32   f04;                      /* +0x04 */
} Obj;

/*rgp*/

void insect_InsectCmdMenuClear_4efd40(Obj *o)
{
    if (o->f00 != 0) {
        MemStackHeapReinit_14de90(o->f00);
        o->f04 = 0;
    }
}
