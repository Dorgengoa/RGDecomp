/* rgp:protos */
#define RGP_SELF_NavGraphAddEdge_30f450 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct {u8 x[0x14];} E14;


/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

u32 NavGraphAddEdge_30f450(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_2;
    u32 temp_3;
    u32 temp_16_2;
    u32 temp_16;

    if (((unsigned char)NavGraphIsValid_311140((int)arg0)) == 0) {
        return -1;
    }
    temp_16_2 = ((unsigned short)NavGraphGetMaxEdges_310bf0(arg0));
    if (temp_16_2 <= ((unsigned short)NavGraphGetEdgeCount_310c00(arg0))) {
        return -1;
    }
    if (arg3 != 0) {
        temp_2 = NavGraphFindEdge_3106e0(arg0, arg1, arg2);
        if (temp_2 != 0) {
            return ((short)NavEdgeGetId_311720(temp_2));
        }
    }
    temp_16 = ((unsigned short)NavGraphGetEdgeCount_310c00(arg0));
    NavEdgeInit_311730((s32)((E14*)NavGraphGetEdges_310c10(arg0)+temp_16), (int)((s16)temp_16), arg1, arg2, 0);
    temp_3 = *(u16 *)(arg0 + 0xB8) + 1;
    if ((*(s32 *)(arg0 + 0xB0) != 0) && (temp_3 <= *(u16 *)(arg0 + 0xBA))) {
        *(u16 *)(arg0 + 0xB8) = temp_3;
    }
    return temp_16;
}
