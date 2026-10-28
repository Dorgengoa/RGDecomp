/* rgp:protos */
#define RGP_SELF_ScriptCmdVecDiv_3344d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Node {
    u8 pad00[0x4];
    f32 m04;
};

struct Obj {
    u8 pad00[0x4];
    struct Node *m04;
    u8 pad08[0x4];
    struct Node *m0C;
    u8 pad10[0x4];
    struct Node *m14;
};

/*rgp*/
/*rgp*/

s32 ScriptCmdVecDiv_3344d0(struct Obj *o, s32 mode)
{
    f32 s;

    if (mode != 4) {
        return 0;
    }
    s = ScriptSlotGetFloat_334890((u8 *)o + 0x18);
    if (s == 0.0f) {
        return 0;
    }
    ScriptSlotStoreFloatRef_3347d0(o, o->m04->m04 / s);
    ScriptSlotStoreFloatRef_3347d0((u8 *)o + 8, o->m0C->m04 / s);
    ScriptSlotStoreFloatRef_3347d0((u8 *)o + 0x10, o->m14->m04 / s);
    return 1;
}
