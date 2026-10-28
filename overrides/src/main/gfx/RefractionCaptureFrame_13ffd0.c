/* rg-override: replaces game/src/main/gfx/RefractionCaptureFrame_13ffd0.c sha256 77a5d997020aabdd335b8c2b4d335a870d6fd575f8fd3262a6c0f30ce8e5ccf6
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

extern void NameTableNodeReset_15ada0(void *node);
extern s32 NameTableNodeSetImage_15a640(void *node, s32 a1, void *name, s32 a3, s32 w, s32 h,
                                        s32 psm, s32 a7, s64 a8, s64 a9);
extern void *NameTableNodeCtor_15ae50(void *node);
extern void DrawEnvGetFrameTexDesc_144cc0(void *ctx, void *node);
extern void DrawEnvPush_144830(void *ctx);
extern void DrawEnvSetFrame_1575e0(void *env, s32 fbp, s32 fbw, s32 psm, s32 fbmsk, s32 a5);
extern s32 DrawEnvWritePacket_157460(void *env, void *dst);
extern s32 MemStackAllocQw_14d950(void *stack, s32 nqw);
extern void GsPktInit_13f7f0(void *pkt, void *stack, void *view);
extern void GsPktBegin_13f7e0(void *pkt);
extern void GsPktSetOriginMode_13e2f0(void *pkt, s32 mode);
extern void GsPktEnableZTest_13e460(void *pkt, s32 v);
extern void GsPktSetZWriteMask_13e430(void *pkt, s32 v);
extern void GsPktSetZTest_13e450(void *pkt, s32 v);
extern void GsPktSetAlphaBlend_13e500(void *pkt, s32 v);
extern void GsPktSetBlendMode_13e4f0(void *pkt, s32 v);
extern void GsPktEnableAlphaTest_13e4d0(void *pkt, s32 v);
extern void GsPktSetTextured_13e400(void *pkt, s32 v);
extern void GsPktOpenPrim_13f730(void *pkt, s32 prim);
extern void GsPktSetRGBAQ_13ee40(void *pkt, s32 r, s32 g, s32 b, s32 a);
extern void GsPktSetTexture_13ec00(void *pkt, void *tex);
extern void GsPktSetUVFixed_13ed90(void *pkt, s32 u, s32 v);
extern void GsPktSetXYZ_13ef10(void *pkt, s32 x, s32 y, s32 z);
extern void GsPktClose_13f5b0(void *pkt);
extern s32 GsPktEnd_13f790(void *pkt);

/* DMA "call" tag template at _gp-0x7330 */
extern rg_u128 D_0047DE40 __attribute__((section(".sdata")));
/* texture name buffer passed to NameTableNodeSetImage (lui 0x46 / -0x75B0) */
extern u8 D_00458A50[];

/* ctx +0x0 = frame index, +0x4 = DMA chain cursor, +0x8[] = per-frame
   memory stacks (stack = entry + 8), +0x270 = draw-env stack pointer. */
static void rcf_add_call_tag(u8 *ctx, u32 addr)
{
    u8 *p = *(u8 **)(ctx + 0x4);
    __builtin_memcpy(p, &D_0047DE40, 16);
    /* [port] address: retail dsll32 4 / dsrl32 4 (& 0x0FFFFFFF, the physical DMA address);
       the port's DMA address is the host pointer, whole (docs/NATIVE-RENDER.md "DMA
       addresses"; RG_HEAP_DMA_PLACEMENT 0 puts the heap anywhere) */
    *(u32 *)(*(u8 **)(ctx + 0x4) + 4) = addr;
    *(u8 **)(ctx + 0x4) = *(u8 **)(ctx + 0x4) + 0x10;
}

static u8 *rcf_cur_stack(u8 *ctx)
{
    u8 *e = *(u8 **)(ctx + 0x8 + (*(s32 *)ctx << 2));
    return e != 0 ? e + 8 : 0;
}

/* Writes the current draw env (at +0x270) into the frame's memory stack and
   chains it with a call tag. */
static void rcf_emit_env(u8 *ctx)
{
    void *env = *(void **)(ctx + 0x270);
    u8 *ms = rcf_cur_stack(ctx);
    u8 *dst;
    s32 n;

    if (ms == 0)
        return;
    dst = *(u8 **)(ms + 0x28) + (*(s32 *)(ms + 0x2C) << 4);
    n = DrawEnvWritePacket_157460(env, dst);
    MemStackAllocQw_14d950(ms, n);
    rcf_add_call_tag(ctx, (u32)dst);
}

