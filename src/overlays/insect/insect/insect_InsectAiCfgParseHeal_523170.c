#include "types.h"
/* insect 0x00523170 -- 23 instructions.  D_004851B8 is _gp+0x48 and so inside
 * the gp window 0x0047D170..0x0048D170; it stays a plain extern.  The
 * `dsll32/dsra32 ..,24` off the second call's result is an s32 local plus an
 * explicit `(s8)` cast -- the byte analogue of normal-s16-cast-sign-extension.
 */

typedef struct Rec {
    u8 m00;                         /* +0x00 */
    s8 m01;                         /* +0x01 */
    u8 pad02[0x08 - 0x02];
    s64 m08;                        /* +0x08 */
} Rec;

extern void *D_004851B8;

extern Rec *insect_InsectAiCfgSelectLevel_522d30(void *ctx, s32 id);
extern s32 func_15F780(void *p);

s32 insect_InsectAiCfgParseHeal_523170(void *arg)
{
    Rec *r;
    s32 v;

    r = insect_InsectAiCfgSelectLevel_522d30(D_004851B8, -1);
    v = func_15F780(arg);
    r->m01 = v;
    if ((s8)v != 0) {
        r->m08 |= 1;
    }
    return 1;
}
