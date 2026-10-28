/* rgp:protos */
#define RGP_SELF_UiGlowSpriteListInit_33bf40 1
#include "port/game_protos.h"
#line 1
#include "types.h"


/*rgp*/                    /* extern */
/*rgp*/                                 /* extern */
/*rgp*/                              /* extern */
extern volatile f32 D_0047D1FC __attribute__((section(".sdata")));
extern f32 D_0047D518;

typedef struct {s16 a,b,c,pad; f32 v,w,x,y;} P;
typedef struct {s32 a,b;s16 c;u8 pad[4];s16 n;P pts[8];} O;
void UiGlowSpriteListInit_33bf40(O *arg0, s32 arg1, s32 arg2) {
    P *var_17;
    s32 var_16; f32 f;

    arg0->a = ((s32)NameTableFindByName_159fb0(GetDrawCtxNameTable_15de40(), arg1, arg2));
    var_17 = arg0->pts;
    arg0->b = arg2;
    var_16 = 0;
    arg0->n = 0;
    do {
        var_17->a = (s16) (s32) RandRangeFloat_1ca5d0(96.0f);
        var_17->b = (s16)RandRangeFloat_1ca5d0(8.0f) + 0x28;
        var_17->v = RandRangeFloat_1ca5d0(D_0047D1FC);
        var_17->w = 0;
        var_17->x = 0.125f;

        f = RandRangeFloat_1ca5d0(1.5f);
        var_16 += 1;
        var_17->y = D_0047D518 + f;
        var_17->c = 1;
        var_17++;
        arg0->n = (s16) (arg0->n + 1);
    } while (var_16 < 8);
    arg0->c = 1;
}
