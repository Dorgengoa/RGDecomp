#include "types.h"
#include "event_vm.h"


extern void ScriptGetCodeAddr_249050(void);
extern s32 ScriptGetInt_2490f0(s32);
extern void Vec4VectorPushBack_249120(EventPlayer *, s32 *);

s32 EvCmdCueMesLabel_245970(s64 *arg0)
{
    s32 sp3x[3];
    EventPlayer *player;

    arg0++;
    player = gEventContext->player;
    sp3x[0] = 0;
    ScriptGetCodeAddr_249050();
    sp3x[2] = ScriptGetInt_2490f0((s32)arg0++);
    sp3x[1] = ScriptGetInt_2490f0((s32)arg0);
    Vec4VectorPushBack_249120(player, sp3x);
    return 1;
}
