/* rgp:protos */
#define RGP_SELF_ModelObjSyncShadowModelFrames_1adbc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 n;
    s32 *tbl;
} Tab;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void ModelObjSyncShadowModelFrames_1adbc0(u8 *a) {
    Tab *t1;
    Tab *t0;
    s32 *p4;
    s32 *p3;
    s32 n;
    s32 m;
    s32 x;
    s32 y;

    ModelObjApplyMotionList_186700(a);
    if (*(s32 *)(a + 0x270) == 0) {
        return;
    }
    ModelGetRootFrame_1511a0(a);
    t1 = *(Tab **)(a + 0x104);
    p4 = *(s32 **)(a + 0x434);
    p3 = *(s32 **)(a + 0x438);
    n = *(s32 *)(a + 0x430);
    t0 = *(Tab **)(a + 0x374);
    if (t1 == NULL) {
        return;
    }
    if (t0 == NULL) {
        return;
    }
    y = t1->n;
    x = t0->n;
    if (*(s32 *)(a + 0x43C) > y) {
        goto slow;
    }
    if (*(s32 *)(a + 0x440) > x) {
        goto slow;
    }
        for (m = n; m > 0; m--, p4++, p3++) {
            x = t1->tbl[*p4];
            if (x != 0) {
                y = t0->tbl[*p3];
                if (y != 0) {
                    FrameCopyMatrixScale_148da0(x, y);
                }
            }
        }
    return;
slow:
        for (m = n; m > 0; m--, p4++, p3++) {
            x = ((s32)ModelGetFrame_1511f0(a, *p4));
            if (x != 0) {
                y = ((s32)ModelGetFrame_1511f0(a + 0x270, *p3));
                if (y != 0) {
                    FrameCopyMatrixScale_148da0(x, y);
                }
            }
        }
}
