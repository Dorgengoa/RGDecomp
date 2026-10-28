/* rgp:protos */
#define RGP_SELF_CharaSysEventLogRecordOpenHud_3a3260 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void *D_004837C0;

typedef struct { u8 pad0[0x244]; s32 unk244; } O3a3260;

s32 CharaSysEventLogRecordOpenHud_3a3260(O3a3260 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 sp6F;
    s32 temp_16;

    if (arg0->unk244 == 0) {
        return 0;
    }
    sp6F = 0;
    CharaSysEventLogKeyAdd_3a33b0(*(s32 *)((u8 *)D_004837C0 + 0x20), arg1, &sp6F);
    temp_16 = CharaEventLogRecord_3a62f0(arg0->unk244, arg1, arg2, arg3, arg4) & 0xFF;
    if (sp6F != 0) {
        CharaSysEventLogKeyRemove_3a3380(*(s32 *)((u8 *)D_004837C0 + 0x20), arg1, 0);
        FieldHudLogOpen_203fb0();
    }
    return temp_16;
}
