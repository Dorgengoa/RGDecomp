/* rgp:protos */
#define RGP_SELF_title_TitleLoadPortCancelCb_4ee0c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EE0C0 -- set a flag, then four calls, two of them
 * taking the object's halfword field. */

typedef struct Obj_title_FUN_004ee0c0 {
    u8 pad000[0x12];
    s16 field012;      /* +0x12 */
} Obj_title_FUN_004ee0c0;

extern s8 D_00484214;
extern void *D_004841E0;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 title_TitleLoadPortCancelCb_4ee0c0(Obj_title_FUN_004ee0c0 *o)
{
    D_00484214 = 1;
    title_TitleLoadShowMsg_4eeb60(-1);
    title_TitleLoadPortCursorBob_4edaf0(o->field012, 0, 0);
    title_TitleSetCardChangeState_4ed360(2);
    StateMachineSetState_28ede0(D_004841E0, 9, 0);
    return 1;
}
