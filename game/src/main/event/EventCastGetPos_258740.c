/* rgp:protos */
#define RGP_SELF_EventCastGetPos_258740 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

typedef struct {
    s32 type;
    u8 pad4[8];
    u8 *obj;
} Slot;

/*rgp*/
/*rgp*/
/*rgp*/

s32 EventCastGetPos_258740(Slot *arg0, s32 arg1, u128 *arg2)
{
    Slot *s;
    u8 *p;

    if (arg1 < 0 || arg1 >= 0x20) {
        return 0;
    }
    s = &arg0[arg1];
    switch (s->type) {
    case 0:
        p = s->obj;
        if (p == NULL) {
            return 0;
        }
        *arg2 = *(u128 *)(p + 0x180);
        return 1;
    case 1:
        p = s->obj;
        if (p == NULL) {
            return 0;
        }
        NodeGetTranslation_186650(p, arg2);
        return 1;
    case 2:
        p = s->obj;
        if (p == NULL) {
            return 0;
        }
        MenuWinGetPos_26c2b0(p, arg2);
        return 1;
    case 3:
        p = s->obj;
        if (p == NULL) {
            return 0;
        }
        ModelFrameGetPos_14a220(p, arg2);
        return 1;
    case 4:
        p = s->obj;
        if (p == NULL) {
            return 0;
        }
        NodeGetTranslation_186650(p, arg2);
        return 1;
    }
    return 0;
}
