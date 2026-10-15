#include "types.h"

extern void ScriptSetRefInt_26a1e0(s32, s16);
extern s32 ScriptGetInt_26a2a0(s32);
extern void *GetInteractState_27a650(void);

typedef struct { u8 b[8]; } E8_260590;
s32 EvCmdGetInteractStateNodeIdMaybe_260590(E8_260590 *arg0) {
    u8 *p;
    u8 *t;

    t = (u8 *)GetInteractState_27a650();
    if (t == NULL) {
        return 0;
    }
    switch (ScriptGetInt_26a2a0((s32) arg0++)) {
    case 0:
        p = *(u8 **)(t + 0x10);
        if (p != NULL) {
            ScriptSetRefInt_26a1e0((s32) arg0, *(s16 *)p);
        } else {
            ScriptSetRefInt_26a1e0((s32) arg0, -1);
        }
    }
    return 1;
}
