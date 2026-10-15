#include "types.h"
typedef struct {u8 x[0x14];} E14;


s32 NavGraphFindEdge_3106e0(u8 *, s32, s32);
u32 NavGraphGetMaxEdges_310bf0(u8 *);
u32 NavGraphGetEdgeCount_310c00(u8 *);
s32 NavGraphGetEdges_310c10(u8 *);
s32 NavGraphIsValid_311140(void);
u32 NavEdgeGetId_311720(s32);
void NavEdgeInit_311730(s32, s64, s32, s32, s32);

u32 NavGraphAddEdge_30f450(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_2;
    u32 temp_3;
    u32 temp_16_2;
    u32 temp_16;

    if (NavGraphIsValid_311140() == 0) {
        return -1;
    }
    temp_16_2 = NavGraphGetMaxEdges_310bf0(arg0);
    if (temp_16_2 <= NavGraphGetEdgeCount_310c00(arg0)) {
        return -1;
    }
    if (arg3 != 0) {
        temp_2 = NavGraphFindEdge_3106e0(arg0, arg1, arg2);
        if (temp_2 != 0) {
            return NavEdgeGetId_311720(temp_2);
        }
    }
    temp_16 = NavGraphGetEdgeCount_310c00(arg0);
    NavEdgeInit_311730((s32)((E14*)NavGraphGetEdges_310c10(arg0)+temp_16), (s16)temp_16, arg1, arg2, 0);
    temp_3 = *(u16 *)(arg0 + 0xB8) + 1;
    if ((*(s32 *)(arg0 + 0xB0) != 0) && (temp_3 <= *(u16 *)(arg0 + 0xBA))) {
        *(u16 *)(arg0 + 0xB8) = temp_3;
    }
    return temp_16;
}
