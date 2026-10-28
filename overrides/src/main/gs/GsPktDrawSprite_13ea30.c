/* rg-override: replaces game/src/main/gs/GsPktDrawSprite_13ea30.c sha256 f9070951f725d04d75882652a11c86423f20c3657caef98c3e7ec72fc4c0f8a9
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

extern void GsPktOpenGifTag_13f3b0(void *pkt, s32 prim, s32 regs_lo, s32 regs_hi, s32 nreg);
extern void GsPktFinalizeTags_13f260(void *pkt);

/* Vertex (x, y, z, w ints) placed by the origin mode at +0x11C:
   1 = as is, 2 = + offset (+0x128/+0x12C), else + offset - size/2
   (+0x130/+0x134; signed /2 like the bgez/sra sequence). */
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

/* Untextured sprite: PACKED GIF tag (PRIM 6 = sprite, REGS 0x441 =
   RGBAQ, XYZF2, XYZF2, NREG 3), colour qword, two placed vertices.
   rect: +0x00 RGBA qword, +0x10 vertex 0, +0x20 vertex 1. */
void GsPktDrawSprite_13ea30(void *pkt, void *rect)
{
    u8 *b = (u8 *)pkt;
    u8 *r = (u8 *)rect;
    u8 *p;

    GsPktOpenGifTag_13f3b0(pkt, 6, 0x441, 0, 3);
    p = *(u8 **)(b + 0xF4);
    *(u8 **)(b + 0xF4) = p + 0x10;
    __builtin_memcpy(p, r, 16);
    p = *(u8 **)(b + 0xF4);
    *(u8 **)(b + 0xF4) = p + 0x20;
    gspkt_xform_vtx(b, (s32 *)(p + 0x00), (const s32 *)(r + 0x10));
    gspkt_xform_vtx(b, (s32 *)(p + 0x10), (const s32 *)(r + 0x20));
    GsPktFinalizeTags_13f260(pkt);
}
