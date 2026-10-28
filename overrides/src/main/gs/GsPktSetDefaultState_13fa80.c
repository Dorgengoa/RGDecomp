/* rg-override: replaces game/src/main/gs/GsPktSetDefaultState_13fa80.c sha256 b98a13e5b03e719a272be6a94bd9c44af06a02de6db33c61719a17cd493883fc
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

extern void GsTestSetAlphaTest_157100(void *env, s32 v);
extern void GsTestSetDate_156ff0(void *env, s32 v);
extern void GsTestSetZTest_156f40(void *env, s32 v);
extern void GsZbufSetZMask_156ee0(void *env, s32 v);
extern void GsFbaSetEnable_156e80(void *env, s32 v);

#define PK_S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PK_U8(p, o)  (*((u8 *)(p) + (o)))

/* +0x70 is the cached GS PRIM value: clears ABE (0x40), TME (0x10), IIP (0x08),
   AA1 (0x80), FGE (0x20) and sets FST (bit 8 = +0x71 bit 0). */
void GsPktSetDefaultState_13fa80(void *pkt)
{
    PK_U8(pkt, 0x70) = (u8)(PK_U8(pkt, 0x70) & ~0x40);
    GsTestSetAlphaTest_157100((u8 *)pkt + 0x10, 1);
    GsTestSetDate_156ff0((u8 *)pkt + 0x10, 0);
    GsTestSetZTest_156f40((u8 *)pkt + 0x10, 2);
    PK_S32(pkt, 0xE4) = 1;
    GsZbufSetZMask_156ee0((u8 *)pkt + 0x10, 1);
    GsFbaSetEnable_156e80((u8 *)pkt + 0x10, 0);
    PK_U8(pkt, 0x70) = (u8)(PK_U8(pkt, 0x70) & ~0x10);
    PK_U8(pkt, 0x71) = (u8)((PK_U8(pkt, 0x71) & ~1) | 1);
    PK_S32(pkt, 0xE0) = 1;
    PK_U8(pkt, 0x70) = (u8)(PK_U8(pkt, 0x70) & ~0x08);
    PK_U8(pkt, 0x70) = (u8)(PK_U8(pkt, 0x70) & ~0x80);
    PK_U8(pkt, 0x70) = (u8)(PK_U8(pkt, 0x70) & ~0x20);
}
