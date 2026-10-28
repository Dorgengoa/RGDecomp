/* rgp:protos */
#define RGP_SELF_RecStackPopTo_1c4020 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 RecStackPopTo_1c4020(u8 *o, s32 key)
{
    s32 idx;
    s32 obj;
    s32 i;
    s32 k;
    s32 r;
    s32 n;

    idx = -1;
    obj = ((s32)RecStackGetSlot_1c4330(o, key));
    if (obj == 0) {
        return idx;
    }
    for (i = 0; i < *(s32 *)(o + 0x1804); i++) {
        k = *(s32 *)(o + i * 4 + 0x1704);
        if (k == key) {
            idx = i + 1;
            break;
        }
    }
    if (idx < 0) {
        return -1;
    }
    MemStackResetChildren_14d170(obj);
    MemStackDetachChildren_14d580(obj);
    n = *(s32 *)(o + 0x1804);
    if (idx >= n) {
        return 0;
    }
    for (i = n - 1; i >= idx; i--) {
        k = *(s32 *)(o + i * 4 + 0x1704);
        r = ((s32)RecStackGetSlot_1c4330(o, k));
        if (r != 0) {
            MemStackClear_14dff0(r);
            *(s32 *)(o + k * 4) = 0;
            *(s32 *)(o + 0x1804) -= 1;
        }
    }
    *(s32 *)(o + 0x1700) = key;
    return 0;
}
