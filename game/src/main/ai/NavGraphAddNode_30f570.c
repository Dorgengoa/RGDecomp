/* rgp:protos */
#define RGP_SELF_NavGraphAddNode_30f570 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E24 { u8 pad[0x24]; } E24;
typedef struct Vec3 { f32 x, y, z; } Vec3;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

u32 NavGraphAddNode_30f570(u8 *arg0, s32 arg1, f32 f)
{
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x0 + sizeof(Vec3)]; char m1[0x10]; })];
    s32 t;
    u32 n;
    u32 c;

    if (((unsigned char)NavGraphIsValid_311140((int)arg0)) == 0) return -1;
    if (((unsigned short)NavGraphGetMaxNodes_310ca0(arg0)) <= ((unsigned short)NavGraphGetNodeCount_310cb0(arg0))) return -1;
    if (!(f <= 0.0f)) {
        t = NavFindNearestNode_310820(arg0, arg1, 0);
        if (t != 0 && NavNodeDistSq_3118d0(t, arg1) <= f * f) return -1;
    }
    NavXformPointToLocal_310d50(arg0, &(*(Vec3 *)(rgp_blk1 + 0x0)), arg1);
    n = ((unsigned short)NavGraphGetNodeCount_310cb0(arg0));
    NavNodeInit_3119d0((s32)((E24 *)NavGraphGetNodes_310cc0(arg0) + n), n, 0, (*(Vec3 *)(rgp_blk1 + 0x0)).x, (*(Vec3 *)(rgp_blk1 + 0x0)).y, (*(Vec3 *)(rgp_blk1 + 0x0)).z);
    c = *(u16 *)(arg0 + 0xA8) + 1;
    if (*(s32 *)(arg0 + 0xA0) != 0 && c <= *(u16 *)(arg0 + 0xAA)) *(u16 *)(arg0 + 0xA8) = c;
    return n;
}
