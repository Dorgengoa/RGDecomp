#include "types.h"

typedef struct S0028ea40 {
    u8 pad0[0x14];
    s16 unk14;
    s16 unk16;
} S0028ea40;

typedef struct O435530 {
    u8 pad0[0x4];
    s32 unk4;
    u8 pad8[0x30 - 0x8];
    s8 a30[0x167];
    s8 a197[0x49];
    s16 unkE0_dummy;
} O435530;

extern S0028ea40 *UiEntryListFindByTag_28ea40(s32 arg0, s32 arg1);
extern void TextEntryMarkStarCells_4357b0(void *arg0, s32 arg1, s32 arg2, s8 *arg3, s8 *arg4, s32 arg5);

void TextEntryFillGapSpaces_435530(u8 *arg0)
{
    S0028ea40 *p;
    s32 n;
    s8 *p7;
    s8 *p8;
    s8 c;

    if (*(s16 *)(arg0 + 0xE0) == 0) {
        return;
    }
    p = UiEntryListFindByTag_28ea40(*(s32 *)(arg0 + 0x4), 0x6D62);
    n = (s16)(p->unk14 + p->unk16 * 29);
    n = n + p->unk16 - 1;
    if (n < 0) {
        return;
    }
    p8 = (s8 *)(arg0 + n + 0x30);
    p7 = (s8 *)(arg0 + 0x197);
    p7 += n;
    for (; n >= 0; p7--, p8--, n--) {
        c = *p8;
        if (c == 0x2A && *p7 == 0x31) {
            *p8 = 0x20;
            continue;
        }
        if (c >= 0x30 && c <= 0x39) {
            break;
        }
        if (c >= 0x61 && c <= 0x7A) {
            break;
        }
        if (c >= 0x41 && c <= 0x5A) {
            break;
        }
    }
    TextEntryMarkStarCells_4357b0(arg0, -1, -1, p7, p8, n);
}
