/* rgp:protos */
#define RGP_SELF_EvCmdMenuThinkClose_25fbb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_0045F0A0[0x100];
extern u8 D_0045F0B0[0x100];

struct S0025FBB0 {
    u8 pad00[0x10];
    s32 unk10;
};

typedef struct {
    f32 a;
    f32 b;
    f32 c;
} Vec3F;

s32 EvCmdMenuThinkClose_25fbb0(void)
{
    Vec3F sp30_38 __attribute__((aligned(16)));
    f32 sp20[3];
    struct S0025FBB0 *temp_16;

    TaskSetEnabled_27c2a0(0, D_0045F0A0);
    TaskSetEnabled_27c2a0(0, D_0045F0B0);
    ThinkMenuClose_2035a0();
    temp_16 = (struct S0025FBB0 *)GetGameData_1fede0();
    func_5219C0(sp20);
    sp30_38 = *(Vec3F *)sp20;
    StateVarSet_3cc9c0(temp_16->unk10, 0x7C, *(s16 *)&sp30_38.b, 1);
    StateVarSet_3cc9c0(temp_16->unk10, 0x7D, *(s16 *)&sp30_38.c, 1);
    return 1;
}
