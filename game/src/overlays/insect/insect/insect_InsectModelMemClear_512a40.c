/* rgp:protos */
#define RGP_SELF_insect_InsectModelMemClear_512a40 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00512A40 -- 108 bytes, 27 instructions.
 * The 0x398-byte block at +0x64 runs exactly up to the s32 at +0x3FC, and the
 * s16 table at +0x400 is 0x1C entries.
 */

typedef struct Obj {
    s32 m00;                        /* +0x00 */
    u8  m04[0x5C - 0x04];           /* +0x04 */
    s32 m5C;                        /* +0x5C */
    s32 m60;                        /* +0x60 */
    u8  m64[0x3FC - 0x64];          /* +0x64 */
    s32 m3FC;                       /* +0x3FC */
    s16 m400[0x1C];                 /* +0x400 */
} Obj;

extern void memset(void *, s32, s32);
/*rgp*/

void insect_InsectModelMemClear_512a40(Obj *o)
{
    s32 i;

    o->m00 = 0;
    o->m5C = 0;
    o->m60 = 0;
    o->m3FC = 0;
    for (i = 0; i < 0x1C; i++) {
        o->m400[i] = -1;
    }
    memset(o->m64, 0, 0x398);
    MemStackClear_14dff0(o->m04);
}
