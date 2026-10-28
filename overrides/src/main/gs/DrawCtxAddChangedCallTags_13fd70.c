/* rg-override: replaces game/src/main/gs/DrawCtxAddChangedCallTags_13fd70.c sha256 96ca15e45d2022066718c065515611801c3d76e01b5a4ae6b28107db126e17d8
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

/* DMA "call" tag template at _gp-0x7330 (the same qword DmaPktAddCallTag
   copies); word 1 (ADDR) is patched per call. */
extern rg_u128 D_0047DE40 __attribute__((section(".sdata")));

/* ctx +0x4 = DMA chain cursor; +0x3C44 = cached count; +0x3C48.. = the
   cached call-target addresses. */
static void dctx_add_call_tag(u8 *ctx, u32 addr)
{
    u8 *p = *(u8 **)(ctx + 0x4);
    __builtin_memcpy(p, &D_0047DE40, 16);
    /* [port] address: retail dsll32 4 / dsrl32 4 (& 0x0FFFFFFF, the physical DMA
       address); the port's DMA address is the host pointer, whole (docs/NATIVE-RENDER.md
       "DMA addresses") */
    *(u32 *)(*(u8 **)(ctx + 0x4) + 4) = addr;
    *(u8 **)(ctx + 0x4) = *(u8 **)(ctx + 0x4) + 0x10;
}

/* Adds a DMA call tag for each of the n packet addresses that differs from
   the cached one.  n == 6 is unrolled in retail and does NOT update the
   cached count at +0x3C44; any other n first checks the count: if it
   changed, every address is emitted and the count stored. */
void DrawCtxAddChangedCallTags_13fd70(void *ctxv, const s32 *addrs, s32 n)
{
    u8 *ctx = (u8 *)ctxv;
    s32 *cache = (s32 *)(ctx + 0x3C48);

    if (n == 6) {
        s32 a[6];
        s32 k;
        for (k = 0; k < 6; k++)
            a[k] = addrs[k];
        for (k = 0; k < 6; k++) {
            if (cache[k] != a[k]) {
                dctx_add_call_tag(ctx, (u32)a[k]);
                cache[k] = a[k];
            }
        }
        return;
    }

    if (*(s32 *)(ctx + 0x3C44) != n) {
        s32 i;
        for (i = n; i > 0; i--) {
            s32 v = *addrs++;
            dctx_add_call_tag(ctx, (u32)v);
            *cache++ = v;
        }
        *(s32 *)(ctx + 0x3C44) = n;
        return;
    }

    while (n > 0) {
        s32 v = *addrs;
        if (*cache != v) {
            dctx_add_call_tag(ctx, (u32)v);
            *cache = v;
        }
        n--;
        addrs++;
        cache++;
    }
}
