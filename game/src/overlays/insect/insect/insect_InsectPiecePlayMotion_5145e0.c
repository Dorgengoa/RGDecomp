/* rgp:protos */
#define RGP_SELF_insect_InsectPiecePlayMotion_5145e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x005145E0 -- 344 bytes, 86 instructions.
 *
 * Builds a 16-byte descriptor on the stack from a table entry, patches it for
 * a few special ids and hands it to insect_InsectPieceMotionQueuePush_514510.  `insect_D_005241F0` is an
 * s32 table indexed by the clamped id; its element pointer is a named local
 * because retail keeps it in $16 across the whole body and loads through it
 * twice.
 */

typedef struct Desc {
    s32 w[4];
} Desc;

typedef struct Obj {
    u8  pad00[0x38];
    s8  f38;                        /* +0x38 */
    u8  pad39[0x4C - 0x39];
    s8  f4C;                        /* +0x4C */
} Obj;

extern void Sprintf_1343b8(Desc *d, const void *src, s32 v);
extern void strcat(Desc *d, const void *src);
/*rgp*/
/*rgp*/

extern s32 insect_D_005241F0[];
extern u8  insect_D_005252B8[];
extern u8  insect_D_005252C0[];
extern u8  insect_D_005252C8[];
extern u8  insect_D_005252D0[];
extern u8  insect_D_005252D8[];

void insect_InsectPiecePlayMotion_5145e0(Obj *o, s32 id, s32 k, f32 x, f32 y)
{
    Desc d __attribute__((aligned(16)));
    const s32 *p;
    s32 n;

    if (id < 0) {
        return;
    }
    n = id;
    if (id >= 8) {
        n = 8;
    }
    p = &insect_D_005241F0[n];
    Sprintf_1343b8(&d, insect_D_005252B8, *p);
    if (id == 9) {
        strcat(&d, insect_D_005252C0);
    }
    if (id == 0xA) {
        strcat(&d, insect_D_005252C8);
    }
    if (o->f38 == 0xC) {
        if (o->f4C <= 0 || insect_InsectPieceTestStatus_513280(o, 0x18) != 0) {
            if (id < 3) {
                strcat(&d, insect_D_005252D0);
            }
        }
    }
    if (o->f38 == 0x10) {
        if (id == 0) {
            Sprintf_1343b8(&d, insect_D_005252D8, *p);
        }
    }
    insect_InsectPieceMotionQueuePush_514510(o, &d, k, x, y);
}
