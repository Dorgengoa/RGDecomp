/* rgp:protos */
#define RGP_SELF_normal_TransSavePortEnterCb_519900 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00519900 -- scene teardown. */
typedef struct Obj { u8 pad00[0x12]; s16 f12; } Obj;

extern u8    D_00484804;
extern void *D_004847D8;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_TransSavePortEnterCb_519900(Obj *p)
{
    D_00484804 = 0;
    SaveUiHideWidget_37b460(0x75A2);
    normal_TransSavePortSelectDraw_519e80(-1);
    normal_TransSaveHighlightOption_519e70(-1);
    SaveSlotRecordsClear_37b800(-1);
    normal_TransSaveShowMsg_519ff0(0x18);
    normal_TransSavePortCursorBob_5187c0(p->f12, 1, 1);
    SaveSetBusy_376b10(0);
    UiEntryListResetRectByTag_28eb10(D_004847D8, 4);
    SaveUiScrollBarThumbPlace_3777a0(UiEntryListFindDataByTag_28ec30(D_004847D8, 4), 0x75A1, 0);
    return 1;
}
