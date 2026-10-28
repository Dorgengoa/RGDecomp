/* rgp:protos */
#define RGP_SELF_TableFindByNameInRange_412e80 1
#include "port/game_protos.h"
#line 1
#include "types.h"
s32 strcmp(s32, s32);                               /* extern */

u8 *TableFindByNameInRange_412e80(u8 *arg0, s16 arg1, s32 arg2) {
    u8 *p;
    s32 i;
    s32 end;
    s32 r;
    s32 base;
    s32 idx;

    if (arg2 == 0) {
        return 0;
    }
    base = *(s32 *)(arg0 + 0x8C);
    if (base == 0 || *(s16 *)(arg0 + 0x7C) <= 0) {
        return 0;
    }

    idx = arg1;
    if (idx < 0 || idx >= 6) {
        idx = 6;
    }
    i = *(s16 *)(arg0 + idx * 4 + 0x98);
    end = *(s16 *)(arg0 + idx * 4 + 0x9A);
    if (i < 0 || end < 0) {
        return 0;
    }
    for (p = (u8 *)(base + (i << 5)); i <= end; i++, p += 0x20) {
        r = strcmp(arg2, *(s32 *)(p + 4));
        if (r == 0) {
            return p;
        }
        if (r < 0) {
            break;
        }
    }
    return 0;
}
