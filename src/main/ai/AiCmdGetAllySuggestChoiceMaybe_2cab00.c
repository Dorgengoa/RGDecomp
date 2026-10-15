#include "types.h"

extern s32 AiAllySuggestGetAccepted_2bb9d0(s32, void *);
extern void ScriptSlotStoreIntRef_2cc900(s32, s16);
extern s32 ScriptSlotGetInt_2cc9c0(s32);
extern s32 D_004DB928[0x100];
extern s32 D_004DB930[0x100];

s32 AiCmdGetAllySuggestChoiceMaybe_2cab00(s64 *arg0) {
    s16 frame[8];
    s32 idx;
    s16 temp_17;
    s32 t;

    t = ScriptSlotGetInt_2cc9c0((s32)arg0++);
    if (t == D_004DB928[0]) {
        idx = AiAllySuggestGetAccepted_2bb9d0(D_004DB930[0], frame);
        temp_17 = frame[idx + 3];
        ScriptSlotStoreIntRef_2cc900((s32)arg0++, frame[idx + 1]);
        ScriptSlotStoreIntRef_2cc900((s32)arg0, temp_17);
        return 1;
    }
    return 0;
}
