#include "types.h"
/* insect 0x0050E2B0 -- 84 bytes, 21 instructions, 4 calls. */

typedef struct Obj {
    u8  pad00[0x450];
    s32 m450;                       /* +0x450 */
} Obj;

extern void *insect_InsectGetDamagePopupList_5108c0(Obj *o);
extern void  func_2D3230(void *h);
extern void  func_2D3180(void *h, s32 *p);
extern void  func_2D2D50(void *h);

void insect_InsectBattleDamagePopupInit_50e2b0(Obj *o)
{
    void *h;

    h = insect_InsectGetDamagePopupList_5108c0(o);
    if (h != 0) {
        func_2D3230(h);
        func_2D3180(h, &o->m450);
        func_2D2D50(h);
    }
}
