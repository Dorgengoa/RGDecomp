#include "types.h"

typedef struct Arg { s32 a; s32 b; } Arg;
typedef struct Vec { f32 x, y, z, w; } __attribute__((aligned(16))) Vec;
typedef struct Mtx { f32 m[4][4]; } __attribute__((aligned(16))) Mtx;

extern void VecSub_13be40(Vec *, Vec *, Vec *);
extern u8 *ObjRecGetLiveObject_1c4a90(s32, s32);
extern void MatMulPoint_1cb8e0(Vec *, Mtx *, Vec *);
extern void CharaSetReqMove_238710(s32, Vec *);
extern void CharaSetPosVec_2387a0(s32, Vec *);
extern void CharaGetPos_2388a0(s32, Vec *);
extern void CharaGetSrtMatrix_2388c0(s32, Mtx *);
extern f32 ScriptSlotGetFloat_2cc9a0(Arg *);
extern s32 AiSeparateFromOthers_2cd2d0(s32, s32, Vec *);
extern s32 D_004DB920[4];
extern s32 D_004DB928[4];
extern s32 D_004DB92C[4];

s32 AiCmdMoveByLocalOffset_2c90f0(Arg *p)
{
    Vec v;
    Vec b;
    Mtx m;
    Vec a;
    u8 *obj;

    if (D_004DB92C[0] == 0) {
        return 0;
    }
    v.x = ScriptSlotGetFloat_2cc9a0(p++);
    v.y = ScriptSlotGetFloat_2cc9a0(p++);
    v.z = ScriptSlotGetFloat_2cc9a0(p);
    v.w = 1.0f;
    obj = ObjRecGetLiveObject_1c4a90(D_004DB920[0], D_004DB928[0]);
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
