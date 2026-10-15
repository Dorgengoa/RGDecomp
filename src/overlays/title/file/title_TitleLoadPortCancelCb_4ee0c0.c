#include "types.h"

/* title.bin overlay, 0x004EE0C0 -- set a flag, then four calls, two of them
 * taking the object's halfword field. */

typedef struct Obj_title_FUN_004ee0c0 {
    u8 pad000[0x12];
    s16 field012;      /* +0x12 */
} Obj_title_FUN_004ee0c0;

extern s8 D_00484214;
extern void *D_004841E0;
extern void title_TitleLoadShowMsg_4eeb60(s32 a);
extern void title_TitleLoadPortCursorBob_4edaf0(s16 a, s32 b, s32 c);
extern void title_TitleSetCardChangeState_4ed360(s16 v);
extern void func_28EDE0(void *a, s32 b, s32 c);

s32 title_TitleLoadPortCancelCb_4ee0c0(Obj_title_FUN_004ee0c0 *o)
{
    D_00484214 = 1;
    title_TitleLoadShowMsg_4eeb60(-1);
    title_TitleLoadPortCursorBob_4edaf0(o->field012, 0, 0);
    title_TitleSetCardChangeState_4ed360(2);
    func_28EDE0(D_004841E0, 9, 0);
    return 1;
}
