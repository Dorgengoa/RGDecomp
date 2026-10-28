/* rgp:protos */
#define RGP_SELF_RecordSetKind_431110 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S431110 {
    s32 w0;
    s32 w4;
    u8 pad8[0xC];
    s32 w14;
} S431110;

typedef struct O431110 {
    u8 pad0[0x1188];
    S431110 *p1188;
} O431110;

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

s32 RecordSetKind_431110(O431110 *arg0, s32 arg1)
{
    S431110 *p;
    s32 old;

    p = arg0->p1188;
    old = p->w4;
    p->w4 = arg1;
    if (arg1 != old) {
        arg0->p1188->w14 = old;
        switch (arg1) {
    case 0x0:
        RecordSetStateClamped_430db0(arg0, 0x0, old);
        break;
    case 0xA:
        RecordSetStateClamped_430db0(arg0, 0x64, old);
        ((void)(((s32)RecordGetPayloadIfKind0A_430bb0(arg0))), RecordPayloadInitKind0A_432490());
        break;
    case 0x14:
        RecordSetStateClamped_430db0(arg0, 0xC8, old);
        RecordPayloadInitKind14_432470(((s32)RecordGetPayloadIfKind14_430b90(arg0)));
        break;
    case 0x1E:
        RecordSetStateClamped_430db0(arg0, 0x12C, old);
        RecordPayloadInitKind1E_432370(((s32)RecordGetPayloadIfKind1E_430b70(arg0)));
        break;
    case 0x28:
        RecordSetStateClamped_430db0(arg0, 0x190, old);
        RecordPayloadInitKind28_432250(((s32)RecordGetPayloadIfKind28_430b50(arg0)));
        break;
    case 0x32:
        RecordSetStateClamped_430db0(arg0, 0x1F4, old);
        RecordPayloadInitKind32_432180(((s32)RecordGetPayloadIfKind32_430b30(arg0)));
        break;
    case 0x3C:
        RecordSetStateClamped_430db0(arg0, 0x258, old);
        RecordPayloadInitKind3C_4320a0(((s32)RecordGetPayloadIfKind3C_430b10(arg0)));
        break;
    case 0x3D:
        RecordSetStateClamped_430db0(arg0, 0x262, old);
        RecordPayloadInitKind3D_431f60(((s32)RecordGetPayloadIfKind3D_430af0(arg0)));
        break;
    case 0x3E:
        RecordSetStateClamped_430db0(arg0, 0x26C, old);
        RecordPayloadInitKind3E_431ed0(((s32)RecordGetPayloadIfKind3E_430ad0(arg0)));
        break;
    case 0x3F:
        RecordSetStateClamped_430db0(arg0, 0x276, old);
        RecordPayloadInitKind3F_431e20(((s32)RecordGetPayloadIfKind3F_430ab0(arg0)));
        break;
    case 0x46:
        RecordSetStateClamped_430db0(arg0, 0x2BC, old);
        break;
        }
    }
    return 1;
}
