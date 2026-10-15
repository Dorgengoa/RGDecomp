#include "types.h"

typedef struct {
    s32 unk0;
    s32 unk4;
} Ctx00245190;

void SoundPlayDefault_1b9ae0(s32, s32, s32);
void ObjRecSetFlags_1c3e00(s32, s32, s32, s32);
s32 GameSceneSoundSlot1GetHandle_1d07b0(s32);
s32 ScriptGetCodeAddr_249050(s32);
s32 ScriptGetInt_2490f0(s32);
s32 EventCastFindKeyByName_24bb50(s32, s32);
s32 EventCastGetObjId_24c160(s32, s32);
extern Ctx00245190 *gEventContext;

s32 EvCmdSoundPlayMaybe_245190(s64 *arg0, s32 arg1) {
    s32 a;
    s32 b;
    s32 h;
    s32 k;
    s32 t;
    s32 c;

    a = gEventContext->unk0;
    b = gEventContext->unk4 + 0x60;
    h = GameSceneSoundSlot1GetHandle_1d07b0(a);
    switch (*(s32 *)arg0) {
    case 0:
        if (arg1 != 1) {
            return 0;
        }
        SoundPlayDefault_1b9ae0(h, ScriptGetInt_2490f0((s32)arg0), 0);
        break;
    case 2:
        if (arg1 != 2) {
            return 0;
        }
        {
            k = ScriptGetCodeAddr_249050((s32)arg0++);
            t = ScriptGetInt_2490f0((s32)arg0);
            c = EventCastGetObjId_24c160(b, EventCastFindKeyByName_24bb50(b, k));
            if (t == 0) {
                ObjRecSetFlags_1c3e00(a, 1, c, 0x200000);
            }
            if (t == 1) {
                ObjRecSetFlags_1c3e00(a, 1, c, 0x400000);
            }
            ObjRecSetFlags_1c3e00(a, 1, c, 0x100000);
        }
        break;
    }
    return 1;
}
