#include "types.h"

/* Three call results held in callee-saved regs ($19,$18,$17 = declaration
   order descending) plus a fourth ($16).  Stack locals go in REVERSE
   declaration order (last-declared gets the LOWEST address): `tag` at 0x5C is
   declared first, the 12-byte `rec` at 0x50 second. */

extern u8 D_00462340[];
extern u8 D_004E7BE0[];

extern void *GetSystemMemStack_202600(void);
extern void *GetDrawCtx_15de80(void);
extern void *GetReadBuffHeap_2025e0(void);
extern void *MemStackHeapAlloc_14db10(void *a, s32 b, s32 c, s32 d);
extern void MemStackAlign64_14d8e0(void *a);
extern s32 ResidentFileReadLocalizedMaybe_1c2860(void *a, void *b, s32 *c);
extern void ModelResRelocate_14bfd0(void *a, void *b);
extern void ModelBuildFrames_1506c0(void *a, void *b, void *c, void *d);
extern void MemStackReturnToOwnerMaybe_14dad0(void *a);
extern void MemStackHeapFree_14dcb0(void *a, void *b);

typedef struct Rec00313c60 {
    s32 m00;
    s32 m04;
    s32 m08;
} Rec00313c60;

void SphereModelLoad_313c60(void)
{
    s32 tag;
    Rec00313c60 rec;
    void *a;
    void *b;
    void *c;
    void *d;

    a = GetSystemMemStack_202600();
    b = GetDrawCtx_15de80();
    c = GetReadBuffHeap_2025e0();
    if (c == 0) {
        return;
    }
    d = MemStackHeapAlloc_14db10(c, 2, 0, 0x40);
    if (d == 0) {
        return;
    }
    MemStackAlign64_14d8e0(c);
    if (ResidentFileReadLocalizedMaybe_1c2860(D_00462340, d, &tag) != 0) {
        rec.m00 = 0;
        ModelResRelocate_14bfd0(&rec, d);
        ModelBuildFrames_1506c0(D_004E7BE0, &rec, b, a);
    }
    MemStackReturnToOwnerMaybe_14dad0(c);
    MemStackHeapFree_14dcb0(c, d);
}
