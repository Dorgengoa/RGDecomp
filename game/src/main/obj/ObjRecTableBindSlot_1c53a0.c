/* rgp:protos */
#define RGP_SELF_ObjRecTableBindSlot_1c53a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_0047E270;

s32 ObjRecTableBindSlot_1c53a0(struct { u8 pad[0x434C]; s32 x; } *arg0, s32 arg1, s32 arg2, void *arg3) {
    s32 temp_2;
    if (arg1 < 0) {
        arg1 = ObjRecTableFindFree_1c5320((void *)arg0);
        if (arg1 < 0) {
            return -1;
        }
    }
    temp_2 = ((s32)ObjRecTableGet_1c3fa0(arg0, arg1));
    if (temp_2 == 0) {
        return -1;
    }
    if (arg3 == NULL) {
        arg3 = &D_0047E270;
    }
    if (arg0->x < 0) {
        arg0->x = arg1;
    }
    if (!(ObjRecBind_1c46c0(temp_2, arg2, arg3, 0) >= 0)) {
        return -1;
    }
    return arg1;
    return -1;
}
