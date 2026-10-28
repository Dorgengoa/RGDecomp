/* rgp:protos */
#define RGP_SELF_InsectCageSetTypeFromItem_391090 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 InsectCageSetTypeFromItem_391090(s32 k)
{
    s32 t;

    t = 0;
    if (k == 0x4169) {
        t = 1;
    } else if (k == 0x416A) {
        t = 2;
    }
    return (InsectCageSetType_3910d0(t), (s32)0);
}
