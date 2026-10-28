/* rgp:protos */
#define RGP_SELF_EvCmdCharaGetEvObjContactXform_25a420 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Vec3 { f32 x, y, z; } Vec3;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdCharaGetEvObjContactXform_25a420(s64 *arg0, s32 arg1)
{ __typeof__(arg0) rgp_entry_arg0 = arg0;
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x0 + sizeof(Vec3)]; char m1[0x10]; })];
    __attribute__((aligned(16))) unsigned char rgp_blk2[sizeof(union { char m0[0x0 + sizeof(Vec3)]; char m1[0x10]; })];
    s32 k;

    arg0++;
    k = CharaGetEvObjContactXform_2d08c0(ScriptGetInt_26a2a0((void *)rgp_entry_arg0), &(*(Vec3 *)(rgp_blk1 + 0x0)), &(*(Vec3 *)(rgp_blk2 + 0x0)));
    ScriptSetRefInt_26a1e0(arg0++, k);
    ScriptSetRefFloat_26a1c0(arg0++, (*(Vec3 *)(rgp_blk1 + 0x0)).x);
    ScriptSetRefFloat_26a1c0(arg0++, (*(Vec3 *)(rgp_blk1 + 0x0)).y);
    ScriptSetRefFloat_26a1c0(arg0++, (*(Vec3 *)(rgp_blk1 + 0x0)).z);
    ScriptSetRefFloat_26a1c0(arg0++, (*(Vec3 *)(rgp_blk2 + 0x0)).x);
    ScriptSetRefFloat_26a1c0(arg0++, (*(Vec3 *)(rgp_blk2 + 0x0)).y);
    ScriptSetRefFloat_26a1c0(arg0++, (*(Vec3 *)(rgp_blk2 + 0x0)).z);
    if (arg1 >= 9) {
        ScriptSetRefFloat_26a1c0(arg0++, Sinf_128fd0((*(Vec3 *)(rgp_blk2 + 0x0)).y));
        ScriptSetRefFloat_26a1c0(arg0++, 0.0f);
        ScriptSetRefFloat_26a1c0(arg0, Cosf_128d30((*(Vec3 *)(rgp_blk2 + 0x0)).y));
    }
    return 1;
}
