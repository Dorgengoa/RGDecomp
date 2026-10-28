/* rgp:protos */
#define RGP_SELF_ActionPacketInitTendencyMaybe_3e2c00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Same family as ActionPacketInitEventTimer_3e2a30/ActionPacketInitAreaTriggerMaybe_3e36b0/ActionPacketInitLoading_3e3a90 etc. in this
   directory -- a constructor that zeroes the object via ActionPacketClear_3e3e90 then
   fills in a handful of fields.  This one additionally dispatches on
   `type` through two DENSE 0..12 switches (mwcc emits a bounds check plus
   a jump table for each): the first groups {1,5,9}/{2,6,10}/{3,7,11}/
   {4,8,12} and sets m02/m03/m00; the second groups {1-4}/{5-8}/{9-12} and
   sets m10.  `type==0` or `type>=13` falls to each switch's default. */

extern s32 D_00483994;

struct Obj0;

struct Obj0 {
    s16 m00;
    u8 m02;
    u8 m03;
    u8 pad004[0x8];
    void *m0C;
    s32 m10;
    f32 m14;
};

struct Obj0 *ActionPacketInitTendencyMaybe_3e2c00(struct Obj0 *p0, void *p1, s32 type, s32 flag, f32 p4)
{
    s32 t0;
    s32 r0;

    t0 = D_00483994;
    if (t0 == 0) {
        return (struct Obj0 *)0;
    }
    r0 = ((s32)ActionPacketClear_3e3e90(p0));

    switch (type) {
    case 2: case 6: case 10:
        p0->m02 = 0xD;
        if (flag == 0) {
            p0->m03 = 0x40;
        } else {
            p0->m03 = 0x3F;
        }
        p0->m00 = 2;
        break;
    case 1: case 5: case 9:
        p0->m02 = 0xC;
        p0->m00 = 1;
        break;
    case 3: case 7: case 11:
        p0->m02 = 0xF;
        p0->m00 = 1;
        break;
    case 4: case 8: case 12:
        p0->m02 = 0x10;
        p0->m00 = 1;
        break;
    default:
        p0->m02 = 0xFF;
        p0->m00 = 0;
        break;
    }

    if (p0->m00 <= 0) {
        return (struct Obj0 *)0;
    }

    switch (type) {
    case 1: case 2: case 3: case 4:
        p0->m10 = 1;
        break;
    case 5: case 6: case 7: case 8:
        p0->m10 = 2;
        break;
    case 9: case 10: case 11: case 12:
        p0->m10 = 3;
        break;
    default:
        p0->m10 = 0xA;
        break;
    }

    p0->m14 = p4;
    p0->m0C = p1;
    return p0;
}
