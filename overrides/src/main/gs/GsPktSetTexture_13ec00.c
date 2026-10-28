/* rg-override: replaces game/src/main/gs/GsPktSetTexture_13ec00.c sha256 d9a4d076adb5648fdb9263b89e589ff6740332e49534f27b002c0bb9b84dd77b
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

extern void *NameTableCopyNode_15ad70(void *dst, void *src);
extern void GsTex1SetFilter_15ac10(void *node, s32 filter);

/* Copies the texture node into +0x78, applies the filter at +0xE0, then
   writes four A+D qwords: NOP (0x3F), TEX1_1 (0x14) from +0xB8,
   TEX0_1 (0x06) from +0xB0, CLAMP_1 (0x08) from +0xC0. */
void GsPktSetTexture_13ec00(void *pkt, void *tex)
{
    u8 *b = (u8 *)pkt;
    u8 *p;

    if (tex == 0)
        return;
    NameTableCopyNode_15ad70(b + 0x78, tex);
    GsTex1SetFilter_15ac10(b + 0x78, *(s32 *)(b + 0xE0));
    p = *(u8 **)(b + 0xF4);
    *(u64 *)(p + 0x00) = 0;
    *(u64 *)(p + 0x08) = 0x3F;
    *(u64 *)(p + 0x10) = *(u64 *)(b + 0xB8);
    *(u64 *)(p + 0x18) = 0x14;
    *(u64 *)(p + 0x20) = *(u64 *)(b + 0xB0);
    *(u64 *)(p + 0x28) = 0x06;
    *(u64 *)(p + 0x30) = *(u64 *)(b + 0xC0);
    *(u64 *)(p + 0x38) = 0x08;
    *(u8 **)(b + 0xF4) = p + 0x40;
}
