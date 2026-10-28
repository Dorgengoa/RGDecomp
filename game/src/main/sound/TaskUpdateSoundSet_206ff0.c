/* rgp:protos */
#define RGP_SELF_TaskUpdateSoundSet_206ff0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj1 { u8 pad000[0x4]; s16 m04; u8 pad006[0x2A]; s16 m30; };
struct Obj0 { u8 pad000[0x18]; struct Obj1 *m18; };
struct Obj2 { u8 pad000[0x4]; s16 m04; };

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 TaskUpdateSoundSet_206ff0(void)
{
    struct Obj0 *r0;
    s32 r1;
    s32 rv;
    struct Obj2 *r3;

    r0 = ((struct Obj0 *)GetGameData_1fede0());
    r1 = ((s32)GetMapMgr_201a90());
    rv = MapGetSoundEnvPresetIdById_1e53f0(r1, r0->m18->m30);
    if (rv == 0x2710) {
        r3 = ((struct Obj2 *)SoundEnvPresetTableGet_207db0(r0->m18->m04));
        rv = r3->m04;
    }
    return SceneSoundEnvApplyPreset_207e20(rv, 0);
}
