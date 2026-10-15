#include "types.h"

void DrawListAddTexLoad_1418c0(s32, s32, f32);
s32 GetDrawCtx_15de80(void);
void TreasureBoxDraw_339540(void *, f32);
s32 TreasureBoxGetTexGroup_33b110(void *);

typedef struct O { u8 pad[0x70]; u8 f0 : 1; u8 f1 : 1; } O;

s32 TreasureBoxPoolDraw_338c00(u8 *arg0, s32 arg1, s32 arg2, f32 fparg0) {
    s32 t;
    s32 cur;
    O **pp;
    s32 i;
    O *o;
    u8 b;

    if (*(s32 *)(arg0 + 0) == 0) {
        return 0;
    }
    if (*(O ***)(arg0 + 4) == NULL) {
        return 0;
    }
    t = GetDrawCtx_15de80();
    pp = *(O ***)(arg0 + 4);
    cur = -1;
    for (i = 0; i < *(s16 *)(arg0 + 8); i++, pp++) {
        o = *pp;
        if (o != NULL) {
            b = o->f1;
            if ((b && arg1) || (!b && arg2)) {
                s32 v = TreasureBoxGetTexGroup_33b110(o);
                if (cur != v) {
                    cur = v;
                    DrawListAddTexLoad_1418c0(t, v, 1.0f);
                }
                TreasureBoxDraw_339540(o, fparg0);
            }
        }
    }
    return 0;
}
