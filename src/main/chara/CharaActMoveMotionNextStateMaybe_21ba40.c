#include "types.h"

typedef struct {
    u8 pad0[0x80];
    u8 x80[0x410];
    u8 x490[0x5A4];
    s16 state;
    u8 padA36[0x9A];
    f32 t;
} Obj;

extern s32 CharaCanGrabLedge_20fc40(Obj *);
extern s32 CharaHasLandedMaybe_20fdb0(Obj *);
extern void VecCopy_1cbe30(void *, void *);

s16 CharaActMoveMotionNextStateMaybe_21ba40(Obj *p)
{
    switch (p->state) {
    case 0xC8:
        return 0;
    case 0xC9:
        return 1;
    case 0xCA:
        return 1;
    case 0xCB:
        if (CharaHasLandedMaybe_20fdb0(p) != 0) {
            return 4;
        }
        return 2;
    case 0x65:
        return 4;
    case 6:
        if (p->t <= 15.0f) {
            break;
        }
    case 1:
    case 2:
        if (CharaCanGrabLedge_20fc40(p) != 0 && !(p->t < 0.0f)) {
            return 0x64;
        }
        if (CharaHasLandedMaybe_20fdb0(p) != 0) {
            return 4;
        }
        break;
    case 5:
        if (p->t < 3.0f) {
            break;
        }
        VecCopy_1cbe30(p->x80, p->x490);
        return 6;
    }
    return p->state;
}
