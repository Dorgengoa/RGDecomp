#include "types.h"

#pragma divbyzerocheck on

typedef struct Obj_FUN_001dd210 {
    u8 pad000[0x38];
    s16 f38;
    u8 pad03A[0x6];
    s32 f40;
} Obj_FUN_001dd210;

s32 MapRecTableOwnsShare_1dd210(Obj_FUN_001dd210 *o, s32 x)
{
    s32 d;

    if (x == 0) {
        return 0;
    }
    if (o->f40 == 0) {
        return 0;
    }
    d = (x - o->f40) / 0x58;
    return d >= 0 && d < o->f38;
}
