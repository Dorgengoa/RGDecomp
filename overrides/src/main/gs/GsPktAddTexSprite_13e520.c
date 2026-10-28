/* rg-override: replaces game/src/main/gs/GsPktAddTexSprite_13e520.c sha256 032d144af1c8a817d5f4ea0c27d61b2f3842eee2a97ebc45780db754cc929346
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

extern void GsPktBeginPrimAD_13f6b0(void *pkt);
extern void GsPktSetTexture_13ec00(void *pkt, void *tex);
extern void GsPktFinalizeTags_13f260(void *pkt);
extern void GsPktOpenGifTag_13f3b0(void *pkt, s32 prim, s32 regs_lo, s32 regs_hi, s32 nreg);

/* Vertex placement by the origin mode at +0x11C (see GsPktDrawSprite). */
static void gspkt_xform_vtx(u8 *pkt, s32 *dst, const s32 *src)
{
    s32 mode = *(s32 *)(pkt + 0x11C);
    if (mode == 1) {
        __builtin_memcpy(dst, src, 16);
    } else if (mode == 2) {
        dst[0] = src[0] + *(s32 *)(pkt + 0x128);
        dst[1] = src[1] + *(s32 *)(pkt + 0x12C);
        dst[2] = src[2];
        dst[3] = src[3];
    } else {
        dst[0] = src[0] + *(s32 *)(pkt + 0x128) - *(s32 *)(pkt + 0x130) / 2;
        dst[1] = src[1] + *(s32 *)(pkt + 0x12C) - *(s32 *)(pkt + 0x134) / 2;
        dst[2] = src[2];
        dst[3] = src[3];
    }
}

/* Textured sprite.  spr: +0x00 RGBA (4 ints), +0x10 vertex 0, +0x20 vertex 1,
   +0x30 "split into strips" flag, +0x40 texture node, +0x50 UV 0, +0x60 UV 1.
   With the flag set and equal x and u extents, the sprite is cut into
   32-pixel-wide strips (0x200 in 12.4) to keep the texture cache happy. */
void GsPktAddTexSprite_13e520(void *pkt, void *sprite)
{
    u8 *b = (u8 *)pkt;
    u8 *s = (u8 *)sprite;
    u8 *p;

    if (*(s32 *)(s + 0x30) != 0
        && *(s32 *)(s + 0x10) - *(s32 *)(s + 0x20) == *(s32 *)(s + 0x50) - *(s32 *)(s + 0x60)) {
        s32 v0[4] __attribute__((aligned(16)));  /* sp+0x60 */
        s32 v1[4] __attribute__((aligned(16)));  /* sp+0x50 */
        s32 uv0[4] __attribute__((aligned(16))); /* sp+0x40 */
        s32 uv1[4] __attribute__((aligned(16))); /* sp+0x30 */
        s32 x, x1, u, u1;
        u64 rgbaq;

        *(s32 *)(b + 0x114) = 0;
        b[0x70] = (u8)((b[0x70] & ~7) | 6); /* PRIM = sprite */
        *(u32 *)(b + 0x110) = 0x3F800000u; /* Q = 1.0f */
        GsPktBeginPrimAD_13f6b0(pkt);
        GsPktSetTexture_13ec00(pkt, *(void **)(s + 0x40));

        /* inlined GsPktSetRGBAQ from the four ints at +0x00 */
        rgbaq = (u64)(s64)*(s32 *)(s + 0x0)
              | ((u64)(s64)*(s32 *)(s + 0x4) << 8)
              | ((u64)(s64)*(s32 *)(s + 0x8) << 16)
              | ((u64)(s64)*(s32 *)(s + 0xC) << 24);
        rgbaq |= (u64)*(u32 *)(b + 0x110) << 32;
        p = *(u8 **)(b + 0xF4);
        *(u64 *)(p + 0x0) = rgbaq;
        *(u64 *)(p + 0x8) = 1;
        *(u8 **)(b + 0xF4) = *(u8 **)(b + 0xF4) + 0x10;
        GsPktFinalizeTags_13f260(pkt);

        /* PACKED: UV, XYZF2, UV, XYZF2 (REGS 0x4343, NREG 4) */
        GsPktOpenGifTag_13f3b0(pkt, 6, 0x4343, 0, 4);
        gspkt_xform_vtx(b, v0, (const s32 *)(s + 0x10));
        gspkt_xform_vtx(b, v1, (const s32 *)(s + 0x20));
        __builtin_memcpy(uv1, s + 0x60, 16);
        __builtin_memcpy(uv0, s + 0x50, 16);

        u = *(s32 *)(s + 0x50);
        x1 = v1[0];
        u1 = uv1[0];
        x = v0[0];
        while (x < x1) {
            s32 nx = x + 0x200;
            v0[0] = x;
            v1[0] = nx;
            uv1[0] = u + 0x200;
            uv0[0] = u;
            if (x1 < nx)
                v1[0] = x1;
            if (u1 < uv1[0])
                uv1[0] = u1;
            x += 0x200;
            u += 0x200;
            p = *(u8 **)(b + 0xF4);
            *(u8 **)(b + 0xF4) = p + 0x40;
            __builtin_memcpy(p + 0x00, uv0, 16);
            __builtin_memcpy(p + 0x10, v0, 16);
            __builtin_memcpy(p + 0x20, uv1, 16);
            __builtin_memcpy(p + 0x30, v1, 16);
        }
        GsPktFinalizeTags_13f260(pkt);
        return;
    }

    /* one sprite: PACKED RGBAQ, UV, XYZF2, UV, XYZF2 (REGS 0x43431, NREG 5) */
    *(s32 *)(b + 0x114) = 0;
    b[0x70] = (u8)((b[0x70] & ~7) | 6);
    *(u32 *)(b + 0x110) = 0x3F800000u;
    GsPktBeginPrimAD_13f6b0(pkt);
    GsPktSetTexture_13ec00(pkt, *(void **)(s + 0x40));
    GsPktFinalizeTags_13f260(pkt);
    GsPktOpenGifTag_13f3b0(pkt, 6, 0x43431, 0, 5);
    p = *(u8 **)(b + 0xF4);
    *(u8 **)(b + 0xF4) = p + 0x10;
    __builtin_memcpy(p, s + 0x00, 16);
    p = *(u8 **)(b + 0xF4);
    *(u8 **)(b + 0xF4) = p + 0x40;
    __builtin_memcpy(p + 0x00, s + 0x50, 16);
    gspkt_xform_vtx(b, (s32 *)(p + 0x10), (const s32 *)(s + 0x10));
    __builtin_memcpy(p + 0x20, s + 0x60, 16);
    gspkt_xform_vtx(b, (s32 *)(p + 0x30), (const s32 *)(s + 0x20));
    GsPktFinalizeTags_13f260(pkt);
}
