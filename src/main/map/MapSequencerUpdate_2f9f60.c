#include "types.h"

typedef struct {
    u8 pad0[0x10];
    u8 sub[0x10];
    s32 p20;
} List;

extern void MemStackHeapFree_14dcb0(s32, u8 *);
extern s32 MapNodeMoverIsIdle_2fa490(u8 *);
extern void MapNodeMoveStep_2fa4a0(u8 *);
extern void MapNodeMoveStart_2fa560(u8 *, u8 *);
extern s32 MapNodeMoverGetId_2fa7b0(u8 *);
extern s32 MapNodeMoveReqGetTargetId_2fa8c0(u8 *);
extern void DListRemove_42e4e0(void *, u8 *);
extern u8 *DListGetHead_42ea60(void *);
extern u8 *DListGetNext_42eb30(u8 *);

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
    next = DListGetHead_42ea60(arg0);
    while ((n = next) != NULL) {
        next = DListGetNext_42eb30(n);
        item = n + 0x10;
        if (MapNodeMoverIsIdle_2fa490(item) != 0) {
            next2 = DListGetHead_42ea60(arg0->sub);
            while ((m = next2) != NULL) {
                next2 = DListGetNext_42eb30(m);
                sub = m + 0x10;
                t = MapNodeMoverGetId_2fa7b0(item);
                if (t == MapNodeMoveReqGetTargetId_2fa8c0(sub)) {
                    MapNodeMoveStart_2fa560(item, sub);
                    MemStackHeapFree_14dcb0(arg0->p20, m);
                    DListRemove_42e4e0(arg0->sub, m);
                    if (MapNodeMoverIsIdle_2fa490(item) == 0) {
                        break;
                    }
                }
            }
        }
        if (MapNodeMoverIsIdle_2fa490(item) != 0) {
            MemStackHeapFree_14dcb0(arg0->p20, n);
            DListRemove_42e4e0(arg0, n);
        }
    }
    for (n = DListGetHead_42ea60(arg0); n != NULL; n = DListGetNext_42eb30(n)) {
        MapNodeMoveStep_2fa4a0(n + 0x10);
    }
}
