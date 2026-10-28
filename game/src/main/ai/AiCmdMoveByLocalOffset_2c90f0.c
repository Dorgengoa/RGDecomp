/* rgp:protos */
#define RGP_SELF_AiCmdMoveByLocalOffset_2c90f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Arg { s32 a; s32 b; } Arg;
typedef struct Vec { f32 x, y, z, w; } __attribute__((aligned(16))) Vec;
typedef struct Mtx { f32 m[4][4]; } __attribute__((aligned(16))) Mtx;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_004DB920[4];
extern s32 D_004DB928[4];
extern s32 D_004DB92C[4];

s32 AiCmdMoveByLocalOffset_2c90f0(Arg *p)
{
    Vec v __attribute__((aligned(16)));
    Vec b __attribute__((aligned(16)));
    Mtx m __attribute__((aligned(16)));
    Vec a __attribute__((aligned(16)));
    u8 *obj;

    if (D_004DB92C[0] == 0) {
        return 0;
    }
    v.x = ScriptSlotGetFloat_2cc9a0(p++);
    v.y = ScriptSlotGetFloat_2cc9a0(p++);
    v.z = ScriptSlotGetFloat_2cc9a0(p);
    v.w = 1.0f;
    obj = ((u8 *)ObjRecGetLiveObject_1c4a90(D_004DB920[0], D_004DB928[0]));
    if (obj == 0) {
        return 0;
    }
    CharaGetSrtMatrix_2388c0(D_004DB92C[0], &m);
    MatMulPoint_1cb8e0(&v, &m, &v);
    CharaGetPos_2388a0(D_004DB92C[0], &b);
    VecSub_13be40(&a, &v, &b);
    CharaSetReqMove_238710(D_004DB92C[0], &a);
    if (AiSeparateFromOthers_2cd2d0(D_004DB920[0], D_004DB928[0], &b) != 0) {
        v = *(Vec *)(obj + 0x180);
        CharaSetPosVec_2387a0(D_004DB92C[0], &v);
    }
    return 1;
}
