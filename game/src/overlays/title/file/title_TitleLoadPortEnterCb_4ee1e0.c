/* rgp:protos */
#define RGP_SELF_title_TitleLoadPortEnterCb_4ee1e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EE1E0 -- a scene-enter sequence: clear a flag, then
 * nine calls in listing order, ending in a constant return.  Both incoming
 * arguments ride straight through into title_TitleLoadSlotCursorBob_4edcf0; only the first is
 * read again, for its +0x12 halfword.
 */

typedef struct Obj_title_FUN_004ee1e0 {
    u8 pad000[0x12];
    s16 field012;      /* +0x12 */
} Obj_title_FUN_004ee1e0;

extern s8 D_00484214;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 title_TitleLoadPortEnterCb_4ee1e0(Obj_title_FUN_004ee1e0 *o, void *b)
{
    SaveSetBusy_376b10(0);
    D_00484214 = 0;
    SaveUiHideWidget_37b460(0x43);
    title_TitleLoadSlotCursorBob_4edcf0(o, b, 0);
    title_TitleLoadPortSelectDraw_4ede70(-1);
    SaveSlotRecordsClear_37b800(-1);
    title_TitleLoadHighlightOption_4ede30(-1);
    title_TitleLoadShowMsg_4eeb60(0x18);
    title_TitleLoadPortCursorBob_4edaf0(o->field012, 1, 1);
    title_TitleSetNoAnalogPause_4f13b0(0);
    return 1;
}
