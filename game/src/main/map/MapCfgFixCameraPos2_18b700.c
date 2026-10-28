/* rgp:protos */
#define RGP_SELF_MapCfgFixCameraPos2_18b700 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_00481250;
extern s32 D_004812CC;

typedef struct { u8 b[8]; } E8;
s32 MapCfgFixCameraPos2_18b700(E8 *arg0)
{
    s32 *tbl;
    s32 slot;
    s32 count;
    s32 next;

    if (MapCfgIsCameraSkipped_18cb00() != 0) {
        return 1;
    }
    tbl = ((s32 *)FixCameraRecGet_189710(D_00481250, D_004812CC));
    if (tbl == NULL) {
        return 0;
    }
    slot = VariantGetInt_15f780((s32) arg0++);
    if (slot < 0 || slot >= 8) {
        return 0;
    }
    VariantReadVec3_15f6c0((u8 *)tbl + (slot * 0x10) + 0x10, (s32) arg0);
    count = *tbl;
    next = slot + 1;
    count = (next < count) ? count : next;
    *tbl = count;
    return 1;
}
