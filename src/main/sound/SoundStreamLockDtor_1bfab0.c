#include "types.h"

extern s32 SignalSema(s32);
extern void OperatorDelete_100840(void *);

struct Sub_FUN_001bfab0 {
    u8 pad000[0x7C];
    s32 m7C;
    u8 m80;
};

struct Obj_FUN_001bfab0 {
    struct Sub_FUN_001bfab0 *m00;
};

void *SoundStreamLockDtor_1bfab0(struct Obj_FUN_001bfab0 *o, s16 flag)
{
    struct Sub_FUN_001bfab0 *s;

    if (o != 0) {
        s = o->m00;
        if (s != 0) {
            if (s->m80 != 0) {
                if (s->m7C > 0) {
                    SignalSema(*(volatile s32 *)&s->m7C);
                }
            }
            s->m80 = 0;
        }
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
