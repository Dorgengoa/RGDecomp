/* rgp:protos */
#define RGP_SELF_factory_FactoryMaterialMatchBlueprint_4f2750 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* f18d SESSION 18.  Two changes from the session-17 park:
 *  1. `u8 found` (was `s32`) plus BARE truth tests (`!found`, not
 *     `found == 0`).  The u8 is what makes mwcc materialise retail's
 *     `daddiu $19,$0,0x1` at 0x004F2838 as a SEPARATE constant from the
 *     `addiu 1` feeding `sb used[j],1` -- that un-CSE is the word the
 *     park was missing.  The bare test is what avoids the `andi` re-narrow
 *     that a `== 0` token costs on a u8.
 *  2. DECLARATION ORDER, found by enumerating 240 random permutations of
 *     the 16 locals in one probe TU (21 bad) and then hill-climbing over
 *     every transposition and relocation of the best (7 bad -> 0). */

typedef struct Item {
    s16 f00;
} Item;

typedef struct Slot {
    Item *f00;
    s16   f04;
    u8    pad06[0xA];
} Slot;                                         /* 0x10 */

typedef struct List {
    u8    pad00[0x8];
    s16   f08;
    u8    pad0A[0x2];
    Slot *f0C;
} List;

typedef struct Ctx {
    u8    pad00[0x70];
    List *f70;
} Ctx;

typedef struct Ent {
    u8 pad00[0x40];
} Ent;                                          /* 0x40 */

typedef struct Group {
    u8   pad00[0xC];
    s16  f0C;
    Ent *f10;
} Group;

typedef struct Hit {
    u8  pad00[0x4];
    s16 f04;
    s16 f06;
} Hit;

extern Ctx *D_00484A48;                         /* _gp - 0x728 */

/*rgp*/
extern void   memset(void *p, s32 v, s32 n);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 factory_FactoryMaterialMatchBlueprint_4f2750(void)
{
    Hit   *h2;
    Group *g;
    Ent   *e;
    Hit   *h;
    s32    i;
    s32    cnt;
    Slot  *s2;
    u8     found;
    Slot  *s;
    u8     used[4];
    s32    m;
    List  *lst;
    s32    n;
    s32    j;
    Ent   *e2;
    s32    hnd;

    lst = D_00484A48->f70;
    if (lst == 0) {
        return 0;
    }
    hnd = GetFactoryObj_367f30();
    g = ((Group *)factory_FactoryPartGroupFindById_504080(hnd, 0xD));
    if (g != 0) {
        memset(used, 0, 4);
        e = g->f10;
        for (i = 0; i < g->f0C; i++, e++) {
            s = lst->f0C;
            found = 0;
            for (j = 0; j < lst->f08 && !found; j++, s++) {
                h = ((Hit *)factory_FactorySlotFindAt_502ad0(hnd, factory_FactoryPartObjGetGridX_4fe120(e),
                                         factory_FactoryPartObjGetGridY_4fe0c0(e)));
                if (h != 0) {
                    if (h->f04 == s->f00->f00) {
                        if (used[j] == 0) {
                            found = 1;
                            used[j] = 1;
                        }
                    }
                }
            }
            if (!found) {
                return -1;
            }
        }
    }
    s2 = lst->f0C;
    cnt = 0;
    for (m = 0; m < lst->f08; m++, s2++) {
        if (g != 0) {
            e2 = g->f10;
            for (n = 0; n < g->f0C; n++, e2++) {
                h2 = ((Hit *)factory_FactorySlotFindAt_502ad0(hnd, factory_FactoryPartObjGetGridX_4fe120(e2),
                                          factory_FactoryPartObjGetGridY_4fe0c0(e2)));
                if (h2 != 0) {
                    if (h2->f04 == s2->f00->f00 && h2->f06 == s2->f04) {
                        cnt++;
                    }
                }
            }
        }
    }
    return cnt == lst->f08;
}
