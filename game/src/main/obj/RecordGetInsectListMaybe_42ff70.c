/* rgp:protos */
#define RGP_SELF_RecordGetInsectListMaybe_42ff70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Sub0042ff70 {
    u8 pad0[8];
    s32 unk8;
} Sub0042ff70;

typedef struct S0042ff70 {
    u8 pad0[0x1188];
    Sub0042ff70 *unk1188;
} S0042ff70;

/*rgp*/
/*rgp*/
/*rgp*/

s32 RecordGetInsectListMaybe_42ff70(S0042ff70 *arg0, s32 arg1) {
    s32 id;
    s32 r;

    id = arg0->unk1188->unk8;
    r = ((s32)RecordGetPayloadIfKind1E_430b70(arg0));
    if (r != 0) {
        if (id == 0x12F) {
            return r + 0x10;
        }
        if (id == 0x130) {
            return r + 0x268;
        }
        if ((u32)(id - 0x131) < 2) {
            return r + arg1 * 0x258 + 0x10;
        }
        return 0;
    }
    r = ((s32)RecordGetPayloadIfKind28_430b50(arg0));
    if (r != 0) {
        if (id == 0x192 || (u32)(id - 0x194) < 2) {
            return r + 0x14;
        }
        return 0;
    }
    r = ((s32)RecordGetPayloadIfKind3D_430af0(arg0));
    if (r != 0) {
        if ((u32)(id - 0x265) < 2) {
            return r + 0xF4;
        }
        return 0;
    }
    return 0;
}
