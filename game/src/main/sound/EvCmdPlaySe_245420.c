/* rgp:protos */
#define RGP_SELF_EvCmdPlaySe_245420 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/                        /* extern */
/*rgp*/                       /* extern */
/*rgp*/                              /* extern */
/*rgp*/                            /* extern */
/*rgp*/                            /* extern */
/*rgp*/                      /* extern */
/*rgp*/                         /* extern */
/*rgp*/                         /* extern */
/*rgp*/                              /* extern */
extern void *gEventContext;

s32 EvCmdPlaySe_245420(s64 *arg0, s32 arg1) {
    s32 a;
    s32 y;
    s32 x;
    s32 ctx;
    void *t;
    s32 z;
    s32 b;

    ctx = *(s32 *)((u8 *)gEventContext + 0x4);
    a = ctx + 0x60;
    b = ctx + 0x4A0;
    if ((arg1 != 2) && (arg1 != 3)) {
        return 0;
    }
    if (*(s32 *)arg0 == 2) {
        t = ObjRecGetLiveObject_1c4a90(*(s32 *)gEventContext, EventCastGetObjId_24c160(a, EventCastFindKeyByName_24bb50(a, ScriptGetCodeAddr_249050((s32)arg0++)), 0));
        if (t != NULL) {
            x = ScriptGetInt_2490f0((s32)arg0++);
            if (arg1 == 3) {
                y = ScriptGetInt_2490f0((s32)arg0);
            } else {
                y = 0;
            }
            if (y != 0) {
                z = *(s32 *)((u8 *)t + 0x500);
            } else {
                z = *(s32 *)((u8 *)t + 0x4FC);
            }
            SoundPlayDefault_1b9ae0(z, x, 0);
            EventSoundTableFindOrAdd_24a060(b, z, x);
        }
    } else {
        x = ScriptGetInt_2490f0((s32)arg0++);
        y = ScriptGetInt_2490f0((s32)arg0);
        if (x == 0) {
            z = GameSceneSoundSlot6GetHandle_1d0780(*(s32 *)gEventContext);
        } else {
            z = EventSoundBankHandleGet_24fc80(x);
        }
        SoundPlayDefault_1b9ae0(z, y, 0);
        EventSoundTableFindOrAdd_24a060(b, z, y);
    }
    return 1;
}
