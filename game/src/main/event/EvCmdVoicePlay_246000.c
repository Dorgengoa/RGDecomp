/* rgp:protos */
#define RGP_SELF_EvCmdVoicePlay_246000 1
#include "port/game_protos.h"
#line 1
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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdVoicePlay_246000(E8 *p0, s32 p1)
{
    s32 r0;
    s32 r1;
    s32 r2;
    void *w;

    r0 = ((s32)GetLoaderMgr_1f59d0());
    w = (void *)((u8 *)gEventContext->m04 + 0x420);
    r1 = EventVoicePickChan_24f270(w, 1);
    r2 = ScriptGetCodeAddr_249050(p0++);
    EventVoiceChanSetPlaying_24f120(w, r1, -1, 0, 0);
    StreamStartChan_1cda90(r0, r1, r2, 0);
    StreamPlayChan_1cda20(r0, r1, 1.0f);
    if (p1 >= 2) {
        ScriptSetRefInt_249030(p0, r1);
    }
    return 1;
}
