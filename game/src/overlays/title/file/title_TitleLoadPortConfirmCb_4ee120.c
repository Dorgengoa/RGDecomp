/* rgp:protos */
#define RGP_SELF_title_TitleLoadPortConfirmCb_4ee120 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EE120 -- a bit test on a field reached through a
 * gp-relative pointer, then five calls.
 *
 * `sb $4, -0xF5C($28)` rides in func_376B10's delay slot with $4 already 1,
 * so the store and the argument are the same constant.
 */

typedef struct Obj_title_FUN_004ee120 {
    u8 pad000[0x12];
    s16 field012;      /* +0x12 */
} Obj_title_FUN_004ee120;

typedef struct Sys_title_FUN_004ee120 {
    u8 pad000[0x1C];
    s32 field01C;      /* +0x1C */
} Sys_title_FUN_004ee120;

extern Sys_title_FUN_004ee120 *D_004841E8;
extern s8 D_00484214;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 title_TitleLoadPortConfirmCb_4ee120(Obj_title_FUN_004ee120 *o)
{
    if ((D_004841E8->field01C & 1) != 0) {
        return 0;
    }
    D_00484214 = 1;
    SaveSetBusy_376b10(1);
    title_TitleLoadPortSelectDraw_4ede70(o->field012);
    title_TitleLoadPortCursorBob_4edaf0(o->field012, 0, 0);
    UiEntryListSelectByTag_28ea90(D_004841E8, 0x7533, 0);
    return 1;
}
