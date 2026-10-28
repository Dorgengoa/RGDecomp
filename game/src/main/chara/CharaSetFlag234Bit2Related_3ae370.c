/* rgp:protos */
#define RGP_SELF_CharaSetFlag234Bit2Related_3ae370 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_FUN_003ae370 {
    u8 pad000[0x234];
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 br : 5;
} Obj_FUN_003ae370;

/*rgp*/

void CharaSetFlag234Bit2Related_3ae370(Obj_FUN_003ae370 *o, s32 x)
{
    if (x != 0) {
        if (CharaIsInReserve_3ae0e0(o) != 0) {
            o->b2 = 1;
            return;
        }
    }
    o->b2 = 0;
}
