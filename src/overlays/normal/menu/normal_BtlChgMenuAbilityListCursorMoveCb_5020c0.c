#include "types.h"
/* normal 0x005020C0 -- guarded on the context pointer, then split on
 * normal_FUN_00505F80: the true arm copies the context's +0x76 into the
 * object's +0x16, the false arm replays it through two setters and runs the
 * 1.0f cue.  1.0f is built with `lui 0x3F80 / mtc1`, no literal pool.
 *
 * `addiu $2,$0,1` appears THREE times.  The outer guard is the
 * `if (guard) { ... } return 1;` shape whose `beql` delay slot carries a COPY
 * of the shared return; the inner early `return 1` is the third. */

typedef struct Obj { u8 pad000[0x16]; s16 f016; } Obj;
typedef struct Ctx { u8 pad000[0x76]; s16 f076; } Ctx;

extern Ctx  *D_00484454;          /* gp - 0xD1C */
extern void *D_004844A4;          /* gp - 0xCCC */

extern s32  normal_BtlChgPageGetScrollDir_505f80(Ctx *p);
extern void normal_BtlChgPageSetScrollPos_5060f0(Ctx *p, s32 a);
extern void normal_BtlChgPageAbilityListScroll_504ea0(Ctx *p, s32 a, s32 b);
extern void func_1B9520(void *p, s32 a, s32 b, f32 v);

s32 normal_BtlChgMenuAbilityListCursorMoveCb_5020c0(Obj *o)
{
    if (D_00484454 != NULL) {
        if (normal_BtlChgPageGetScrollDir_505f80(D_00484454) != 0) {
            o->f016 = D_00484454->f076;
            return 1;
        }
        normal_BtlChgPageSetScrollPos_5060f0(D_00484454, o->f016);
        normal_BtlChgPageAbilityListScroll_504ea0(D_00484454, 0, o->f016);
        func_1B9520(D_004844A4, 4, 0, 1.0f);
    }
    return 1;
}
