#include "types.h"
/* insect 0x005159F0 -- 56 bytes, 14 instructions.  Three parallel 3-vectors
 * copied to their "previous" slots; the loop indexes all six arrays off one
 * scaled pointer. */

typedef struct Obj {
    u8  pad00[0x78];
    f32 f78[3];                     /* +0x78 */
    f32 f84[3];                     /* +0x84 */
    f32 f90[3];                     /* +0x90 */
    f32 f9C[3];                     /* +0x9C */
    f32 fA8[3];                     /* +0xA8 */
    f32 fB4[3];                     /* +0xB4 */
} Obj;

void insect_InsectPieceSavePos_5159f0(Obj *o)
{
    s32 i;

    for (i = 0; i < 3; i++) {
        o->f9C[i] = o->f78[i];
        o->fA8[i] = o->f84[i];
        o->fB4[i] = o->f90[i];
    }
}
