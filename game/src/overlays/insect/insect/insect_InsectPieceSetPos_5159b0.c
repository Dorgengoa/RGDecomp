/* rgp:protos */
#define RGP_SELF_insect_InsectPieceSetPos_5159b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x005159B0 -- 52 bytes, 13 instructions, no calls, 1 conditional
 * branch.  Store a 3-vector at +0x78 and copy it to the "previous" slot at
 * +0x84; the loop indexes BOTH arrays off one scaled pointer, which is what
 * the shared `addu $5, $4, $3` with `lwc1 0x78($5)` / `swc1 0x84($5)` is.
 */

typedef struct Obj {
    u8  pad00[0x78];
    f32 f78[3];                     /* +0x78 */
    f32 f84[3];                     /* +0x84 */
} Obj;

void insect_InsectPieceSetPos_5159b0(Obj *o, f32 x, f32 y, f32 z)
{
    s32 i;

    o->f78[0] = x;
    o->f78[1] = y;
    o->f78[2] = z;
    for (i = 0; i < 3; i++) {
        o->f84[i] = o->f78[i];
    }
}
