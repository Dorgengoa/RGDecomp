/* rgp:protos */
#define RGP_SELF_CharaCmdSpeed_22c7f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Stack locals are allocated in REVERSE declaration order, so the buffer that
   lands at sp+0x40 is declared LAST. */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

struct Obj0 {
    s32 m00;
};

struct Buf10 {
    u8 b[0x10];
};

struct Buf20 {
    u8 b[0x20];
};

s32 CharaCmdSpeed_22c7f0(struct Obj0 *p0, s32 p1, s32 argc)
{
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x0 + sizeof(struct Buf10)]; char m1[0x10 + sizeof(struct Buf10)]; char m2[0x20 + sizeof(struct Buf20)]; char m3[0x40]; char m4[0x10]; char m5[0x20]; char m6[0x30]; })]; typedef char rgp_blk1_chk0[(0x0) + sizeof(struct Buf10) <= (0x10) && (0x0) >= 0 ? 1 : -1]; typedef char rgp_blk1_chk1[(0x10) + sizeof(struct Buf10) <= (0x20) && (0x10) >= 0 ? 1 : -1];
    
    
    struct Buf10 sp40 __attribute__((aligned(16)));
    s32 r0;
    s32 o;
    f32 x;
    f32 y;
    f32 z;

    if (argc != 3) {
        return 1;
    }
    r0 = ((s32)GetActionMgr_1fdb50());
    o = ((s32)ActionMgrFindById_233b50(r0, p0->m00));
    if (o == 0) {
        return 1;
    }
    CharaGetSrtMatrix_2388c0(o, &(*(struct Buf10 *)(rgp_blk1 + 0x0)));
    x = ScriptArgGetFloat_302cf0(p1);
    y = ScriptArgGetFloat_302cf0(p1 + 5);
    z = ScriptArgGetFloat_302cf0(p1 + 0xA);
    VecWeightedSum3_1cb860(&sp40, &(*(struct Buf10 *)(rgp_blk1 + 0x0)), &(*(struct Buf10 *)(rgp_blk1 + 0x10)), &(*(struct Buf20 *)(rgp_blk1 + 0x20)), x, y, z);
    CharaSetVelocityFromVec_238790(o, &sp40);
    return 1;
}
