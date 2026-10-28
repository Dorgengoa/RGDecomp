/* rg-override: replaces game/src/main/gs/GsPktDisableTests_13f9e0.c sha256 74668639640c8c751e5654ac001807bb408d10d9cb875e83d6ef59685f4b2294
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

extern void GsTestSetZTest_156f40(void *env, s32 v);
extern void GsZbufSetZMask_156ee0(void *env, s32 v);
extern void GsTestSetAlphaTest_157100(void *env, s32 v);
extern void GsTestSetDate_156ff0(void *env, s32 v);

#define PK_S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PK_U8(p, o)  (*((u8 *)(p) + (o)))

void GsPktDisableTests_13f9e0(void *pkt)
{
    GsTestSetZTest_156f40((u8 *)pkt + 0x10, 0);
    PK_S32(pkt, 0xE4) = 1;
    GsZbufSetZMask_156ee0((u8 *)pkt + 0x10, 1);
    GsTestSetZTest_156f40((u8 *)pkt + 0x10, 0);
    PK_U8(pkt, 0x70) = (u8)(PK_U8(pkt, 0x70) & ~0x40);
    GsTestSetAlphaTest_157100((u8 *)pkt + 0x10, 0);
    GsTestSetDate_156ff0((u8 *)pkt + 0x10, 0);
    PK_U8(pkt, 0x70) = (u8)(PK_U8(pkt, 0x70) & ~0x10);
}
