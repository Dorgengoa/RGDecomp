/* rgp:protos */
#define RGP_SELF_StringFindChar_1b3c20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct SH1 { u8 flag : 1; u8 len : 7; } SH1;
s32 StringFindChar_1b3c20(void *arg0, s64 arg1, u32 arg2)
{
    s8 *cur;
    u32 len;
    u8 *base;
    s8 *end;
    s8 c;

    if (!(*(u32 *)((u8 *)arg0 + 0x0) & 1)) {
        base = (u8 *)arg0 + 1;
        len = ((SH1 *)arg0)->len;
    } else {
        base = *(void **)((u8 *)arg0 + 0x8);
        len = *(u32 *)((u8 *)arg0 + 0x4);
    }
    if (arg2 < len) {
        c = (s8)arg1;
        end = (s8 *)base + len;
        for (cur = (s8 *)base + arg2; cur < end; cur++) {
            if (c == *cur) {
                return (s32)(cur - (s8 *)base);
            }
        }
    }
    return -1;
}
