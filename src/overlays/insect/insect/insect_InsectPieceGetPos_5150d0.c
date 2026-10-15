#include "types.h"
/* insect 0x005150D0 -- 92 bytes, 23 instructions.  Three optional vec3
 * copies; the first has no guard, the second and third are `if (p != 0)`. */

typedef struct Obj {
    u8  pad00[0x78];
    f32 m78[3];                     /* +0x78 */
    f32 m84[3];                     /* +0x84 */
    f32 m90[3];                     /* +0x90 */
} Obj;

void insect_InsectPieceGetPos_5150d0(Obj *o, f32 *a, f32 *b, f32 *c)
{
    a[0] = o->m78[0];
    a[1] = o->m78[1];
    a[2] = o->m78[2];
    if (b != 0) {
        b[0] = o->m84[0];
        b[1] = o->m84[1];
        b[2] = o->m84[2];
    }
    if (c != 0) {
        c[0] = o->m90[0];
        c[1] = o->m90[1];
        c[2] = o->m90[2];
    }
}
