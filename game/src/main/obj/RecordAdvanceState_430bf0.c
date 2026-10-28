/* rgp:protos */
#define RGP_SELF_RecordAdvanceState_430bf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Inner00430bf0 {
    u8 pad0[8];
    s32 unk8;
    u8 padC[0x14 - 0xC];
    s32 unk14;
} Inner00430bf0;

typedef struct S00430bf0 {
    u8 pad0[0x1188];
    Inner00430bf0 *unk1188;
} S00430bf0;

/*rgp*/

s32 RecordAdvanceState_430bf0(S00430bf0 *arg0, s8 *arg1)
{
    s32 temp_3;
    u8 var_16;
    Inner00430bf0 *temp_4;

    var_16 = 0;
    RecordSetStateClamped_430db0(arg0, arg0->unk1188->unk8 + 1, 0);
    temp_4 = arg0->unk1188;
    temp_3 = temp_4->unk14;
    switch (temp_3) {
    case 0x0:
        if (temp_4->unk8 == 0) {
            var_16 = 1;
        }
        break;
    case 0xA:
        if (temp_4->unk8 == 0x66) {
            var_16 = 1;
        }
        break;
    case 0x14:
        if (temp_4->unk8 == 0xCB) {
            var_16 = 1;
        }
        break;
    case 0x1E:
        if (temp_4->unk8 == 0x133) {
            var_16 = 1;
        }
        break;
    case 0x28:
        if (temp_4->unk8 == 0x196) {
            var_16 = 1;
        }
        break;
    case 0x32:
        if (temp_4->unk8 == 0x1FA) {
            var_16 = 1;
        }
        break;
    case 0x3C:
        if (temp_4->unk8 == 0x25F) {
            var_16 = 1;
        }
        break;
    case 0x3D:
        if (temp_4->unk8 == 0x26A) {
            var_16 = 1;
        }
        break;
    case 0x3E:
        if (temp_4->unk8 == 0x270) {
            var_16 = 1;
        }
        break;
    case 0x3F:
        if (temp_4->unk8 == 0x27B) {
            var_16 = 1;
        }
        break;
    case 0x46:
        if (temp_4->unk8 == 0x2BE) {
            var_16 = 1;
        }
        break;
    }
    if (arg1 != NULL) {
        *arg1 = var_16;
    }
    return arg0->unk1188->unk8;
}
