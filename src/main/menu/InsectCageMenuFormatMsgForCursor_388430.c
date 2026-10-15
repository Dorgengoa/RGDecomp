#include "types.h"

typedef struct {
    u8 pad00[0x14];
    s32 unk14;
    u8 pad18[0x1C - 0x18];
    s32 unk1C;
    u8 pad20[0xB0 - 0x20];
} Ctx00388430;

extern void MsgFormatParamsCtor_28aa00(Ctx00388430 *);
extern void MsgFormat_28a9a0(s32, s32, Ctx00388430 *, s32);
extern s32 MenuObjInsectGetName_386d40(s32);
extern s32 InsectCageMenuMsgLookup_389d30(s32);
extern s32 InsectCageMenuGetCursorObj_390f70(void);

void InsectCageMenuFormatMsgForCursor_388430(s32 arg0, s32 arg1) {
    Ctx00388430 sp30;
    s32 tmp;

    MsgFormatParamsCtor_28aa00(&sp30);
    sp30.unk14 = 0;
    if (InsectCageMenuGetCursorObj_390f70() != 0) {
        tmp = InsectCageMenuGetCursorObj_390f70();
        sp30.unk1C = MenuObjInsectGetName_386d40(tmp);
    }
    MsgFormat_28a9a0(arg0, InsectCageMenuMsgLookup_389d30(arg1), &sp30, 1);
}