/* Copies the frame buffer into a (1<<lg)-square texture via a sprite drawn
   into a temporary frame, for the refraction effect. */
void RefractionCaptureFrame_13ffd0(void *ctxv, s32 lg)
{
    u8 *ctx = (u8 *)ctxv;
    u8 tex[0x70] __attribute__((aligned(16))); /* sp+0x90 texture node */
    u8 *view;
    s32 size, nblk;
    s32 th, tw, fy, fx;
    u8 *pkt;
    s32 r;

    NameTableNodeReset_15ada0(ctx + 0x3BD8);
    view = *(u8 **)(ctx + 0x3BA0);
    size = 1 << lg;
    NameTableNodeSetImage_15a640(ctx + 0x3BD8, -10, D_00458A50, 0, size, size, 0x20, 0, 0, 0);

    /* the capture's TBP: VRAM top - (size*size*4 bytes) / 256 */
    nblk = (size * size * 4) / 256;
    *(u16 *)(ctx + 0x3C10) = (u16)((*(u16 *)(ctx + 0x3C10) & ~0x3FFF)
                                   | ((*(s32 *)(view + 0x4) - nblk) & 0x3FFF));
    ctx[0x3C14] = (u8)(ctx[0x3C14] & ~0x4);

    NameTableNodeCtor_15ae50(tex);
    DrawEnvGetFrameTexDesc_144cc0(ctx, tex);
    th = (s32)((u32)*(s16 *)(tex + 0x4) << 4);
    tw = (s32)((u32)*(s16 *)(tex + 0x2) << 4);
    fy = (s32)((u32)*(s16 *)(ctx + 0x3BDC) << 4);
    fx = (s32)((u32)*(s16 *)(ctx + 0x3BDA) << 4);
    DrawEnvPush_144830(ctx);

    /* `if (ctx + 0x3BD8 != 0)` in retail: always true */
    {
        u64 t0 = *(u64 *)(ctx + 0x3C10);
        s32 a1 = (*(u16 *)(ctx + 0x3C10) & 0x3FFF) >> 5;
        s32 a2 = (s32)(((t0 >> 14) & 0x3F) << 6);
        s32 a3 = *(s16 *)(ctx + 0x3BDC);
        s32 a4 = (*(u16 *)(ctx + 0x3C12) >> 4) & 0x3F;
        DrawEnvSetFrame_1575e0(*(void **)(ctx + 0x270), a1, a2, a3, a4, 0);
    }

    rcf_emit_env(ctx);

    pkt = ctx + 0x130;
    GsPktInit_13f7f0(pkt, rcf_cur_stack(ctx), *(void **)(ctx + 0x270));
    GsPktBegin_13f7e0(pkt);
    GsPktSetOriginMode_13e2f0(pkt, 0);
    GsPktEnableZTest_13e460(pkt, 0);
    GsPktSetZWriteMask_13e430(pkt, 1);
    GsPktSetZTest_13e450(pkt, 0);
    GsPktSetAlphaBlend_13e500(pkt, 4);
    GsPktSetBlendMode_13e4f0(pkt, 1);
    GsPktEnableAlphaTest_13e4d0(pkt, 0);
    GsPktSetTextured_13e400(pkt, 0);
    GsPktSetTextured_13e400(pkt, 1);
    GsPktOpenPrim_13f730(pkt, 6);
    GsPktSetRGBAQ_13ee40(pkt, 0x80, 0x80, 0x80, 0x80);
    GsPktSetTexture_13ec00(pkt, tex);
    GsPktSetUVFixed_13ed90(pkt, 0, 0);
    GsPktSetXYZ_13ef10(pkt, 0, 0, 0);
    GsPktSetUVFixed_13ed90(pkt, tw, th);
    GsPktSetXYZ_13ef10(pkt, fx, fy, 0);
    GsPktClose_13f5b0(pkt);
    r = GsPktEnd_13f790(pkt);
    if (r != 0)
        rcf_add_call_tag(ctx, (u32)r);

    rcf_emit_env(ctx);

    /* pop the draw-env stack */
    if ((u32)(ctx + 0x280) < (u32)*(u8 **)(ctx + 0x270))
        *(u8 **)(ctx + 0x270) = *(u8 **)(ctx + 0x270) - 0x190;

    rcf_emit_env(ctx);
}
