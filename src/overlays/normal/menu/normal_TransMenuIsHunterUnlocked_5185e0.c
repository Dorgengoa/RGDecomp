#include "types.h"
/* normal 0x005185E0 -- one-line forwarder; the trailing `andi 0xFF` is the u8
 * return narrowing. */

typedef struct Ctx {
    u8    pad000[0x18];
    void *f18;
} Ctx;

extern Ctx *func_1FEDE0(void);
extern s32  func_3C7F40(void *p, s32 a, s32 b, s32 c);

u8 normal_TransMenuIsHunterUnlocked_5185e0(void)
{
    return func_3C7F40(func_1FEDE0()->f18, 0x40E9, 10, 0);
}
