#include "types.h"

typedef struct T_002452d0 { u8 b[8]; } T_002452d0;
typedef struct Obj0_002452d0 { s32 m00; s32 m04; } Obj0_002452d0;

typedef struct E_002452d0 {
    u8 pad0[0x4FC];
    s32 f4FC;
    s32 f500;
} E_002452d0;

extern Obj0_002452d0 *gEventContext;
extern s32 ScriptGetCodeAddr_249050(T_002452d0 *);
extern s32 ScriptGetInt_2490f0(T_002452d0 *);
extern s32 EventCastFindKeyByName_24bb50(void *, s32);
extern s32 EventCastGetObjId_24c160(void *, s32);
extern E_002452d0 *ObjRecGetLiveObject_1c4a90(s32, s32);
extern void SoundStopEntry_1b8bc0(s32, s32, s32);
extern s32 EventSoundBankHandleGet_24fc80(s32);
extern s32 GameSceneSoundSlot6GetHandle_1d0780(s32);

s32 EvCmdSoundStop_2452d0(T_002452d0 *q, s32 kind)
{
    void *ctx;
    E_002452d0 *e;
    s32 a;
    s32 c;
    s32 d;
    s32 f;
    s32 g;
    s32 h;
    s32 a2;
    s32 b2;
    s32 x;
    if (kind == 2) goto k23;
    if (kind == 3) goto k23;
    return 0;
k23:
    if (*(s32 *)q != 2) goto other;
    ctx = (void *)(gEventContext->m04 + 0x60);
    a = ScriptGetCodeAddr_249050(q++);
    c = EventCastFindKeyByName_24bb50(ctx, a);
    d = EventCastGetObjId_24c160(ctx, c);
    e = ObjRecGetLiveObject_1c4a90(gEventContext->m00, d);
    if (e == 0) goto one;
    f = ScriptGetInt_2490f0(q++);
    if (kind == 3) {
        g = ScriptGetInt_2490f0(q);
    } else {
        g = 0;
    }
    if (g != 0) {
        h = e->f500;
    } else {
        h = e->f4FC;
    }
    SoundStopEntry_1b8bc0(h, f, 0);
    goto one;
other:
    a2 = ScriptGetInt_2490f0(q++);
    b2 = ScriptGetInt_2490f0(q);
    if (a2 == 0) {
        x = GameSceneSoundSlot6GetHandle_1d0780(gEventContext->m00);
    } else {
        x = EventSoundBankHandleGet_24fc80(a2);
    }
    SoundStopEntry_1b8bc0(x, b2, 0);
one:
    return 1;
}
