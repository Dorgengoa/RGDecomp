#include "types.h"

typedef struct Node00140890 Node00140890;
struct Node00140890 {
    u8 pad0[4];
    s32 unk4;
    u8 pad8[0x1C];
    Node00140890 *unk24;
};

typedef struct S00140890 {
    u8 pad0[0x3BA4];
    s32 unk3BA4;
    u8 pad3BA8[4];
    s32 unk3BAC;
    u8 pad3BB0[0xC];
    s32 unk3BBC;
    s32 *unk3BC0;
    s32 *unk3BC4;
    s32 *unk3BC8;
    Node00140890 **unk3BCC;
    s32 unk3BD0;
    s32 unk3BD4;
} S00140890;

extern s32 MemStackAllocQw_14d950(s32, s32);

void DrawListSortBuckets_140890(S00140890 *arg0) {
    s32 h;
    s32 *cnt;
    s32 i;
    s32 c;
    s32 k;
    Node00140890 *nd;
    Node00140890 **q;

    h = arg0->unk3BA4;
    if (h == 0) return;
    cnt = arg0->unk3BC8;
    for (i = 0; i < arg0->unk3BBC; i++) {
        c = *cnt++;
        if (c > 0) {
            arg0->unk3BC0[i] = MemStackAllocQw_14d950(h, c / 4 + 1);
            arg0->unk3BC4[i] = arg0->unk3BC0[i];
        }
    }
    for (k = arg0->unk3BD4; k >= 0; k--) {
        nd = arg0->unk3BCC[k];
        if (nd != 0) {
            while (nd != 0) {
            q = (Node00140890 **)arg0->unk3BC4[nd->unk4];
            arg0->unk3BC4[nd->unk4] = (s32)(q + 1);
            *q = nd;
                nd = nd->unk24;
            }
        }
    }
    arg0->unk3BAC = 1;
}
