#include "types.h"
#pragma opt_propagation off
#pragma opt_common_subs off
s32 HashTableFreeNodes_1a89c0(s32, s32, s32);
static inline s32 isnull(u8 *p) { return !(p != 0); }

void EffInstFreeParticles_19a7b0(u8 *arg0, s32 arg1, u8 *arg2) {
    u8 **pp;
    s32 i;
    u8 *node;
    u8 *t;
    s32 j;
    u8 *e;
    s32 a;
    s32 b;

    pp = *(u8 ***)(arg0 + 0xA0);
    if (*(s32 *)(arg2 + 0xC4) == 0) {
        return;
    }
    for (i = 0; i < *(s32 *)(arg0 + 0x9C); i++, pp++) {
        t = *(u8 **)(*pp + 0xC);
        if (t == 0) {
            continue;
        }
        node = *(u8 **)(t + 0x44);
        e = *(u8 **)(arg2 + 0xC4) + i * 0x120;
        for (j = 0; !isnull(node) && j < *(s32 *)(e + 0xC0); j++) {
            a = *(s32 *)(node + 4);
            HashTableFreeNodes_1a89c0(a, arg1, *(s32 *)(e + 0xC4) + j * 0x110);
            node = *(u8 **)node;
        }
    }
}
