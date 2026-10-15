#include "types.h"
/* normal 0x005185A0 -- `dsll32 30 / dsrl32 31` off an `lbu` is a ONE-BIT
 * unsigned bitfield at LSB offset 1, i.e. the SECOND declared u8:1. */

typedef struct Flags {
    u8 pad000[0x42D0];
    u8 b0 : 1;
    u8 b1 : 1;
} Flags;

typedef struct Ctx {
    u8     pad000[0x18];
    Flags *f18;
} Ctx;

extern Ctx *func_1FEDE0(void);

s32 normal_TransMenuCanWarp_5185a0(void)
{
    u8 v = func_1FEDE0()->f18->b1;

    return !v;
}
