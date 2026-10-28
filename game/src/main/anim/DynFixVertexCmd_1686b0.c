/* rgp:protos */
#define RGP_SELF_DynFixVertexCmd_1686b0 1
#include "port/game_protos.h"
#line 1
/* main s27m: CLOSED -- DynFixVertexBindFrame_168740 takes arg0 (retail never writes $a0); arg0 is the
   walker: `arg0 += 2` (0x10) then VariantGetFloat_15f740(arg0++) (s26 post-inc param lever). */
#include "types.h"

/*rgp*/
/*rgp*/

typedef struct { u8 b[8]; } E8_1686B0;
s32 DynFixVertexCmd_1686b0(E8_1686B0 *arg0, s32 arg1) {
    void *temp_2;

    temp_2 = DynFixVertexBindFrame_168740(arg0);
    arg0 += 2;
    if (temp_2 == NULL) {
        return 0;
    }
    if (arg1 >= 3) {
        *(f32 *)((u8 *)temp_2 + 0x14) = VariantGetFloat_15f740(arg0++);
    }
    if (arg1 >= 4) {
        *(f32 *)((u8 *)temp_2 + 0x1C) = VariantGetFloat_15f740(arg0);
    }
    *(s32 *)((u8 *)temp_2 + 0x18) = 0;
    return 1;
}
