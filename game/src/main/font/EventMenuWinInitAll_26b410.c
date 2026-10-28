/* rgp:protos */
#define RGP_SELF_EventMenuWinInitAll_26b410 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Eight fixed slots of 0xE0 bytes out of the table D_0048206C points at.
   Retail reaches the stride with `sll 3; subu; sll 5` -- (i*8 - i) * 32 --
   which is the shift-and-subtract form of a multiply by 0xE0, so the source
   is an ordinary array index and not a hand-scaled pointer. The base is
   reloaded through $gp on every iteration. */

typedef struct Slot0026b410 {
    u8 bytes[0xE0];
} Slot0026b410;

extern Slot0026b410 *D_0048206C;

/*rgp*/

void EventMenuWinInitAll_26b410(void)
{
    s32 i;

    for (i = 0; i < 8; i++) {
        MenuWinInit_26c450(&D_0048206C[i]);
    }
}
