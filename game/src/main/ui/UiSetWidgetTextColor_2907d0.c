/* rgp:protos */
#define RGP_SELF_UiSetWidgetTextColor_2907d0 1
#include "port/game_protos.h"
#line 1
/* main s27m: 14 -> 11 -- UiGetWidgetText_28f620 takes (a, b, idx) per its merged definition, so
   this unit has two leading pass-through params. PARK: retail loop is NON-ROTATED
   (li -1 hoisted, beql p==NULL -> epilogue with v0=1, beq id==-1, sw, b back);
   while/for/goto/for(;;)+break and opt_rotateloops off are all 0x78-0x80. */
#include "types.h"

typedef struct {
    s16 id;
    u8 pad2[0xA];
    s32 val;
} Elem2907D0;

/*rgp*/

s32 UiSetWidgetTextColor_2907d0(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    Elem2907D0 *p;

    p = ((Elem2907D0 *)UiGetWidgetText_28f620(arg0, arg1, 0));
    if (p == NULL) {
        return 0;
    }
    if (arg3 != 0) {
        for (;;) {
            if (p == NULL) break;
            if (p->id == -1) break;
            p->val = arg2;
            p++;
        }
    } else {
        p->val = arg2;
    }
    return 1;
}
