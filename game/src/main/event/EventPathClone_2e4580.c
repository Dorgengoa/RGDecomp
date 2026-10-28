/* rgp:protos */
#define RGP_SELF_EventPathClone_2e4580 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S002e4580 { s32 unk0; s32 unk4; s32 unk8; s16 unkC; s16 unkE; } S002e4580;
typedef struct Arg1_2e4580 { u8 pad0[8]; s32 unk8; s16 unkC; } Arg1_2e4580;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void memcpy(s32, s32, s32);
/*rgp*/
s32 EventPathClone_2e4580(S002e4580 *arg0, Arg1_2e4580 *arg1, s32 arg2) {
    s32 t;
    s16 n;
    s32 i;
    EventPathClear_2e4720((void *)arg0);
    if (!(arg1 != NULL && arg2 != 0)) return 0;
    t = ((s32)MemStackStrDup_14cff0(EventPathGetName_2e4570(arg1), arg2));
    arg0->unk0 = t;
    if (t == 0) return 0;
    n = arg1->unkC;
    t = ((s32)ConstructNewArray_100710(((s32)MemStackNew_14e1b0((n * 8) + 0x10, arg2)), (void *)EventPathSegCtor_2e47f0, 0, 8, n));
    arg0->unk8 = t;
    if (t == 0) return 0;
    n = arg1->unkC;
    arg0->unkC = n;
    memcpy(arg0->unk8, arg1->unk8, n * 8);
    i = 0;
    while (i < arg0->unkC) {
        n = EventPathSegGetLength_2e4770(arg0->unk8 + (i * 8));
        i += 1;
        arg0->unkE = (s16)(arg0->unkE + n);
    }
    arg0->unk4 = EventPathGetFlags_2e4560(arg1);
    return 1;
}
