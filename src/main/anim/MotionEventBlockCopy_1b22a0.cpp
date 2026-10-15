#include "types.h"

class VE {
    u8 pad_[0x24];
public:
    virtual void * f08();
};

/* Copy-with-remap.  $6 == 0 -> the three tail words are copied verbatim
   (that arm is the FALL-THROUGH, so it is the source's `if` body).
   The loop reuses the `src` register for the per-node child, which is why the
   node pointer is loaded in the bnel delay slot.  Indirect call = C_table:
   a handler table pointer held at offset 0x24 of the node, slot 0x8.        */

typedef struct Node Node;

extern "C" void *MemStackStrDup_14cf10(void *, void *);
extern "C" void MotionEventBlockNewEvent_1b1df0(void *, void *, void *, Node *);

extern "C" void MotionEventBlockCopy_1b22a0(u8 *src, u8 *dst, void *ctx)
{
    u8 *n;
    u8 *q;

    *(s32 *)(dst + 0x00) = *(s32 *)(src + 0x00);
    *(s32 *)(dst + 0x04) = *(s32 *)(src + 0x04);
    if (ctx == 0) {
        *(s32 *)(dst + 0x08) = *(s32 *)(src + 0x08);
        *(s32 *)(dst + 0x0C) = *(s32 *)(src + 0x0C);
        *(s32 *)(dst + 0x10) = *(s32 *)(src + 0x10);
    } else {
        *(void **)(dst + 0x08) = MemStackStrDup_14cf10(*(void **)(src + 0x08), ctx);
        *(void **)(dst + 0x0C) = MemStackStrDup_14cf10(*(void **)(src + 0x0C), ctx);
        *(s32 *)(dst + 0x10) = 0;
        for (n = *(u8 **)(src + 0x10); n != 0; n = *(u8 **)(n + 0x00)) {
            q = *(u8 **)(n + 0x10);
            MotionEventBlockNewEvent_1b1df0(dst, ctx, ((VE *)q)->f08(), (Node *)q);
        }
    }
}
