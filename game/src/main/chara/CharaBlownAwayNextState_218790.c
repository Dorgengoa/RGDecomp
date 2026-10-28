/* rgp:protos */
#define RGP_SELF_CharaBlownAwayNextState_218790 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x3D8];
    s32 unk3D8;
    u8 pad3DC[0xA34 - 0x3DC];
    s16 unkA34;
} Obj218;

/*rgp*/
/*rgp*/

s32 CharaBlownAwayNextState_218790(Obj218 *arg0) {
    switch (arg0->unkA34) {
    case 0:
    case 2:
    case 3:
        break;
    case 1:
        if (((unsigned char)CharaIsHeadUnderwaterMaybe_238250((void *)arg0)) != 0) {
            return 2;
        }
        if (CharaHasLandedMaybe_20fdb0(arg0) != 0) {
            return 2;
        }
        if (arg0->unk3D8 & 0x10) {
            return 2;
        }
        break;
    default:
        return 0;
    }
    return arg0->unkA34;
}
