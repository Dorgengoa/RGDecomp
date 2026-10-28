/* rgp:protos */
#define RGP_SELF_MinimapSetRectExploredByName_32b590 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Item0032b590 {
    u8 pad0[0x54];
    s8 unk54[1];
} Item0032b590;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 strcmp(const s8 *, const s8 *);

void MinimapSetRectExploredByName_32b590(s32 arg0, s8 *arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 v;
    s32 b;
    s32 a;
    s32 n;
    s32 i;
    Item0032b590 *it;
    s32 fl;

    v = ((s32)GetMinimapMgr_201a70());
    if (arg0 == 0 || arg1 == NULL) {
        return;
    }

    a = MinimapMgrFindSlotByName_322340(v, arg0);
    if (a == 0) {
        return;
    }
    b = ((s32)MinimapGetEntryList_32a8b0(a));
    if (b == 0) {
        return;
    }
    n = ((short)EntryListGetCount_323680(b));
    fl = arg4 != 0;
    for (i = 0; i < n; i++) {
        it = ((Item0032b590 *)EntryListSelectByIndex_323540(b, i));
        if (it != NULL && strcmp(it->unk54, arg1) == 0) {
            MinimapSetRectExplored_32b9a0(arg2, arg3, fl, a, it);
        }
    }
}
