#include "types.h"
/* normal 0x004FCFD0 -- the 0x38 widget's per-frame refresh.  Same tail shape
 * as normal_FUN_004FD2D0 (the 0x38 record's f02 reset) but the value written
 * is 25 * the caller record's f12: `sll 2 / addu / sll 2 / addu` is one
 * multiply by 25, not two source multiplies. */

typedef struct Fld { u8 pad00[2]; s16 f02; } Fld;
typedef struct Wgt { u8 pad00[0x20]; Fld *f20; } Wgt;
typedef struct Rec { u8 pad00[0x12]; s16 f12; } Rec;

extern void *D_00484454;          /* gp - 0xD1C */
extern void *D_0048449C;          /* gp - 0xCD4 */

extern void  func_289EF0(s32 a);
extern Wgt  *func_290460(void *p, u16 id);
extern void  func_290F60(void *p, u16 id, s32 x, s32 y);

s32 normal_BtlChgMenuTacticsCursorMoveCb_4fcfd0(Rec *a)
{
    Wgt *w;
    Fld *t;

    if (D_00484454 == 0) {
        return 0;
    }
    func_289EF0(4);
    if (D_0048449C != 0) {
        func_290F60(D_0048449C, 0x38, 7, 6);
        w = func_290460(D_0048449C, 0x38);
        if (w != 0) {
            t = w->f20;
            if (t != 0) {
                t->f02 = (s16)(a->f12 * 25);
            }
        }
    }
    return 1;
}
