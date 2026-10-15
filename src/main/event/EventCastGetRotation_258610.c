#include "types.h"
#include "vec.h"

typedef struct {
    s32 type;
    u8 pad4[8];
    u8 *obj;
} Slot;

typedef struct {
    s32 a;
    s32 b;
    f32 c;
    s32 d;
} Out;

extern void FrameGetRot_14a1f0(void *, Out *);
extern void NodeGetRotation_1865e0(void *, Out *);
extern f32 MenuWinGetRotZ_26c230(void *);

s32 EventCastGetRotation_258610(Slot *arg0, s32 arg1, Out *arg2)
{
    Slot *s;
    u8 *p;
    u8 **pp;

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
        *(u128 *)arg2 = *(u128 *)(p + 0x190);
        return 1;
    case 1:
        p = s->obj;
        if (p == NULL) {
            return 0;
        }
        NodeGetRotation_1865e0(p, arg2);
        return 1;
    case 3:
        p = s->obj;
        if (p == NULL) {
            return 0;
        }
        FrameGetRot_14a1f0(p, arg2);
        return 1;
    case 2:
        pp = &s->obj;
        if (*pp == NULL) {
            return 0;
        }
        arg2->a = 0;
        arg2->b = 0;
        arg2->d = 0;
        arg2->c = MenuWinGetRotZ_26c230(*pp);
        return 1;
    case 4:
        p = s->obj;
        if (p == NULL) {
            return 0;
        }
        NodeGetRotation_1865e0(p, arg2);
        return 1;
    }
    return 0;
}
