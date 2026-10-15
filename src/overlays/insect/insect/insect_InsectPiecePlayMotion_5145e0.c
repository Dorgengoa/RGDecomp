#include "types.h"
/* insect 0x005145E0 -- 344 bytes, 86 instructions.
 *
 * Builds a 16-byte descriptor on the stack from a table entry, patches it for
 * a few special ids and hands it to insect_InsectPieceMotionQueuePush_514510.  `D_005241F0` is an
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

extern void func_1343B8(Desc *d, const void *src, s32 v);
extern void func_134690(Desc *d, const void *src);
extern s32  insect_InsectPieceTestStatus_513280(Obj *o, s32 k);
extern void insect_InsectPieceMotionQueuePush_514510(Obj *o, Desc *d, s32 k, f32 x, f32 y);

extern const s32 D_005241F0[];
extern const u8  D_005252B8[];
extern const u8  D_005252C0[];
extern const u8  D_005252C8[];
extern const u8  D_005252D0[];
extern const u8  D_005252D8[];

void insect_InsectPiecePlayMotion_5145e0(Obj *o, s32 id, s32 k, f32 x, f32 y)
{
    Desc d;
    const s32 *p;
    s32 n;

    if (id < 0) {
        return;
    }
    n = id;
    if (id >= 8) {
        n = 8;
    }
    p = &D_005241F0[n];
    func_1343B8(&d, D_005252B8, *p);
    if (id == 9) {
        func_134690(&d, D_005252C0);
    }
    if (id == 0xA) {
        func_134690(&d, D_005252C8);
    }
    if (o->f38 == 0xC) {
        if (o->f4C <= 0 || insect_InsectPieceTestStatus_513280(o, 0x18) != 0) {
            if (id < 3) {
                func_134690(&d, D_005252D0);
            }
        }
    }
    if (o->f38 == 0x10) {
        if (id == 0) {
            func_1343B8(&d, D_005252D8, *p);
        }
    }
    insect_InsectPieceMotionQueuePush_514510(o, &d, k, x, y);
}
