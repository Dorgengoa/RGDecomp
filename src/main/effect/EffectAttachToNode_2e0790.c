#include "types.h"

struct Vec09f0 { f32 x, y, z, w; } __attribute__((aligned(16)));

typedef struct Cmd09f0 {
    s16 mode;               /* 0x00 */
    u8 pad02[0x6];
    s32 idx;                /* 0x08 */
    s32 arg;                /* 0x0C */
} Cmd09f0;

typedef struct Node09f0 {
    u8 pad00[0x30];
    struct Vec09f0 f20;
} Node09f0;

extern Node09f0 *HandleTableGetDeref_1a0ca0(void *, s32);
extern void EffectEntryAttachToNodeByIdx_2ddfe0(void *, Cmd09f0 *, s32 );

static __inline s32 IsNull09f0(s32 v)
{
    return !v;
}

s32 EffectAttachToNode_2e0790(u8 *base, Cmd09f0 *cmd, s32 src)
{
    s32 i;
    u8 *p;
    Node09f0 *n;

    if (cmd->mode == 1) {
        i = cmd->idx;
        if (i < 0 || i >= 0x30) {
            return 1;
        }
        p = (u8 *)(i * 0x70 - (-(s32)base));
        if (*(s32 *)(p + 0x1D0) != 1) {
            return 2;
        }
        if (*(s32 *)(p + 0x174) < 0) {
            return 3;
        }
        if (IsNull09f0(cmd->arg)) {
            return 4;
        }
        n = HandleTableGetDeref_1a0ca0(base + 0x58, *(volatile s32 *)&cmd->arg);
        if (n != 0) {
            *(s32 *)((u8 *)n + 0xEC) = src;
        }
        goto done;
    }
    if (cmd->mode == 2) {
        goto docall;
    }
    if (cmd->mode != 3) {
        goto done;
    }
docall:
    EffectEntryAttachToNodeByIdx_2ddfe0(base + 0x1674, cmd, src);
done:
    return 0;
}
