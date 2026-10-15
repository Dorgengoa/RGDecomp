#include "types.h"

extern s32 NameTableFindByName_159fb0(s32, void *, s32);
extern s32 GetDrawCtxNameTable_15de40(void);
extern void GetDrawCtx_15de80(void);
extern u8 D_0049D0B0[0x2E0];

void TexPairResolveAll_18fa70(void) {
    s32 i;
    s32 id;
    u8 *e;

    for (i = 0; i < 8; i++) {
        GetDrawCtx_15de80();
        id = GetDrawCtxNameTable_15de40();
        e = D_0049D0B0 + i * 0x5C;
        *(s32 *)(e + 0x54) = NameTableFindByName_159fb0(id, e, -1);
        *(s32 *)(e + 0x58) = NameTableFindByName_159fb0(id, e + 0x20, -1);
    }
}
