/* rgp:protos */
#define RGP_SELF_EvCmdSoundSlotLoad_248050 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct T_00248050 { u8 b[8]; } T_00248050;

typedef struct Obj0_00248050 { s32 m00; } Obj0_00248050;

extern Obj0_00248050 *gEventContext;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdSoundSlotLoad_248050(T_00248050 *q, s32 kind)
{
    u8 buf[0x80] __attribute__((aligned(16)));
    s32 a;
    s32 b;
    s32 c;
    void *obj;
    void *r;
    if (kind == 3) goto g0;
    return 0;
g0:
    a = ScriptGetInt_2490f0(q++);
    b = ScriptGetInt_2490f0(q++);
    c = ScriptGetInt_2490f0(q);
    GameSceneSoundEnvApplyPreset_1d0e30(gEventContext->m00, b, 0, 0);
    if (GameSceneGetEventSoundPath_1d14f0(gEventContext->m00, buf, b) != 0) goto g1;
    return 0;
g1:
    if (a < 0) goto zero;
    if (a <= 12) goto g2;
zero:
    return 0;
g2:
    obj = FileLoadCached_26a6c0(buf, 0);
    if (obj == 0) return 0;
    r = GameSceneSoundSlotFindByBank_1d0d70(gEventContext->m00, a);
    if (r == 0) return 0;
    EventSoundBankHandleSet_24fca0(SoundSlotStartFromData_1d1e80(r, obj), c);
    return 1;
}
