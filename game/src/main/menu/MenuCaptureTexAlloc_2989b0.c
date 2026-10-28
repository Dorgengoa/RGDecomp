/* rgp:protos */
#define RGP_SELF_MenuCaptureTexAlloc_2989b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN MenuCaptureTexAlloc_2989b0 -- window 0x00296000-0x0029C000.  PURE SUBSTITUTION off
   src/wf/main/MenuCaptureScreenTex_298810.c (byte-identical, manifest unit #30): this is that
   unit's HEAD -- the same GetDrawCtxNameTable_15de40 / NameTableFreeGroup_158ac0(0x32D) /
   NameTableAddEntry_159b70(...,0x100,0x100,0x20,...) allocation and the same
   `D_00482414->f2 = 0` bitfield insert -- with the blit loop and the
   MemStackAlign64_14d8e0/0014d950 handle traffic removed.

   Two differences from the seed, both read off the listing:
     * ONE `NameTableFreeGroup_158ac0(w, 0x32D)` here, not two.
     * the `m50` store re-loads BOTH globals (`lw %gp_rel(D_00482418)` +
       `lw %gp_rel(D_00482414)`).  In the seed the destination was a live
       local; here it is a global read, and the `sb 0x3C` above it invalidates
       the cached `D_00482414` load, so both are written as global reads.
       A LOAD WILL NOT CROSS A STORE TO A GLOBAL.
   The seed's two pragmas are NOT carried: `opt_propagation off` existed for
   the blit loop's `r + q[i]` fold and `opt_rotateloops off` for that loop's
   entry test.  There is no loop here.  */

typedef struct Res989b0 {
    u8 pad00[0x3C];
    u8 f0 : 1;
    u8 f1 : 1;
    u8 f2 : 1;               /* bit 2 of +0x3C */
    u8 f3 : 5;
    u8 pad3D[0x13];
    void *m50;               /* +0x50 */
} Res989b0;

/*rgp*/
/*rgp*/
/*rgp*/


extern Res989b0 *D_00482414;
extern void *D_00482418;
extern u8 D_00461240[];

void MenuCaptureTexAlloc_2989b0(void)
{
    void *w;

    w = GetDrawCtxNameTable_15de40();
    NameTableFreeGroup_158ac0(w, 0x32D);
    D_00482414 = ((Res989b0 *)NameTableAddEntry_159b70(w, 0x32D, D_00461240, 0, 0x100, 0x100, 0x20, 0, (long long)(0), 0
));
    if (D_00482414 != 0) {
        D_00482414->f2 = 0;
        D_00482414->m50 = D_00482418;
    }
}
