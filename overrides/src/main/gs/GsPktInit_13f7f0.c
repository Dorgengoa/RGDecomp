/* rg-override: replaces game/src/main/gs/GsPktInit_13f7f0.c sha256 27a92cc80333e3716d64c2b8115f515aabb11acf60f2e44dd29e77c5109ee4b6
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

extern void NameTableNodeReset_15ada0(void *node);
extern void GsEnvInit_1573b0(void *env);
extern void DrawEnvGetZbufReg_157770(void *view, void *dst);
extern void GsFrameSet_156e10(void *env, void *frame);
extern void GsTestSetAlphaTest_157100(void *env, s32 v);
extern void GsTestSetDate_156ff0(void *env, s32 v);
extern void GsTestSetZTest_156f40(void *env, s32 v);
extern void GsZbufSetZMask_156ee0(void *env, s32 v);
extern void GsFbaSetEnable_156e80(void *env, s32 v);

#define PK_S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PK_U8(p, o)  (*((u8 *)(p) + (o)))

void GsPktInit_13f7f0(void *pkt, void *stack, void *view)
{
    u8 *v = (u8 *)view;
    s32 mode;

    *(void **)pkt = stack;
    PK_S32(pkt, 0x4) = 0;
    PK_S32(pkt, 0xE8) = 1;
    NameTableNodeReset_15ada0((u8 *)pkt + 0x78);
    GsEnvInit_1573b0((u8 *)pkt + 0x10);
    DrawEnvGetZbufReg_157770(view, (u8 *)pkt + 0x40);
    GsFrameSet_156e10((u8 *)pkt + 0x10, v + 0x80);

    PK_S32(pkt, 0x128) = (s32)((u32)*(s32 *)(v + 0xC) << 4);  /* origin X (12.4) */
    PK_S32(pkt, 0x12C) = (s32)((u32)*(s32 *)(v + 0x10) << 4); /* origin Y */
    PK_S32(pkt, 0x130) = (s32)((u32)*(s32 *)(v + 0x4) << 4);  /* width */
    PK_S32(pkt, 0x134) = (s32)((u32)*(s32 *)(v + 0x8) << 4);  /* height */

    /* origin mode: retail inlines the setter with the constant 0 */
    mode = 0;
    PK_S32(pkt, 0x11C) = mode;
    if (mode == 1) {
        PK_S32(pkt, 0x124) = 0;
        PK_S32(pkt, 0x120) = 0;
    } else if (mode == 2) {
        PK_S32(pkt, 0x120) = PK_S32(pkt, 0x128);
        PK_S32(pkt, 0x124) = PK_S32(pkt, 0x12C);
    } else {
        PK_S32(pkt, 0x120) = PK_S32(pkt, 0x128) - PK_S32(pkt, 0x130) / 2;
        PK_S32(pkt, 0x124) = PK_S32(pkt, 0x12C) - PK_S32(pkt, 0x134) / 2;
    }

    /* the default state, inlined (same sequence as GsPktSetDefaultState) */
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
