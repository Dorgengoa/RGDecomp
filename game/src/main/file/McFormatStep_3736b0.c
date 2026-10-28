/* rgp:protos */
#define RGP_SELF_McFormatStep_3736b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    u8 pad14[0x1C - 0x14];
} Slot;

typedef struct {
    u8 pad0[0x4A4];
    Slot slots[2];
    u8 pad4DC[0x4E0 - 0x4DC];
    s32 state;
    u8 pad4E4[0x4EC - 0x4E4];
    s16 idx;
} Obj;

extern s32 sceMcSync_12d098(s32, s32 *, s32 *);
extern s32 sceMcGetInfo_12d1b8(s16, s32, void *, void *, void *);
extern s32 sceMcFormat_12d6c8(s16, s32);
/*rgp*/
/*rgp*/
/*rgp*/

s32 McFormatStep_3736b0(Obj *arg0)
{
    s32 sp4C;
    s32 sp48;
    Slot *slot;
    s16 *out;

    slot = &arg0->slots[arg0->idx];
    out = ((s16 *)SaveMgrGetResult_375a00((void *)arg0));
    switch (arg0->state) {
    case 0:
        if (sceMcSync_12d098(1, 0, 0) == 0) {
            goto fail;
        }
        if (sceMcFormat_12d6c8(arg0->idx, 1) == 0) {
            arg0->state++;
            goto fail;
        }
        *out = 0xC;
        return 1;
    case 1:
        SaveProgressAdd_373650(arg0, 1);
        if (sceMcSync_12d098(1, &sp4C, &sp48) == 0) {
            goto fail;
        }
        if (sp48 < 0) {
            McSetErrorResult_375890(arg0, sp48);
            return 1;
        }
        arg0->state++;
        goto fail;
    case 2:
        if (sceMcGetInfo_12d1b8(arg0->idx, 1, &slot->unk4, &slot->unk10, &slot->unk8) == 0) {
            arg0->state++;
            goto fail;
        }
        *out = 0xC;
        return 1;
    case 3:
        if (sceMcSync_12d098(1, &sp4C, &sp48) == 0) {
            goto fail;
        }
        if (sp48 < 0) {
            McSetErrorResult_375890(arg0, sp48);
            return 1;
        }
        slot->unk0 = 1;
        return 1;
    }
fail:
    return 0;
}
