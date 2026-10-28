/* rgp:protos */
#define RGP_SELF_MapEntryCloneWithCardNode_1e12c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S_001e12c0 {
    u8 pad0[0x794];
    s32 f794;
} S_001e12c0;

extern u8 D_0045B478[];
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MapEntryCloneWithCardNode_1e12c0(S_001e12c0 *a, void *b, void *c, int rgp_a3)
{
    s32 t;
    MapEntryReset_1e1350(a, (int)b, (int)c, (int)rgp_a3);
    if (b == 0) goto zero;
    if (c != 0) goto ok;
zero:
    return 0;
ok:
    ModelObjExCopy_1aff40(b, a, c);
    t = ModelFindFrameIndexByName_151220(a, D_0045B478);
    a->f794 = ((s32)ModelGetFrame_1511f0(a, t));
    return 1;
}
