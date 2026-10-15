#include "types.h"

#pragma divbyzerocheck on

struct Obj0;
struct Obj0 {
    u8 pad000[0x1F0];
    s32 m1F0;
    u8 pad1F4[0x1448];
    f32 m163C;
};

typedef struct {
    u8 pad000[0x1F8];
    s32 f1F8;
} T_0018d7d0;

extern s32 TimeOfDayPhase_18d890(void);
extern f32 TimeOfDayGetHour_18d920(struct Obj0 *p0);

s32 TimeOfDaySlot_18d7d0(T_0018d7d0 *arg0)
{
    s32 count;
    f32 f0;
    f32 f2;
    s32 result;

    count = arg0->f1F8;
    if (count < 2)
        return 0;

    if (count == 4)
        return TimeOfDayPhase_18d890();

    f0 = TimeOfDayGetHour_18d920((struct Obj0 *)arg0);
    f2 = f0 - 9.0f;
    if (f2 < 0.0f)
        f2 += 24.0f;

    result = (s32)(f2 / (24.0f / (f32)count));
    return result % count;
}
