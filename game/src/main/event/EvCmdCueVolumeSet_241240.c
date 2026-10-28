/* rgp:protos */
#define RGP_SELF_EvCmdCueVolumeSet_241240 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s32 a, b; } T_00241240;
typedef struct { s32 a; s32 b; f32 c; } M_00241240;

/*rgp*/
/*rgp*/
/*rgp*/
extern struct { s32 f0; void *f4; } *gEventContext;

s32 EvCmdCueVolumeSet_241240(T_00241240 *q)
{
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x0 + sizeof(M_00241240)]; char m1[0x10]; })];
    s32 r;
    f32 f;

    r = ScriptGetInt_2490f0(q++);
    f = TaggedGetFloat_2490d0(q);
    (*(M_00241240 *)(rgp_blk1 + 0x0)).b = r;
    (*(M_00241240 *)(rgp_blk1 + 0x0)).a = 9;
    (*(M_00241240 *)(rgp_blk1 + 0x0)).c = f;
    Vec4VectorPushBack_249120(gEventContext->f4, &(*(M_00241240 *)(rgp_blk1 + 0x0)));
    return 1;
}
