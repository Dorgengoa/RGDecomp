#include "types.h"

/* Hub function, called from many already-merged src/ files -- their
   extern declarations pin the signature as (s32, s32, f32, f32, f32)
   returning void (a couple of callers discard a return value via an
   s32 decl, but nothing sets $2 here).  Calls two already-closed
   siblings: UiFindWidget_290460 (the list-lookup-by-key hub this lane already
   matched) and UiGetWidgetAlpha_290770 (src/p19d/UiGetWidgetAlpha_290770.c, returns a f32
   field off the same lookup). */

struct Node00290690 {
    u8 pad0[0x3C];
    f32 f3C;
    u8 pad40[0xC];
    f32 f4C;
    u8 pad50[0xC];
    f32 f5C;
};

extern struct Node00290690 *UiFindWidget_290460(void *head, s32 key);
extern f32 UiGetWidgetAlpha_290770(s32, s32);

void UiFadeWidgetAlpha_290690(void *arg0, s32 arg1, f32 fa, f32 fb, f32 fc)
{
    struct Node00290690 *node;

    node = UiFindWidget_290460(arg0, arg1);
    if (fc == -1.0f) {
        fc = UiGetWidgetAlpha_290770((s32)arg0, arg1);
    }
    if (node != 0) {
        if (fc >= 0.0f) {
            node->f3C = fc;
        }
        node->f4C = fa;
        if (fa < fc) {
            if (fb > 0.0f) {
                fb = fb * -1.0f;
            }
        }
        node->f5C = fb;
    }
}
/* MATCHED (s39 NEWVEIN). The s38 draft used an explicit `if (fb<=0){store;
   goto done;} fb=-fb; store;` goto-merge shape that cost 1 extra word (a
   bc1fl-likely-false-skip + explicit `b` to reach the merge, vs retail's
   bc1tl-likely-true landing directly on a fused delay-slot store). Dropping
   the goto entirely and writing the plain natural clamp idiom --
   `if (fb > 0.0f) { fb = -fb; } node->f5C = fb;` (single shared store,
   no goto) -- made mwcc pick the bc1tl fused-store shape on its own and
   closed the last word. LEVER for the vein: when a "goto done" merge is
   only there to skip a single trailing shared store, try dropping the
   goto and writing the plain if+fallthrough-store form first -- mwcc will
   often duplicate the store into both branch exits itself, with the
   correct likely-branch polarity, and the goto-based hand-duplication is
   actually the thing defeating it here. */
