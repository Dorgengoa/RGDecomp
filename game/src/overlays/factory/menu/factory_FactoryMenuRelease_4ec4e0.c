/* rgp:protos */
#define RGP_SELF_factory_FactoryMenuRelease_4ec4e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ent {
    s32 f00;
    s32 f04;
} Ent;                                          /* 8 */

extern Ent   D_00480810[1];                     /* _gp - 0x4960 */
extern s32   D_00484A70;                        /* _gp - 0x700  */
extern void *D_00484A58;                        /* _gp - 0x718  */
extern void *D_00484A2C;                        /* _gp - 0x744  */
extern void *D_00484A30;                        /* _gp - 0x740  */
extern u8    D_00484A68;                        /* _gp - 0x708  */

/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_004B2570[0x10];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryMenuRelease_4ec4e0(void)
{
    void *w;
    void *h;
    s32   i;
    Ent  *e;

    w = GetDrawCtxNameTable_15de40();
    for (i = 0; i < 2; i++) {
        e = &D_00480810[i];
        if (e->f04 >= 0) {
            if (e->f00 != -1) {
                h = GetLoaderMgr_1f59d0();
                LoaderReleaseById_1cd340(h, e->f00);
                e->f00 = -1;
                e->f04 = 0;
            }
        }
    }
    D_00484A70 = 0;
    PadClearRepeatAll_183960(D_004B2570);
    PadClearStickDpadThreshold_183940(D_004B2570);
    D_00484A58 = 0;
    if (D_00484A2C != 0) {
        MemStackReset_14d830(D_00484A2C);
    }
    if (D_00484A30 != 0) {
        MemStackReset_14d830(D_00484A30);
    }
    NameTableFreeGroup_158ac0(w, 0x32D);
    NameTableFreeGroup_158ac0(w, 0x32F);
    NameTableFreeGroup_158ac0(w, 0x32E);
    D_00484A68 = 0;
}
