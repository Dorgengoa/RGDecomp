/* rgp:protos */
#define RGP_SELF_EvCmdSoundSlotLoad_2624b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 a;
    s32 b;
} Cur;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_00481F78;
typedef struct {
    s32 t[13];
    s32 last;
} Tbl;
extern Tbl D_004BD9E8;

s32 EvCmdSoundSlotLoad_2624b0(Cur *arg0, s32 arg1)
{
    u8 sp40[0x80] __attribute__((aligned(16)));
    s32 n;
    s32 h;
    void *p;
    s32 r;

    switch (arg1) {
    case 2:
        n = 4;
        break;
    case 3:
        n = ScriptGetInt_26a2a0(arg0++);
        break;
    default:
        return 0;
    }
    h = GameSceneSoundSlotFindByBank_1d0d70(D_00481F78, n);
    if (h == 0) {
        return 0;
    }
    switch (arg0->a) {
    case 0:
        if (!(GameSceneGetEventSoundPath_1d14f0(D_00481F78, sp40, ScriptGetInt_26a2a0(arg0++)) & 0xFF)) {
            return 0;
        }
        p = sp40;
        break;
    case 2:
        p = ScriptGetCodeAddr_26a200(arg0++);
        break;
    default:
        return 0;
    }
    if (n < 0 || n > 12) {
        return 0;
    }
    r = FileLoadCached_26a6c0(p, 0);
    if (r == 0) {
        return 0;
    }
    h = SoundSlotStartFromData_1d1e80(h, r);
    ScriptSetRefInt_26a1e0(arg0, h);
    D_004BD9E8.t[n] = h;
    D_004BD9E8.last = h;
    return 1;
}
