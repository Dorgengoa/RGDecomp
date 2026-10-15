#include "types.h"

extern s32 UiSetWidgetVisible_290010(s32, s32, s32, s32);
extern void InsectCageMenuFormatMsgForCursor_388430(s32, s32);
extern void InsectCageMenuDialogTwoButtonLayout_38c740(void);
extern void InsectCageMenuSetStateFlagMaybe_390aa0(s32, s32);
extern s32 InsectCageMenuDialogButtonFocus_38c660(void *, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483304;
extern s16 D_00483334;
extern u8 D_004833D4;
extern u8 D_004833D8;
extern u8 D_004833DC;

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s16 m10;
};

s32 InsectCageMenuRemoveDialogOpen_38c6b0(struct Obj0 *p0, s32 p1)
{
    s32 r0;
    s32 t0;
    s32 r4;

    D_004833D4 = 0;
    D_004833D8 = 0;
    p0->m10 = 1;
    D_004833DC = 1;
    D_00483334 = 0;
    r0 = UiSetWidgetVisible_290010(p1, 0x75E4, 1, -1);
    t0 = D_00483304;
    InsectCageMenuFormatMsgForCursor_388430((t0 + 0xE80), 0x5DC);
    InsectCageMenuDialogTwoButtonLayout_38c740();
    InsectCageMenuSetStateFlagMaybe_390aa0(6, 1);
    r4 = InsectCageMenuDialogButtonFocus_38c660(p0, p1, 1);
    return 1;
}
