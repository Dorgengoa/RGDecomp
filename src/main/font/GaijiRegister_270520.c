#include "types.h"

extern s32 GetDrawCtxNameTable_15de40(void);
extern s32 GaijiGetImageBuf_270590(void);
extern void NameTableRegisterImArchive_1594d0(s32, s32, s32, s32, s32);
extern s32 NameTableFindByName_159fb0(s32, void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045F680[];
extern s32 D_004820E0;

s32 GaijiRegister_270520(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 r3;

    r0 = GetDrawCtxNameTable_15de40();
    r1 = GaijiGetImageBuf_270590();
    NameTableRegisterImArchive_1594d0(r0, r1, p0, 0, 0);
    r3 = NameTableFindByName_159fb0(r0, D_0045F680, -1);
    D_004820E0 = r3;
    return r3;
}
