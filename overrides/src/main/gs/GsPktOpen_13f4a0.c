/* rg-override: replaces game/src/main/gs/GsPktOpen_13f4a0.c sha256 006cd734f055aebd8a1a1737b6b0cc657ee220a37462cd8c7c736f6e3d160d30
 * why: asm body (asmexclude); C port on the VU0 model, from the retail listing */
#include "types.h"

extern s32 GsEnvWritePacket_157190(void *env, void *dst);

#define PK_S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PK_PTR(p, o) (*(u8 **)((u8 *)(p) + (o)))

/* Starts a packet at the memory stack's top (+0x00 -> stack; stack +0x28
   base, +0x2C used qwords): DMA cnt tag + VIF DIRECT 9, an A+D GIF tag of 2
   regs: NOP (0x3F) and PRMODECONT (0x1A) = 1, then the GS
   environment (GsEnvWritePacket on +0x10). */
void GsPktOpen_13f4a0(void *pkt)
{
    u8 *ms, *p;
    s32 n;

    PK_S32(pkt, 0xE8) = 1;
    if (*(void **)pkt == 0)
        return;
    PK_S32(pkt, 0xE8) = 0;
    ms = *(u8 **)pkt;
    p = *(u8 **)(ms + 0x28) + (*(s32 *)(ms + 0x2C) << 4);
    PK_PTR(pkt, 0xEC) = p;
    if (PK_S32(pkt, 0xF0) == 0) {
        /* [port] address: retail dsll32 4 / dsrl32 4 (& 0x0FFFFFFF) = the physical DMA
           address of the packet base; the port's DMA address is the host pointer, whole
           (docs/NATIVE-RENDER.md "DMA addresses") */
        PK_S32(pkt, 0xF0) = (s32)(u32)PK_PTR(pkt, 0xEC);
    }

    p = PK_PTR(pkt, 0xEC);
    PK_PTR(pkt, 0xF4) = p;
    *(u32 *)(p + 0x0) = 0x10000009u; /* DMAtag cnt, QWC 9 */
    *(u32 *)(p + 0x8) = 0;
    *(u32 *)(p + 0x4) = 0;
    *(u32 *)(p + 0xC) = 0x50000009u; /* VIF DIRECT 9 */

    p = PK_PTR(pkt, 0xF4);
    PK_PTR(pkt, 0xF4) = p + 0x10;
    PK_PTR(pkt, 0x100) = p + 0x10;
    *(u32 *)(p + 0x10) = 0x8002;
    *(u32 *)(p + 0x14) = 0x10000000;
    *(u32 *)(p + 0x18) = 0xE;
    *(u32 *)(p + 0x1C) = 0;

    p = PK_PTR(pkt, 0xF4);
    PK_PTR(pkt, 0xF4) = p + 0x10;
    *(u64 *)(p + 0x10) = 0;
    *(u64 *)(p + 0x18) = 0x3F;
    *(u64 *)(p + 0x20) = 1;
    *(u64 *)(p + 0x28) = 0x1A;
    PK_PTR(pkt, 0xF4) = p + 0x30;

    n = GsEnvWritePacket_157190((u8 *)pkt + 0x10, p + 0x30);
    PK_PTR(pkt, 0xF4) = PK_PTR(pkt, 0xF4) + (n << 4);
}
