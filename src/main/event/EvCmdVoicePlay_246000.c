#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

struct Obj1 {
    u8 pad000[0x420];
};

struct Obj0 {
    u8 pad000[0x4];
    struct Obj1 *m04;
};

extern struct Obj0 * gEventContext;
extern s32 GetLoaderMgr_1f59d0(void);
extern s32 EventVoicePickChan_24f270(void *, s32);
extern s32 ScriptGetCodeAddr_249050(E8 *);
extern void EventVoiceChanSetPlaying_24f120(void *, s32, s32, s32);
extern void StreamStartChan_1cda90(s32, s32, s32, s32);
extern void StreamPlayChan_1cda20(s32, s32, f32);
extern void ScriptSetRefInt_249030(E8 *, s32);

s32 EvCmdVoicePlay_246000(E8 *p0, s32 p1)
{
    s32 r0;
    s32 r1;
    s32 r2;
    void *w;

    r0 = GetLoaderMgr_1f59d0();
    w = (void *)((u8 *)gEventContext->m04 + 0x420);
    r1 = EventVoicePickChan_24f270(w, 1);
    r2 = ScriptGetCodeAddr_249050(p0++);
    EventVoiceChanSetPlaying_24f120(w, r1, -1, 0);
    StreamStartChan_1cda90(r0, r1, r2, 0);
    StreamPlayChan_1cda20(r0, r1, 1.0f);
    if (p1 >= 2) {
        ScriptSetRefInt_249030(p0, r1);
    }
    return 1;
}
