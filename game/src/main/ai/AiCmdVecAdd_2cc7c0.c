/* rgp:protos */
#define RGP_SELF_AiCmdVecAdd_2cc7c0 1
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

s32 AiCmdVecAdd_2cc7c0(struct Obj *o, s32 mode)
{
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x0 + sizeof(f32[3])]; char m1[0x10]; })];

    if (mode != 6) {
        return 0;
    }
    ScriptSlotsToVec4_2cc920((*(f32 (*)[3])(rgp_blk1 + 0x0)), (u8 *)o + 0x18);
    ScriptSlotStoreFloatRef_2cc8e0(o, o->m04->m04 + (*(f32 (*)[3])(rgp_blk1 + 0x0))[0]);
    ScriptSlotStoreFloatRef_2cc8e0((u8 *)o + 8, o->m0C->m04 + (*(f32 (*)[3])(rgp_blk1 + 0x0))[1]);
    ScriptSlotStoreFloatRef_2cc8e0((u8 *)o + 0x10, o->m14->m04 + (*(f32 (*)[3])(rgp_blk1 + 0x0))[2]);
    return 1;
}
