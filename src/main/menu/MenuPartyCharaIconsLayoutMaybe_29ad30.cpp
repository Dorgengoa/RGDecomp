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
    virtual s32 v0(s32, s32);
    virtual s32 v1(s32, s32);
    virtual s32 v2(s32, s32);
    virtual s32 v3(s32, s32);
    virtual s32 v4(s32, s32);
    virtual s32 v5(s32, s32);
    virtual s32 v6(s32, s32);
    virtual s32 v7(s32, s32);
    virtual s32 v8(s32, s32);
    virtual s32 v9(s32, s32);
    virtual s32 v10(s32, s32);
    virtual s32 v11(s32, s32);
    virtual s32 v12(s32, s32);
    virtual s32 v13(s32, s32);
    virtual s32 v14(s32, s32);
    virtual s32 v15(s32, s32);
    virtual s32 v16(s32, s32);
    virtual s32 v17(s32, s32);
    virtual s32 v18(s32, s32);
    virtual s32 v19(s32, s32);
    virtual s32 v20(s32, s32);
    virtual s32 v21(s32, s32);
    virtual s32 v22(s32, s32);
    virtual s32 v23(s32, s32);
    virtual s32 v24(s32, s32);
    virtual s32 v25(s32, s32);
    virtual s32 v26(s32, s32);
    virtual s32 v27(s32, s32);
    virtual s32 v28(s32, s32);
    virtual s32 v29(s32, s32);
    virtual s32 v30(s32, s32);
    virtual s32 v31(s32, s32);
    virtual s32 v32(s32, s32);
    virtual s32 v33(s32, s32);
    virtual s32 v34(s32, s32);
    virtual s32 v35(s32, s32);
    virtual s32 v36(s32, s32);
    virtual s32 v37(s32, s32);
    virtual s32 v38(s32, s32);
    virtual s32 v39(s32, s32);
    virtual s32 v40(s32, s32);
    virtual s32 v41(s32, s32);
    virtual s32 v42(s32, s32);
    virtual s32 v43(s32, s32);
    virtual s32 v44(s32, s32);
    virtual s32 v45(s32, s32);
    virtual s32 v46(s32, s32);
    virtual s32 v47(s32, s32);
    virtual s32 v48(s32, s32);
    virtual s32 v49(s32, s32);
    virtual s32 v50(s32, s32);
    virtual s32 v51(s32, s32);
    virtual s32 v52(s32, s32);
    virtual s32 v53(s32, s32);
    virtual s32 v54(s32, s32);
    virtual s32 v55(s32, s32);
    virtual s32 v56(s32, s32);
    virtual s32 v57(s32, s32);
    virtual s32 v58(s32, s32);
    virtual s32 v59(s32, s32);
    virtual s32 v60(s32, s32);
    virtual s32 v61(s32, s32);
    virtual s32 v62(s32, s32);
    virtual s32 v63(s32, s32);
    virtual s32 v64(s32, s32);
    virtual s32 v65(s32, s32);
    virtual s32 v66(s32, s32);
    virtual s32 v67(s32, s32);
    virtual s32 v68(s32, s32);
    virtual s32 v69(s32, s32);
    virtual s32 v70(s32, s32);
    virtual s32 v71(s32, s32);
    virtual s32 v72(s32, s32);
    virtual s32 v73(s32, s32);
    virtual s32 v74(s32, s32);
    virtual s32 v75(s32, s32);
    virtual s32 v76(s32, s32);
    virtual s32 v77(s32, s32);
    virtual s32 v78(s32, s32);
    virtual s32 v79(s32, s32);
    virtual s32 v80(s32, s32);
    virtual s32 v81(s32, s32);
    virtual s32 v82(s32, s32);
    virtual s32 v83(s32, s32);
    virtual s32 v84(s32, s32);
    virtual s32 v85(s32, s32);
    virtual s32 v86(s32, s32);
    virtual s32 v87(s32, s32);
    virtual s32 v88(s32, s32);
    virtual s32 v89(s32, s32);
    virtual s32 v90(s32, s32);
    virtual s32 v91(s32, s32);
    virtual s32 v92(s32, s32);
    virtual s32 v93(s32, s32);
    virtual s32 v94(s32, s32);
};

extern "C" VC *PartyGetSlotChara_3c2fb0(s32, s32);

extern "C" s32 MenuPartyCharaIconsLayoutMaybe_29ad30(Win *w, s32 id, s32 key)
{
    Pt6 a;
    Pt9 b;
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
