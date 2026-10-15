#include "types.h"

typedef struct Old0014bbc0 {
    s32 u0;
    s32 a;
    s32 b;
    s32 c;
    s32 u10;
    s32 d;
    s32 e;
    s32 f;
    s32 g;
    s32 h;
    s32 u28;
    s32 u2C;
} Old0014bbc0;

typedef struct Sub0014bbc0 {
    s8 a;
    s8 b;
    s8 c;
    s8 h;
    s16 d;
    s16 e;
    s32 unk8;
    s32 unkC;
    u8 data[0x20];
    u8 data2[0x20];
} Sub0014bbc0;

typedef struct Rec0014bbc0 {
    s32 u0;
    s32 off;
} Rec0014bbc0;

typedef struct Node0014bbc0 {
    s32 next;
    s32 u4;
    s32 unk8;
    u32 count;
    Rec0014bbc0 recs[1];
} Node0014bbc0;

typedef struct Hdr0014bbc0 {
    s32 u0;
    s32 unk4;
    s32 u8;
    s32 unkC;
} Hdr0014bbc0;

extern void *memcpy(void *, const void *, u32);

s32 MotResRelocateBlockList_14bbc0(Hdr0014bbc0 **arg0, Node0014bbc0 *node)
{
    u8 *c;
    u32 j;
    Rec0014bbc0 *rec;
    Sub0014bbc0 *sub;
    Old0014bbc0 tmp;

    c = (u8 *)(*arg0)->unkC;
    for (; node != NULL; node = (Node0014bbc0 *)node->next) {
        if (node->next != 0) {
            node->next = (s32)((u8 *)node + node->next);
        }
        if (node->unk8 != 0) {
            node->unk8 = (s32)(c + node->unk8);
        }
        rec = node->recs;
        for (j = 0; j < node->count; j++, rec++) {
            if (rec->off == 0) {
                continue;
            }
            sub = (Sub0014bbc0 *)((u8 *)node + rec->off);
            rec->off = (s32)sub;
            if ((*arg0)->unk4 == 0) {
                tmp = *(Old0014bbc0 *)sub;
                sub->a = tmp.a;
                sub->b = tmp.b;
                sub->c = tmp.c;
                sub->h = tmp.h;
                sub->d = tmp.d;
                sub->e = tmp.e;
                sub->unk8 = tmp.f;
                sub->unkC = tmp.g;
                memcpy(sub->data, sub->data2, 0x20);
                sub = (Sub0014bbc0 *)(s32)sub;
            }
            while (sub != NULL) {
                if (sub->unk8 != 0) {
                    sub->unk8 = (s32)((u8 *)sub + sub->unk8);
                }
                if (sub->unkC != 0) {
                    sub->unkC = (s32)((u8 *)sub + sub->unkC);
                }
                break;
            }
        }
    }

    return 1;
}
