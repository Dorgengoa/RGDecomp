/* rgp:protos */
#define RGP_SELF_factory_FactoryMenuResReady_4ec0e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Slot {
    s32 f0;
    s32 f4;
} Slot;

extern Slot  D_00480810[1];                     /* _gp - 0x4960 */
extern void *D_00484A2C;                        /* _gp - 0x744  */
extern void *D_00484A30;                        /* _gp - 0x740  */
extern void *D_00484A70;                        /* _gp - 0x700  */
extern void *D_00484A88;                        /* _gp - 0x6E8  */
extern u8    D_00484A64;                        /* _gp - 0x70C  */
extern u8    D_00484A68;                        /* _gp - 0x708  */
extern void *D_004807F8;                        /* _gp - 0x4978 */

extern u8 factory_D_0050CA70[];
extern u8 factory_D_0050CA88[];
extern u8 factory_D_0050CAA0[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 factory_FactoryMenuResReady_4ec0e0(void)
{
    void *h;
    s32   total;
    s32   i;
    Slot *e;
    void *p;
    void *q;
    s32   sz;
    s32   k;

    h = GetLoaderMgr_1f59d0();
    total = 0;
    for (i = 0; i < 2; i++) {
        e = &D_00480810[i];
        if (e->f4 == 0) {
            if (e->f0 != -1) {
                e->f4 = LoaderGetStatus_1cd4f0(h, e->f0);
                if (e->f4 == 1) {
                    if (i != 1) {
                        MemStackAlign64_14d8e0(D_00484A2C);
                        p = LoaderGetData_1cd490(h, e->f0, &sz);
                    }
                    if (i == 1) {
                        p = LoaderGetData_1cd490(h, e->f0, &sz);
                        q = GetDrawCtxNameTable_15de40();
                        MemMoveIfDiff_289c60(p, sz, D_00484A88);
                        NameTableRegisterImArchive_1594d0(q, D_00484A88, 0x32E, D_00484A30, 0);
                    } else if (i == 0) {
                        ResGroupLoadByKind_42b840(GetMenuResGroup_206a40(), 2, 5, D_00484A2C, p);
                        D_00484A70 = MsgTableLoadFromArchive_202a50(p, factory_D_0050CA70, D_00484A2C);
                        TexGroupLoadFromArchive_202be0(p, factory_D_0050CA88, D_00484A2C, 0x32D, 0);
                        TexGroupLoadFromArchive_202be0(p, factory_D_0050CAA0, D_00484A2C, 0x32F, D_00484A2C);
                        factory_FactoryMenuBuildWidgets_4ea1d0();
                    }
                    LoaderReleaseById_1cd340(h, e->f0);
                    e->f0 = -1;
                }
            }
        }
    }
    for (k = 0; k < 2; k++) {
        total += D_00480810[k].f4;
    }
    if (total == 2) {
        D_00484A64 = 1;
        D_00484A68 = 1;
        StateMachineSetState_28ede0(D_004807F8, 0x88B8, 0);
        return 1;
    }
    return 0;
}
