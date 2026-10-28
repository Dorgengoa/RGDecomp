/* rgp:protos */
#define RGP_SELF_RecordGetCageInsectCountsMaybe_42fec0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

s32 RecordGetCageInsectCountsMaybe_42fec0(void *arg0) {
    s32 id;
    s32 v;

    id = *(s32 *)((u8 *)*(void **)((u8 *)arg0 + 0x1188) + 8);
    v = ((s32)RecordGetPayloadIfKind1E_430b70(arg0));
    if (v != 0) {
        if (id == 0x12F) {
            return v + 0x4C0;
        }
        if (id == 0x130) {
            return v + 0x4C3;
        }
        return 0;
    }
    v = ((s32)RecordGetPayloadIfKind28_430b50(arg0));
    if (v != 0) {
        if (id == 0x192) {
            return v + 0x26C;
        }
        return 0;
    }
    v = ((s32)RecordGetPayloadIfKind3D_430af0(arg0));
    if (v != 0) {
        if (id == 0x265) {
            return v + 0x34C;
        }
        return 0;
    }
    return 0;
}
