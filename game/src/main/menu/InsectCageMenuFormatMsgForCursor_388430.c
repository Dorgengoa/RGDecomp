/* rgp:protos */
#define RGP_SELF_InsectCageMenuFormatMsgForCursor_388430 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad00[0x14];
    s32 unk14;
    u8 pad18[0x1C - 0x18];
    s32 unk1C;
    u8 pad20[0xB0 - 0x20];
} Ctx00388430;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void InsectCageMenuFormatMsgForCursor_388430(s32 arg0, s32 arg1) {
    Ctx00388430 sp30 __attribute__((aligned(16)));
    s32 tmp;

    MsgFormatParamsCtor_28aa00(&sp30);
    sp30.unk14 = 0;
    if (InsectCageMenuGetCursorObj_390f70() != 0) {
        tmp = InsectCageMenuGetCursorObj_390f70();
        sp30.unk1C = MenuObjInsectGetName_386d40(tmp, 0, 0, 0);
    }
    MsgFormat_28a9a0(arg0, InsectCageMenuMsgLookup_389d30(arg1), &sp30, 1);
}
