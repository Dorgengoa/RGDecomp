/* rgp:protos */
#define RGP_SELF_MapSequencerUpdate_2f9f60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x10];
    u8 sub[0x10];
    s32 p20;
} List;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void MapSequencerUpdate_2f9f60(List *arg0) {
    s32 t;
    u8 *n;
    u8 *next;
    u8 *item;
    u8 *m;
    u8 *next2;
    u8 *sub;

    if (arg0->p20 == 0) {
        return;
    }
    next = ((u8 *)DListGetHead_42ea60(arg0));
    while ((n = next) != NULL) {
        next = ((u8 *)DListGetNext_42eb30(n));
        item = n + 0x10;
        if (((unsigned char)MapNodeMoverIsIdle_2fa490(item)) != 0) {
            next2 = ((u8 *)DListGetHead_42ea60(arg0->sub));
            while ((m = next2) != NULL) {
                next2 = ((u8 *)DListGetNext_42eb30(m));
                sub = m + 0x10;
                t = MapNodeMoverGetId_2fa7b0(item);
                if (t == MapNodeMoveReqGetTargetId_2fa8c0(sub)) {
                    MapNodeMoveStart_2fa560(item, sub);
                    MemStackHeapFree_14dcb0(arg0->p20, m);
                    DListRemove_42e4e0(arg0->sub, m);
                    if (((unsigned char)MapNodeMoverIsIdle_2fa490(item)) == 0) {
                        break;
                    }
                }
            }
        }
        if (((unsigned char)MapNodeMoverIsIdle_2fa490(item)) != 0) {
            MemStackHeapFree_14dcb0(arg0->p20, n);
            DListRemove_42e4e0(arg0, n);
        }
    }
    for (n = ((u8 *)DListGetHead_42ea60(arg0)); n != NULL; n = ((u8 *)DListGetNext_42eb30(n))) {
        MapNodeMoveStep_2fa4a0(n + 0x10);
    }
}
