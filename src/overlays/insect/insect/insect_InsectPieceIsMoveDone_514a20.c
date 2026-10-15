#include "types.h"
/* insect 0x00514A20 -- 160 bytes, 40 instructions, no calls.  Three parallel
 * f32[3] members at 0x78 / 0x84 / 0x90.  Every guard is an explicit-zero /
 * member-vs-member compare with the LOADED value in fs. */

typedef struct Obj {
    u8  pad0000[0x78];
    f32 f78[3];                     /* +0x78 */
    f32 f84[3];                     /* +0x84 */
    f32 f90[3];                     /* +0x90 */
} Obj;

s32 insect_InsectPieceIsMoveDone_514a20(Obj *o)
{
    s32 i;
    s32 ok;

    ok = 1;
    for (i = 0; i < 3; i++) {
        if (o->f78[i] != o->f84[i]) {
            ok = 0;
        }
    }
    for (i = 0; i < 3; i++) {
        if (o->f90[i]) {
            if (ok != 0) {
                for (i = 0; i < 3; i++) {
                    o->f90[i] = 0.0f;
                }
                return 1;
            }
            return 0;
        }
    }
    return 1;
}
