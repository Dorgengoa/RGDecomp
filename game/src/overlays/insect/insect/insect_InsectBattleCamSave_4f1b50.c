/* rgp:protos */
#define RGP_SELF_insect_InsectBattleCamSave_4f1b50 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004F1B50 -- 100 bytes, 25 instructions, 2 calls.  Both guards are
 * early returns; the copy loop walks base + i*4 and uses constant +0x60 /
 * +0x70 displacements, so one induction pointer feeds four accesses. */

typedef struct Obj {
    f32 m00[3];                     /* +0x00 */
    u8  pad0C[0x10 - 0x0C];
    f32 m10[3];                     /* +0x10 */
    u8  pad1C[0x60 - 0x1C];
    f32 m60[3];                     /* +0x60 */
    u8  pad6C[0x70 - 0x6C];
    f32 m70[3];                     /* +0x70 */
} Obj;

/*rgp*/
/*rgp*/

void insect_InsectBattleCamSave_4f1b50(Obj *o)
{
    s32 i;

    if (insect_InsectBattleCamEyeSettled_4f19f0(o) == 0) {
        return;
    }
    if (insect_InsectBattleCamTargetSettled_4f1980(o) == 0) {
        return;
    }
    for (i = 0; i < 3; i++) {
        o->m60[i] = o->m00[i];
        o->m70[i] = o->m10[i];
    }
}
