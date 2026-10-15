#include "types.h"

typedef struct Obj_FUN_0028ec80 {
    u8 pad000[0x4];
    s32 f04;
    u8 pad008[0x18];
    u8 b20_0 : 1;
    u8 b20_1 : 1;
    u8 b20_r : 6;
    u8 f21;
    u8 f22;
} Obj_FUN_0028ec80;

void UiEntryListReset_28ec80(Obj_FUN_0028ec80 *o)
{
    o->f04 = 0;
    o->b20_0 = 0;
    o->f21 = 0;
    o->b20_1 = 0;
    o->f22 = 0;
}
