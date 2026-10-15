#include "types.h"

typedef struct { u8 pad[0x80]; s16 f80; } T_001d6dc0;

extern void StreamChanSetVolume_1d7010(T_001d6dc0 *, f32);
extern void StreamChanSetOpenReq_1d71a0(T_001d6dc0 *, s32);
extern void StreamChanSetResumeReq_1d7170(T_001d6dc0 *, s32);
extern void StreamChanSetPauseReq_1d7140(T_001d6dc0 *, s32);
extern void StreamChanSetStopReq_1d7110(T_001d6dc0 *, s32);
extern void StreamChanUpdate_1d72d0(T_001d6dc0 *, f32);
extern void SoundStreamSlotFree_1bd3a0(s32);
extern void StreamChanInit_1d7610(T_001d6dc0 *);

void StreamChanClose_1d6dc0(T_001d6dc0 *p)
{
    if (p->f80 >= 0) {
        StreamChanSetVolume_1d7010(p, 0.0f);
        StreamChanSetOpenReq_1d71a0(p, 0);
        StreamChanSetResumeReq_1d7170(p, 0);
        StreamChanSetPauseReq_1d7140(p, 1);
        StreamChanSetStopReq_1d7110(p, 1);
        StreamChanUpdate_1d72d0(p, 0.0f);
        SoundStreamSlotFree_1bd3a0(p->f80);
    }
    StreamChanInit_1d7610(p);
}
