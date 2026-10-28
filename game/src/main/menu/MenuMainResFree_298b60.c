/* rgp:protos */
#define RGP_SELF_MenuMainResFree_298b60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN MenuMainResFree_298b60 -- same opening as the settled seed MenuMainResLoad_299080:
   `bnel $2,$0` PAST the `b` means the fall-through is the if BODY, so the
   guard is the positive `if (p == 0) return 1;`, and the dead
   `lbu 0x24C / andi 1` is that seed's `n = 3; if (bit) n = 3;` -- mwcc folds
   the select and keeps the condition.  LoadHandleArrayFree_28b0f0's SECOND PARAMETER IS
   s16 (the implicit conversion is what emits the dsll32/dsra32 pair). */

typedef struct Cfg298B60 { u8 pad000[0x24C]; u8 m24C; } Cfg298B60;
typedef struct Sys298B60 { u8 pad00[0x20]; Cfg298B60 *m20; } Sys298B60;

/*rgp*/
/*rgp*/

extern void *D_004823F8;

s32 MenuMainResFree_298b60(void)
{
    Sys298B60 *p;
    s32 n;

    p = ((Sys298B60 *)GetGameData_1fede0());
    if (p == 0) {
        return 1;
    }
    n = 3;
    if ((p->m20->m24C & 1) != 0) {
        n = 3;
    }
    LoadHandleArrayFree_28b0f0(D_004823F8, n);
    return 1;
}
