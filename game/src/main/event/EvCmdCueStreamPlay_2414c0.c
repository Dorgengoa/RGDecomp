/* rgp:protos */
#define RGP_SELF_EvCmdCueStreamPlay_2414c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D288;
extern void *gEventContext;

typedef struct {
    s32 type;
    s32 val;
    f32 f;
} Ev;

s32 EvCmdCueStreamPlay_2414c0(s64 *arg0) {
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x0 + sizeof(Ev)]; char m1[0x10]; })];
    f32 f;
    s32 id;
    s32 t;

    id = ScriptGetInt_2490f0((s32)arg0++);
    f = 1.0f;
    if (*(s32 *)arg0 == 1) {
        f = TaggedGetFloat_2490d0(arg0);
    } else if (*(s32 *)arg0 == 0) {
        t = (s32)TaggedGetFloat_2490d0(arg0);
        if (t == 0) {
            f = 1.0f;
        }
        if (t == 1) {
            f = D_0047D288;
        }
    }
    (*(Ev *)(rgp_blk1 + 0x0)).val = id;
    (*(Ev *)(rgp_blk1 + 0x0)).type = 6;
    (*(Ev *)(rgp_blk1 + 0x0)).f = f;
    Vec4VectorPushBack_249120(*(s32 *)((u8 *)gEventContext + 4), &(*(Ev *)(rgp_blk1 + 0x0)));
    return 1;
}
