#include "types.h"
/* normal 0x00506BC0 -- two guards sharing a `return 0`; no callee-saved frame
 * because `p` is dead after func_289B60 takes it in $4. */
typedef struct Obj { u8 pad00[0xA6]; s16 fA6; } Obj;
extern void *func_289B60(Obj *p);
extern void  func_291910(void *w);
extern s32 normal_LeaderHudDraw_506bc0(Obj *p);
s32 normal_LeaderHudDraw_506bc0(Obj *p)
{
    void *w;
    if (p->fA6 == 0) {
        return 0;
    }
    w = func_289B60(p);
    if (w == 0) {
        return 0;
    }
    func_291910(w);
    return 1;
}
