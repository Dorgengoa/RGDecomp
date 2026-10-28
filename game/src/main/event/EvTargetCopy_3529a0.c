/* rgp:protos */
#define RGP_SELF_EvTargetCopy_3529a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct O {
    u8 pad0[0x30];
    s32 m30;
    u8 pad34[0x9C];
    f32 v[6][4];
    s32 n;
} O;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvTargetCopy_3529a0(O *arg0, O *arg1, s32 arg2)
{
    s32 r;
    s32 j;

    EvTargetInit_352be0(arg0);
    if ((arg1 == NULL) || (arg2 == 0)) {
        return 0;
    }
    if (TargetRefCopy_2e7140(arg0, ((s32)EvTargetGetTargetRef_352990(arg1)), arg2) == 0) {
        return 0;
    }
    r = ((s32)MemStackStrDup_14cff0(EvTargetGetName_352980(arg1), arg2));
    arg0->m30 = r;
    if (r == 0) {
        return 0;
    }
    if (arg1->n > 0) {
        for (arg0->n = 0; arg0->n < arg1->n; arg0->n++) {
            arg0->v[*(s32 *)((u8 *)arg0 + 0x130)][0] = arg1->v[*(s32 *)((u8 *)arg0 + 0x130)][0];
            arg0->v[*(s32 *)((u8 *)arg0 + 0x130)][1] = arg1->v[*(s32 *)((u8 *)arg0 + 0x130)][1];
            arg0->v[*(s32 *)((u8 *)arg0 + 0x130)][2] = arg1->v[*(s32 *)((u8 *)arg0 + 0x130)][2];
            arg0->v[*(s32 *)((u8 *)arg0 + 0x130)][3] = 1.0f;
        }
    }
    return 1;
}
