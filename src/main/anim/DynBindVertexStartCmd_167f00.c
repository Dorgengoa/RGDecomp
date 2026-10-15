#include "types.h"

typedef struct {
    u8 padD4[0xD4];
    s32 unkD4;
    void *unkD8;
} S00481154;

extern void *MemStackAllocQw_14d950(s32 a, u32 b);
extern s32 VariantGetInt_15f780(void);
extern void *memset(void *, s32, u32);
extern S00481154 *D_00481154;
extern s32 D_00481158;
extern s32 D_0048116C;
extern s32 D_00481178;

s32 DynBindVertexStartCmd_167f00(void) {
    s32 count;
    s32 g;
    u32 bytes;
    u32 blocks;
    S00481154 *ctx;
    s32 i;

    count = VariantGetInt_15f780();
    g = D_00481158;
    bytes = count * 0x10;
    ctx = D_00481154;
    ctx->unkD4 = count;
    if (bytes & 0xF) {
        blocks = (bytes >> 4) + 1;
    } else {
        blocks = bytes >> 4;
    }
    ctx->unkD8 = MemStackAllocQw_14d950(g, blocks);
    for (i = 0; i < ctx->unkD4; i++) {
        memset((u8 *)ctx->unkD8 + (i * 0x10), 0, 0x10);
    }
    D_00481178 = 0;
    D_0048116C = 0;
    return 1;
}
