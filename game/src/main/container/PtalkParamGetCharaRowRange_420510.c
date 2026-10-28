/* rgp:protos */
#define RGP_SELF_PtalkParamGetCharaRowRange_420510 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 PtalkParamGetCharaRowRange_420510(void *arg0, s32 arg1, s32 *arg2, s32 *arg3) {
    s32 idx;
    s32 off;
    void *p;

    *arg2 = -1;
    *arg3 = -1;
    if (arg1 < 0) {
        return -1;
    }
    idx = MainCharaIdToNumber_4016b0(arg1) - 1;
    if (idx < 0 || idx >= 9) {
        idx = 9;
    }
    off = idx * 4;
    p = (void *)(off + (s32)arg0);
    *arg2 = *(s16 *)((u8 *)p + 0x98);
    *arg3 = *(s16 *)((u8 *)p + 0x9A);
    return *arg2;
}
