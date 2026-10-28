/* rgp:protos */
#define RGP_SELF_MapCfgFixCameraOffGroup_18b620 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct E8 { u8 b[8]; };
struct Obj0 { s8 m00; };
struct Obj1 { s32 m00; s32 m04; };

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_00481250;
extern s32 D_004812CC;

s32 MapCfgFixCameraOffGroup_18b620(struct E8 *p0)
{
    struct E8 *q;
    s32 r0;
    s32 r1;
    s32 r2;
    struct Obj1 *r3;
    struct Obj0 *r4;

    q = p0;
    r0 = MapCfgIsCameraSkipped_18cb00();
    if (r0 != 0) {
        return 1;
    }
    r1 = VariantGetInt_15f780(q++);
    r2 = ((s32)FixCameraRecGet_189710(D_00481250, D_004812CC));
    if (r2 == 0) {
        return 0;
    }
    r3 = ((struct Obj1 *)FixCameraGetOffGroupSlot_193820(r2, r1));
    if (r3 == 0) {
        return 0;
    }
    r4 = ((struct Obj0 *)SlotGetInt_15f720(q++));
    if (r4 == 0) {
        return 0;
    }
    if (r4->m00 != 0) {
        goto pay;
    }
    return 1;
pay:
    r3->m04 = VariantGetInt_15f780(q);
    r3->m00 = MapPartsGroupFind_189b70(D_00481250, r4);
    return 1;
}
