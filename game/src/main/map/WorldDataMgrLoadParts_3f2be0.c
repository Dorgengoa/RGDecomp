/* rgp:protos */
#define RGP_SELF_WorldDataMgrLoadParts_3f2be0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj Obj;
typedef struct Sub { u8 pad[0x2C]; s32 a; u8 pad2[4]; s32 b; } Sub;
struct Obj {
    u8 pad0[4];
    Sub *sub;
    u8 pad8[0x2C];
    void *part[21];
    u8 pad88[0x24];
    s32 diff;
};

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_004B2570[0x400];

s32 WorldDataMgrLoadParts_3f2be0(Obj *obj, s32 arg1, s32 arg2, s32 flag) {
    s32 before;
    Sub *s;

    if (arg1 == 0) return 0;
    s = obj->sub;
    if (s == 0) return 0;
    before = s->b - s->a;
    if (obj->part[0] != 0) {
        WorldSubsysLoad_411db0(obj->part[0], arg1, arg2, obj);
        if (flag != 0) PadWaitReady_1849e0(D_004B2570);
    }
    if (obj->part[1] != 0) {
        WorldSubsysLoad_405480(obj->part[1], arg1, arg2, obj);
        if (flag != 0) PadWaitReady_1849e0(D_004B2570);
    }
    if (obj->part[2] != 0) {
        WorldSubsysLoad_428560(obj->part[2], arg1, arg2, obj);
        if (flag != 0) PadWaitReady_1849e0(D_004B2570);
    }
    if (obj->part[3] != 0) {
        WorldSubsysLoad_40c560(obj->part[3], arg1, arg2, obj);
        if (flag != 0) PadWaitReady_1849e0(D_004B2570);
    }
    if (obj->part[4] != 0) {
        WorldSubsysLoad_3f43b0(obj->part[4], arg1, arg2, obj);
        if (flag != 0) PadWaitReady_1849e0(D_004B2570);
    }
    if (obj->part[5] != 0) {
        WorldSubsysLoad_3f9ec0(obj->part[5], arg1, arg2, obj);
        if (flag != 0) PadWaitReady_1849e0(D_004B2570);
    }
    if (obj->part[6] != 0) {
        WorldSubsysLoad_3fc320(obj->part[6], arg1, arg2, obj);
        if (flag != 0) PadWaitReady_1849e0(D_004B2570);
    }
    if (obj->part[7] != 0) {
        WorldSubsysLoad_3f7fb0(obj->part[7], arg1, arg2, obj);
        if (flag != 0) PadWaitReady_1849e0(D_004B2570);
    }
    if (obj->part[8] != 0) {
        WorldSubsysLoad_3f9310(obj->part[8], arg1, arg2, obj);
        if (flag != 0) PadWaitReady_1849e0(D_004B2570);
    }
    if (obj->part[9] != 0) {
        WorldSubsysLoad_3fe2e0(obj->part[9], arg1, arg2, obj);
        if (flag != 0) PadWaitReady_1849e0(D_004B2570);
    }
    if (obj->part[10] != 0) {
        WorldSubsysLoad_429410(obj->part[10], arg1, arg2, obj);
        if (flag != 0) PadWaitReady_1849e0(D_004B2570);
    }
    if (obj->part[11] != 0) {
        WorldSubsysLoad_4004a0(obj->part[11], arg1, arg2, obj);
        if (flag != 0) PadWaitReady_1849e0(D_004B2570);
    }
    if (obj->part[12] != 0) {
        WorldSubsysLoad_419a10(obj->part[12], arg1, arg2, obj);
        if (flag != 0) PadWaitReady_1849e0(D_004B2570);
    }
    if (obj->part[13] != 0) {
        WorldSubsysLoad_40a4c0(obj->part[13], arg1, arg2, obj);
        if (flag != 0) PadWaitReady_1849e0(D_004B2570);
    }
    if (obj->part[14] != 0) {
        WorldSubsysLoad_41c620(obj->part[14], arg1, arg2, obj);
        if (flag != 0) PadWaitReady_1849e0(D_004B2570);
    }
    if (obj->part[15] != 0) {
        WorldSubsysLoad_402590(obj->part[15], arg1, arg2, obj);
        if (flag != 0) PadWaitReady_1849e0(D_004B2570);
    }
    if (obj->part[16] != 0) {
        WorldSubsysLoad_425950(obj->part[16], arg1, arg2, obj);
        if (flag != 0) PadWaitReady_1849e0(D_004B2570);
    }
    if (obj->part[17] != 0) {
        WorldSubsysLoad_427130(obj->part[17], arg1, arg2, obj);
        if (flag != 0) PadWaitReady_1849e0(D_004B2570);
    }
    if (obj->part[18] != 0) {
        WorldSubsysLoad_41ff30(obj->part[18], arg1, arg2, obj);
        if (flag != 0) PadWaitReady_1849e0(D_004B2570);
    }
    if (obj->part[19] != 0) {
        WorldSubsysLoad_41e550(obj->part[19], arg1, arg2, obj);
        if (flag != 0) PadWaitReady_1849e0(D_004B2570);
    }
    if (obj->part[20] != 0) {
        WorldSubsysLoad_40eef0(obj->part[20], arg1, arg2, obj);
        if (flag != 0) PadWaitReady_1849e0(D_004B2570);
    }
    s = obj->sub;
    obj->diff = before - (s->b - s->a);
    return 1;
}
