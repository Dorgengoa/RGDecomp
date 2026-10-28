/* rgp:protos */
#define RGP_SELF_DListInsertSortedById_227110 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_dead_assignments off

typedef struct {
    u8 pad0[0x3E];
    s16 unk3E;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

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
    DListRemove_42e4e0((void *)arg0, (void *)arg1);
    if (((unsigned char)IsNonNegative_42cab0(arg1->unk3E)) == 0) {
        return 0;
    }
    id = arg1->unk3E;
    cur = ((Obj *)DListGetHead_42ea60(arg0));
    if (cur == NULL) {
        cur = NULL;
        goto done;
    }
    if (IntCompare_42ca30(id, cur->unk3E) < 0) {
        r = 0;
        goto done;
    }
    n = ((unsigned short)DListGetCountPow2_42ea70(arg0));
    while (n > 0) {
        n >>= 1;
        t = ((Obj *)DListNodeAdvance_42eb00(cur, n));
        if (t != NULL && IntCompare_42ca30(id, t->unk3E) >= 0) {
            cur = t;
        }
    }
    cur = ((Obj *)DListGetNext_42eb30(cur));
done:
    if (cur != NULL) {
        r = DListInsertBefore_42e860(arg0, cur, arg1);
    } else {
        r = DListPushBack_42e5a0(arg0, arg1);
    }
    return r & 0xFF;
}
