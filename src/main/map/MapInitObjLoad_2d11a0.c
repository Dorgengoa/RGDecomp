#include "types.h"

/* `len` has its address taken, so it lives on the stack and is re-loaded
   at every use.  The bgez/sra/addiu 0xF/sra block is a signed /16 (a
   power-of-two shift, no divide trap).  D_0046xxxx are %hi/%lo =>
   incomplete arrays. */

extern char D_00461580[];
extern char D_004615A0[];

extern void *GetSystemMemStack_202600(void);
extern void *GetReadBuffHeap_2025e0(void);
extern void *MemStackHeapAlloc_14db10(void *, s32, s32, s32);
extern void *GetDrawCtxNameTable_15de40(void);
extern void MemStackAlign64_14d8e0(void *);
extern s32 ResidentFileReadLocalizedMaybe_1c2860(char *, void *, s32 *);
extern void EventScriptRunTwoPass_2fd9d0(void *, s32, s32, s32);
extern void *MemStackAllocQw_14d950(void *, s32);
extern void *memcpy(void *, void *, u32);
extern void NameTableRegisterImArchive_1594d0(void *, void *, s32, void *, s32);
extern void MemStackReturnToOwnerMaybe_14dad0(void *);
extern void MemStackHeapFree_14dcb0(void *, void *);

void MapInitObjLoad_2d11a0(void)
{
    void *heap;
    void *fs;
    void *buf;
    void *ctx;
    void *dst;
    s32 len;

    heap = GetSystemMemStack_202600();
    fs = GetReadBuffHeap_2025e0();
    buf = MemStackHeapAlloc_14db10(fs, 2, 0, 0x40);
    if (buf != 0) {
        ctx = GetDrawCtxNameTable_15de40();
        MemStackAlign64_14d8e0(fs);
        if (ResidentFileReadLocalizedMaybe_1c2860(D_00461580, buf, &len) != 0) {
            EventScriptRunTwoPass_2fd9d0(buf, len, -1, -1);
        }
        if (ResidentFileReadLocalizedMaybe_1c2860(D_004615A0, buf, &len) != 0) {
            dst = MemStackAllocQw_14d950(heap, (len / 16) + 1);
            memcpy(dst, buf, len);
            NameTableRegisterImArchive_1594d0(ctx, dst, 0x334, heap, 0);
        }
        MemStackReturnToOwnerMaybe_14dad0(fs);
        MemStackHeapFree_14dcb0(fs, buf);
    }
}
