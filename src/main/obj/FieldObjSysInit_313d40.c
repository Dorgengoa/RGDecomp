#include "types.h"

extern void GetDrawCtx_15de80(void);
extern void HandleHeapRefReset_312890(void *);
extern s32 MemStackAllocAligned64_14da10(s32, s32);
extern void HandleHeapRefInit_3128b0(void *, s32, s32, s32);
extern void HandleRegistryReset_314ab0(void *);
extern void ModelInit_151d50(void *);
extern void TargetMngClearTarget_313c00(void);
extern void TargetMngInit_320910(void *);
extern void TargetMngSetEnabled_31f4e0(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482A24;
extern s32 D_00482A38;
extern u8 D_004E7BE0[];
extern u8 D_004E7E60[];

void FieldObjSysInit_313d40(s32 p0, s32 p1)
{
    s32 r2;

    GetDrawCtx_15de80();
    HandleHeapRefReset_312890(&D_00482A24);
    r2 = MemStackAllocAligned64_14da10(p1, 0x2800);
    HandleHeapRefInit_3128b0(&D_00482A24, r2, 0x28000, 0x10);
    HandleRegistryReset_314ab0(&D_00482A38);
    ModelInit_151d50(D_004E7BE0);
    TargetMngClearTarget_313c00();
    TargetMngInit_320910(D_004E7E60);
    TargetMngSetEnabled_31f4e0(D_004E7E60, 1);
}
