/* rgp:protos */
#define RGP_SELF_HandleHeapCompact_312aa0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_s128 s128;

typedef struct Node00312aa0 {
    u8 *unk0;
    struct Node00312aa0 *unk4;
    struct Node00312aa0 *unk8;
} Node00312aa0;

typedef struct S00312aa0 {
    u8 pad0[8];
    s32 unk8;
    u8 *unkC;
    u8 pad10[4];
    Node00312aa0 *unk14;
    Node00312aa0 *unk18;
    Node00312aa0 *unk1C;
} S00312aa0;

extern void memmove(void *dst, void *src, u32 n);

void HandleHeapCompact_312aa0(S00312aa0 *arg0)
{

    s128 *d;
    Node00312aa0 *cur;
    u8 *dst;
    u32 size;
    s128 *s;
    Node00312aa0 *prev;
    Node00312aa0 *next;
    s32 n;
    u8 *src;
    cur = arg0->unk14;
    if (cur == NULL) {
        return;
    }
    prev = NULL;
    dst = NULL;
    while (cur != NULL) {
        next = cur->unk8;
        if (cur->unk4 == NULL) {
            if (dst == NULL) {
                dst = cur->unk0;
            }
            if (prev != NULL) {
                prev->unk8 = next;
                if (cur == arg0->unk18) {
                    arg0->unk18 = prev;
                }
            } else {
                arg0->unk14 = next;
                if (cur == arg0->unk18) {
                    arg0->unk18 = arg0->unk14;
                }
            }
            cur->unk8 = arg0->unk1C;
            arg0->unk1C = cur;
            cur = next;
            continue;
        }
        {
            if (dst != NULL) {
                if (next != NULL) {
                    src = cur->unk0;
                    size = next->unk0 - src;
                } else {
                    src = cur->unk0;
                    size = arg0->unkC - src;
                }
                if (!(arg0->unk8 & 0xF)) {
                    s = (s128 *)src;
                    d = (s128 *)dst;
                    n = size >> 4;
                    while (n > 0) {
                        n--;
                        *d = *s;
                        s++;
                        d++;
                    }
                } else {
                    memmove(dst, *(u8 **)cur, size);
                }
                cur->unk0 = dst;
                dst += size;
            }
            prev = cur;
        }
        cur = next;
    }
    if (dst != NULL) {
        arg0->unkC = dst;
    }
}
