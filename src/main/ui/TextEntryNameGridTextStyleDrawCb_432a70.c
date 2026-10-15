#include "types.h"

extern void *D_00484104;
extern void TextEntryNameGridTextStyle_433380(void *p, s32 a, s32 b, s32 c, s32 d, s32 e);

s32 TextEntryNameGridTextStyleDrawCb_432a70(s32 a, s32 b, s32 c, s32 d, s32 e)
{
    if (D_00484104 != 0) TextEntryNameGridTextStyle_433380(D_00484104, a, b, c, d, e);
    return 1;
}
