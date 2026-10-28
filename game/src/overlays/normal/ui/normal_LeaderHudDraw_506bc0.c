/* rgp:protos */
#define RGP_SELF_normal_LeaderHudDraw_506bc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00506BC0 -- two guards sharing a `return 0`; no callee-saved frame
 * because `p` is dead after func_289B60 takes it in $4. */
typedef struct Obj { u8 pad00[0xA6]; s16 fA6; } Obj;
/*rgp*/
/*rgp*/
extern s32 normal_LeaderHudDraw_506bc0(Obj *p);
s32 normal_LeaderHudDraw_506bc0(Obj *p)
{
    void *w;
    if (p->fA6 == 0) {
        return 0;
    }
    w = UiPageGetLayout_289b60(p);
    if (w == 0) {
        return 0;
    }
    UiDrawWidgets_291910(w);
    return 1;
}
