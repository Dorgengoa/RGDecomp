/* rgp:protos */
#define RGP_SELF_MesWinDrawPageIcon_2713f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 x;
    s32 y;
    s32 w;
    s32 h;
} Rect;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_0045F200[];
extern s32 D_0045F208[];
extern s16 D_0045F6F0[];
extern s16 D_0045F6F2[];
extern s16 D_0045F6F4[];
extern s16 D_0045F6F6[];

void MesWinDrawPageIcon_2713f0(u8 *s, s32 arg1)
{
    Rect dst __attribute__((aligned(16)));
    Rect src __attribute__((aligned(16)));
    u8 col[8];
    u8 *g;
    s32 t;

    if (arg1 == 0) {
        return;
    }
    if (*(s8 *)(s + 0x1DEE) == 0) {
        return;
    }
    if (((unsigned char)DoubleLess_1002b0(fptodp(MesWinGetOpenRate_277540((void *)s)), 1.0)) != 0) {
        return;
    }
    if (MesWinHasCloseMark_2715f0(s)) {
        return;
    }
    t = MesWinGetShownEnd_271680(s);
    if (t < MesWinGetCharCount_274c70(s) || *(s32 *)(s + 0x1C24) >= 0) {
        if (((signed char)MesWinIsPageWait_2721f0(s)) == 0) {
            return;
        }
    }
    if ((MesWinGetPageFrames_271ec0(s) / 16) % 2 != 0) {
        return;
    }
    g = ((u8 *)GetDrawCtx_15de80());
    t = DrawEnvGetWidth_1451e0(g);
    DrawEnvGetHeight_1451d0(g);
    {
        s32 x0 = *(s32 *)(s + 0x80) + (s16)(D_0045F208[0] + 4);
        s32 h, w;

        col[2] = 0x80;
        col[1] = 0x80;
        col[0] = 0x80;
        col[3] = (*(u8 *)(s + 0x195C) << 7) / 128;
        dst.x = x0;
        src.x = D_0045F6F2[0];
        src.y = D_0045F6F0[0];
        w = D_0045F6F6[0];
        h = D_0045F6F4[0];
        src.w = w;
        src.h = h;
        dst.y = t / 2 - (s16)(D_0045F200[0] - 1) / 2;
        dst.w = w;
        dst.h = h;
    }
    FontDrawGaijiSprite_26fa50(arg1, &dst, &src, col);
}
