#include "types.h"

extern void SemaHandleDelete_1c2150(void *);
extern void OperatorDelete_100840(void *);

void *SoundStreamSlotDtor_1bf6c0(void *o, s16 flag)
{
    void *p;

    if (o != 0) {
        p = (u8 *)o + 0xC;
        if (p != 0) {
            SemaHandleDelete_1c2150(p);
        }
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
