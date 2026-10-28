#include "types.h"

struct T252600 { u8 pad000[0x60]; s32 f60; };

extern "C" u8 D_004BDDB0[16];
extern "C" s32 EventCastMotionIsFinished_258340(void *, s32);

extern "C" u32 EvSubNodeWaitMotionEnd_252600(s32 a0, struct T252600 *b)
{
    bool t;

    t = !EventCastMotionIsFinished_258340(D_004BDDB0, b->f60);
    return (bool)(t);
}
