/* rgp:protos */
#define RGP_SELF_InsectUiConfirmButtonSetSelectedMaybe_392b20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s16 x0;
    s16 x2;
    s16 x4;
    s16 x6;
    s16 x8;
    s16 xA;
    s16 xC;
    s16 xE;
    f32 x10;
    f32 x14;
    s16 x18;
    s16 x1A;
} T;

void InsectUiConfirmButtonSetSelectedMaybe_392b20(s32 arg0, u8 *arg1, s32 arg2) {
    T *t;
    f32 fz;
    if (arg1 == NULL) {
        return;
    }
    t = *(T **)(arg1 + 0x20);
    if (t == NULL) {
        return;
    }
    t->x2 = 0;
    t->x0 = 0;
    fz = t->x0;
    t->xC = 0x34;
    t->x4 = 0x34;
    t->xE = 0x1A;
    t->x6 = 0x1A;
    t->x1A = 0;
    t->x18 = 0;
    t->x10 = t->x14 = fz;
    if (arg2 != 0) {
        t->x8 = 0xCC;
        t->xA = 0x7A;
    } else {
        t->x8 = 0x98;
        t->xA = 0x7A;
    }
}
