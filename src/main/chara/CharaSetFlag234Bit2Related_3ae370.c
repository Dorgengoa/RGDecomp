#include "types.h"

typedef struct Obj_FUN_003ae370 {
    u8 pad000[0x234];
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 br : 5;
} Obj_FUN_003ae370;

extern s32 CharaIsInReserve_3ae0e0(Obj_FUN_003ae370 *o);

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
