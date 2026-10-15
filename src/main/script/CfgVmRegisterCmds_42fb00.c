#include "types.h"

typedef struct E { u16 key; u16 pad; s32 val; } E;
typedef struct L { s32 n; E e[0x80]; } L;
extern void *memcpy(void *, const void *, s32);

s32 CfgVmRegisterCmds_42fb00(L *arg0, u16 *arg1_)
{
    u16 *arg1;
    u8 *src;
    u8 *cur;
    s32 j;
    s32 k;
    s32 pos;
    s32 count;

    if (arg1_ == NULL) {
        return 0;
    }
    arg1 = arg1_;
    arg0->n = 0;
    while (*arg1 > 0) {
        pos = 0;
        cur = (u8 *)arg0 + 4;
        j = 0;
        while (j < *(s32 *)arg0) {
            if (*arg1 < *(u16 *)cur) {
                break;
            }
            pos += 1;
            j += 1;
            cur += 8;
        }
        count = arg0->n;
        src = (u8 *)arg0 + count * 8 - 4;
        k = count - 1;
        while (k >= pos) {
            memcpy(src + 8, src, 8);
            k -= 1;
            src -= 8;
        }
        memcpy((u8 *)arg0 + 4 + pos * 8, arg1, 8);
        arg1 += 4;
        arg0->n += 1;
        if (arg0->n >= 0x80) {
            break;
        }
    }
    return 1;
}
