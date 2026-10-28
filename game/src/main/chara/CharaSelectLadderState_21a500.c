/* rgp:protos */
#define RGP_SELF_CharaSelectLadderState_21a500 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj {
    u8 pad0[0x570];
    u64 m570;
    u8 pad578[0x854 - 0x578];
    s32 m854;
    s32 m858;
    u8 pad85C[0xA34 - 0x85C];
    s16 mA34;
    u8 padA36[0xA44 - 0xA36];
    s32 mA44;
    u8 padA48[0xAD0 - 0xA48];
    f32 mAD0;
    f32 mAD4;
} Obj;

/*rgp*/
/*rgp*/

s32 CharaSelectLadderState_21a500(Obj *p)
{
    u64 flags;
    s32 st;
    s32 r;

    flags = p->m570;
    if (flags & 0x4000) {
        switch (p->mA34) {
        case 1:
        case 0:
            break;
        default:
            return 0x65;
        }
    }
    st = p->mA34;
    switch (st) {
    case 0xC8:
        if (p->mA44 & 0x1000000) {
            if (p->m854 == 0) {
                if (!(flags & 0x20)) {
                    goto neg;
                }
                return 0;
            }
            if (flags & 0x40) {
                return 1;
            }
            goto neg;
        }
        return p->m854 != 0;
    neg:
        return -1;
    case 0:
        r = (p->mAD0 >= 30.0f) ? 0x28 : st;
        return r;
    case 1:
        r = (p->mAD0 >= 30.0f) ? 0x2C : st;
        return r;
    case 0x2B:
    case 0x2F:
        return st;
    case 0x28:
    case 0x29:
    case 0x2A:
    case 0x2C:
    case 0x2D:
    case 0x2E:
        if (((unsigned char)CharaPlayedMotionIsCurrent_2124c0(p)) == 0 || CharaGetMotionFrame_238570(p) < 1.0f) {
            return p->mA34;
        }
        p->mA34 += 10;
        *(s32 *)&p->mAD0 = 0;
        *(s32 *)&p->mAD4 = 0;
        break;
    }
    st = p->mA34;
    switch (st) {
    case 0x32:
    case 0x33:
    case 0x34:
    case 0x36:
    case 0x37:
    case 0x38:
        flags = p->m570;
        if (flags & 0x20) {
            if (p->m854 == p->m858 - 6) {
                return 0x2B;
            }
            switch (st) {
            case 0x32:
            case 0x34:
            case 0x38:
                return 0x29;
            case 0x33:
            case 0x37:
                return 0x2A;
            }
        }
        if (flags & 0x40) {
            if (p->m854 == 1) {
                return 0x2F;
            }
            switch (st) {
            case 0x36:
            case 0x34:
            case 0x38:
                return 0x2D;
            case 0x33:
            case 0x37:
                return 0x2E;
            }
        }
        return st;
    default:
        return -1;
    }
}
