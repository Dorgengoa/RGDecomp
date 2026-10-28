/* rgp:protos */
#define RGP_SELF_insect_InsectPieceMotionQueuePush_514510 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00514510 -- 204 bytes, 51 instructions.
 *
 * An 8-slot particle table at +0xE8, stride 0x20.  The 0xE9 flag byte is
 * materialised as its own pointer in the bnez delay slot, so it is a NAMED
 * pointer local read through in both arms.
 */

typedef struct Ent {
    s8  f00;                        /* +0x00 */
    s8  f01;                        /* +0x01 */
    u8  pad02[0x04 - 0x02];
    f32 f04;                        /* +0x04 */
    f32 f08;                        /* +0x08 */
    u8  f0C[0x20 - 0x0C];           /* +0x0C */
} Ent;

typedef struct Obj {
    u8  pad00[0xE8];
    Ent a[8];                       /* +0xE8 */
} Obj;

extern s32  strlen(const void *s);
/*rgp*/

void insect_InsectPieceMotionQueuePush_514510(Obj *o, s32 a, s8 t, f32 x, f32 y)
{
    s32 i;
    s8 *f;

    for (i = 0; i < 8; i++) {
        f = &o->a[i].f01;
        if (*f == 0) {
            insect_InsectPieceMotionSlotSetName_5147c0(&o->a[i], a);
            o->a[i].f04 = x;
            o->a[i].f08 = y;
            o->a[i].f00 = t;
            *f = 1;
            return;
        }
        if (strlen(o->a[i].f0C) == 0) {
            *f = 0;
        }
    }
}
