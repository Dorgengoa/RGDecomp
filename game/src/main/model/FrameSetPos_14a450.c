/* rgp:protos */
#define RGP_SELF_FrameSetPos_14a450 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"


/* "set if changed" property.  bnel $6,$0 -> the FALL-THROUGH (slot == 0)
   case is the `if` body.  The three float compares branch in opposite
   directions, so they are an `||`.  The lq/sq copy is the 16-byte aligned
   Vec4 assignment. */

struct Obj {
    u8 pad000[0x14];
    Vec4 *m14;      /* 0x14 */
    u8 pad018[0x11];
    u8 m29;         /* 0x29 */
    u8 pad02A;
    u8 m2B;         /* 0x2B */
    u8 m2C;         /* 0x2C */
    u8 pad02D[3];
    Vec4 m30;       /* 0x30 */
};

void FrameSetPos_14a450(struct Obj *p0, Vec4 *p1)
{
    Vec4 *t0;
    u128 t1;

    t0 = p0->m14;
    if (t0 == 0) {
        p0->m14 = &p0->m30;
        p0->m2B = 1;
        p0->m29 = 1;
        p0->m2C = 0;
        t1 = *(u128 *)p1;
        *(u128 *)p0->m14 = t1;
        p0->m29 = 1;
    } else if (t0->x != p1->x || t0->y != p1->y || t0->z != p1->z) {
        *t0 = *p1;
        p0->m29 = 1;
    }
}
