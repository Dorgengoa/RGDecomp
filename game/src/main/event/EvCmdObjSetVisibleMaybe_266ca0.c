/* rgp:protos */
#define RGP_SELF_EvCmdObjSetVisibleMaybe_266ca0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdObjSetVisibleMaybe_266ca0(s64 *arg0, s32 arg1)
{
    void *p;
    s32 a;
    s32 b;
    f32 f;

    if ((p = EventSceneGetObj_2676e0(ScriptGetInt_26a2a0((s32)arg0++))) == NULL) {
        return 0;
    }
    a = ScriptGetInt_26a2a0((s32)arg0++);
    *(s32 *)((u8 *)p + 0x1C0) = a != 0;
    if (arg1 < 3) {
        goto tail;
    }
    b = ScriptGetInt_26a2a0((s32)arg0++);
    *(s32 *)((u8 *)p + 0x1DC) = b;
    if (b != 1) {
        goto tail;
    }
    if (a == 1) {
        *(s32 *)((u8 *)p + 0x1C8) &= ~1;
    } else {
        *(s32 *)((u8 *)p + 0x1C8) |= 1;
    }
    if (arg1 >= 4) {
        f = TaggedGetFloat_26a280((s32)arg0);
        *(f32 *)((u8 *)p + 0x1E4) = f;
        *(f32 *)((u8 *)p + 0x1E8) = f;
    }
    return 1;
tail:
    if (a == 1) {
        *(s32 *)((u8 *)p + 0x1C8) &= ~1;
    } else {
        *(s32 *)((u8 *)p + 0x1C8) |= 1;
    }
    ModelObjFadeSnap_186b20(p);
    *(f32 *)((u8 *)p + 0x1E4) = 1.0f;
    *(f32 *)((u8 *)p + 0x1E8) = 1.0f;
    return 1;
}
