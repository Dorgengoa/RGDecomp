/* rgp:protos */
#define RGP_SELF_RecordSetStateClamped_430db0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S430db0 {
    s32 w0;
    s32 w4;
    s32 w8;
    u8 padC[0xC];
    s32 w18;
} S430db0;

typedef struct O430db0 {
    u8 pad0[0x1188];
    S430db0 *p1188;
} O430db0;

/*rgp*/

s32 RecordSetStateClamped_430db0(O430db0 *o, s32 v, s32 unused)
{
    S430db0 *p;
    s32 old;

    p = o->p1188;
    old = p->w8;
    p->w8 = v;
    if (v != old) {
        o->p1188->w18 = old;
        switch (o->p1188->w4) {
    case 0x0:
        if (v < 0x0) {
            RecordSetStateClamped_430db0(o, 0x0, old);
        } else if (v > 0x0) {
            RecordSetStateClamped_430db0(o, 0x0, old);
        }
        RecordSetSubState_430bd0(o, 0);
        break;
    case 0xA:
        if (v < 0x64) {
            RecordSetStateClamped_430db0(o, 0x64, old);
        } else if (v > 0x66) {
            RecordSetStateClamped_430db0(o, 0x66, old);
        }
        RecordSetSubState_430bd0(o, 0);
        break;
    case 0x14:
        if (v < 0xC8) {
            RecordSetStateClamped_430db0(o, 0xC8, old);
        } else if (v > 0xCB) {
            RecordSetStateClamped_430db0(o, 0xCB, old);
        }
        RecordSetSubState_430bd0(o, 0);
        break;
    case 0x1E:
        if (v < 0x12C) {
            RecordSetStateClamped_430db0(o, 0x12C, old);
        } else if (v > 0x133) {
            RecordSetStateClamped_430db0(o, 0x133, old);
        }
        RecordSetSubState_430bd0(o, 0);
        break;
    case 0x28:
        if (v < 0x190) {
            RecordSetStateClamped_430db0(o, 0x190, old);
        } else if (v > 0x196) {
            RecordSetStateClamped_430db0(o, 0x196, old);
        }
        RecordSetSubState_430bd0(o, 0);
        break;
    case 0x32:
        if (v < 0x1F4) {
            RecordSetStateClamped_430db0(o, 0x1F4, old);
        } else if (v > 0x1FA) {
            RecordSetStateClamped_430db0(o, 0x1FA, old);
        }
        RecordSetSubState_430bd0(o, 0);
        break;
    case 0x3C:
        if (v < 0x258) {
            RecordSetStateClamped_430db0(o, 0x258, old);
        } else if (v > 0x25F) {
            RecordSetStateClamped_430db0(o, 0x25F, old);
        }
        RecordSetSubState_430bd0(o, 0);
        break;
    case 0x3D:
        if (v < 0x262) {
            RecordSetStateClamped_430db0(o, 0x262, old);
        } else if (v > 0x26A) {
            RecordSetStateClamped_430db0(o, 0x26A, old);
        }
        RecordSetSubState_430bd0(o, 0);
        break;
    case 0x3E:
        if (v < 0x26C) {
            RecordSetStateClamped_430db0(o, 0x26C, old);
        } else if (v > 0x270) {
            RecordSetStateClamped_430db0(o, 0x270, old);
        }
        RecordSetSubState_430bd0(o, 0);
        break;
    case 0x3F:
        if (v < 0x276) {
            RecordSetStateClamped_430db0(o, 0x276, old);
        } else if (v > 0x27B) {
            RecordSetStateClamped_430db0(o, 0x27B, old);
        }
        RecordSetSubState_430bd0(o, 0);
        break;
    case 0x46:
        if (v < 0x2BC) {
            RecordSetStateClamped_430db0(o, 0x2BC, old);
        } else if (v > 0x2BE) {
            RecordSetStateClamped_430db0(o, 0x2BE, old);
        }
        RecordSetSubState_430bd0(o, 0);
        break;
        }
    }
    return 1;
}
