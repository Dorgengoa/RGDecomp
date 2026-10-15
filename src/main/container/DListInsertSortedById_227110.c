#include "types.h"
#pragma opt_dead_assignments off

typedef struct {
    u8 pad0[0x3E];
    s16 unk3E;
} Obj;

extern s32 IntCompare_42ca30(s16, s16);
extern s32 IsNonNegative_42cab0(s16);
extern void DListRemove_42e4e0(void);
extern s32 DListPushBack_42e5a0(s32, Obj *);
extern s32 DListInsertBefore_42e860(s32, Obj *, Obj *);
extern Obj *DListGetHead_42ea60(s32);
extern s32 DListGetCountPow2_42ea70(s32);
extern Obj *DListNodeAdvance_42eb00(Obj *, s32);
extern Obj *DListGetNext_42eb30(Obj *);

s32 DListInsertSortedById_227110(s32 arg0, Obj *arg1)
{
    s16 id;
    Obj *cur;
    s32 n;
    Obj *t;
    s32 r;

    if (arg1 == NULL) {
        return 0;
    }
    DListRemove_42e4e0();
    if (IsNonNegative_42cab0(arg1->unk3E) == 0) {
        return 0;
    }
    id = arg1->unk3E;
    cur = DListGetHead_42ea60(arg0);
    if (cur == NULL) {
        cur = NULL;
        goto done;
    }
    if (IntCompare_42ca30(id, cur->unk3E) < 0) {
        r = 0;
        goto done;
    }
    n = DListGetCountPow2_42ea70(arg0);
    while (n > 0) {
        n >>= 1;
        t = DListNodeAdvance_42eb00(cur, n);
        if (t != NULL && IntCompare_42ca30(id, t->unk3E) >= 0) {
            cur = t;
        }
    }
    cur = DListGetNext_42eb30(cur);
done:
    if (cur != NULL) {
        r = DListInsertBefore_42e860(arg0, cur, arg1);
    } else {
        r = DListPushBack_42e5a0(arg0, arg1);
    }
    return r & 0xFF;
}
