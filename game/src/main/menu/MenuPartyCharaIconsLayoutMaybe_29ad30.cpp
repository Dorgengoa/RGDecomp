#include "types.h"

extern "C" {
typedef struct Pt { s16 x; s16 y; } Pt;
typedef struct Pt6 { Pt p[6]; } Pt6;
typedef struct Pt9 { Pt p[9]; } Pt9;
typedef struct Ctx { u8 pad[0x18]; s32 ctx; } Ctx;
typedef struct Win { u8 pad[0x4C4]; s32 h; } Win;
extern Ctx *GetGameData_1fede0(void);
extern void UiSetSpriteX_28fcd0(s32, s32, s32, s32);
extern void UiSetSpriteUv_28f970(s32, s32, s32, s32, s32);
extern void UiSetSpritePos_28fd10(s32, s32, s32, s32, s32);
extern Pt D_00450CE0[];
extern Pt D_00450D00[];
}

class VC {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v92(s32 a0, s32 a1) { return VCM(s32, (void *, s32, s32), 0x178, a0, a1); }
    
    s32 v94(s32 a0, s32 a1) { return VCM(s32, (void *, s32, s32), 0x180, a0, a1); }
};

extern "C" VC *PartyGetSlotChara_3c2fb0(s32, s32);

extern "C" s32 MenuPartyCharaIconsLayoutMaybe_29ad30(Win *w, s32 id, s32 key)
{
    Pt6 a __attribute__((aligned(16)));
    Pt9 b __attribute__((aligned(16)));
    Ctx *c;
    s32 cnt;
    s32 i;
    VC *o;
    s32 n;
    s32 j;
    s32 m;
    s32 k;

    c = GetGameData_1fede0();
    for (i = 0; i < 11; i++) {
        UiSetSpriteX_28fcd0(w->h, id, -1, i);
    }
    o = PartyGetSlotChara_3c2fb0(c->ctx, (s16)key);
    if (o == 0) return 0;
    a = *(Pt6 *)D_00450CE0;
    b = *(Pt9 *)D_00450D00;
    cnt = 0;
    for (i = 0; i < 5; i++) {
        if (o->v92(i, 1) > 0) cnt++;
    }
    for (i = 0; i < 8; i++) {
        if (o->v94(i + 2, 1) > 0) cnt++;
    }
    n = 20;
    if (cnt >= 11) n = 18;
    k = 0;
    for (j = 0; j < 5; j++) {
        if (o->v92(j, 1) > 0) {
            UiSetSpriteUv_28f970(w->h, id, a.p[j].x, a.p[j].y, k);
            UiSetSpritePos_28fd10(w->h, id, k * n + 0xAE, 0x71, k);
            k++;
        }
    }
    for (m = 0; m < 8; m++) {
        if (o->v94(m + 2, 1) > 0) {
            UiSetSpriteUv_28f970(w->h, id, b.p[m].x, b.p[m].y, k);
            UiSetSpritePos_28fd10(w->h, id, k * n + 0xAE, 0x71, k);
            k++;
            if (k >= 11) return 1;
        }
    }
    return 1;
}
