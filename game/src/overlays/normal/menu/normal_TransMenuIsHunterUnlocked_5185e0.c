/* rgp:protos */
#define RGP_SELF_normal_TransMenuIsHunterUnlocked_5185e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005185E0 -- one-line forwarder; the trailing `andi 0xFF` is the u8
 * return narrowing. */

typedef struct Ctx {
    u8    pad000[0x18];
    void *f18;
} Ctx;

/*rgp*/
/*rgp*/

u8 normal_TransMenuIsHunterUnlocked_5185e0(void)
{
    return InvHasItemInCategory_3c7f40(((Ctx *)GetGameData_1fede0())->f18, 0x40E9, 10, 0);
}
