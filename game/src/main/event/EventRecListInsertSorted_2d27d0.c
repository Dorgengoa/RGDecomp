/* rgp:protos */
#define RGP_SELF_EventRecListInsertSorted_2d27d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN EventRecListInsertSorted_2d27d0 -- 340 B / 85 words.
   COLD TWIN FAMILY, n=10, 3,400 B (build/px-lanes/cold-L5.json): all ten members
   share one 85-instruction stream and differ ONLY in three callee addresses, so
   one reading converts all ten.  Ordered insert into a sorted skip-list-ish
   container: a key is extracted from arg1+0x10, the top node is walked down by a
   halving stride, and the hit is handed to the insert-after or insert-head call.

   TWO readings had to be measured before the bytes came out.
   1. Retail's two dispatches both BRANCH INTO the body and then spend an extra
      `b <join>` on the fall-through arm.  Writing them as plain `if (c) { body }`
      lets mwcc invert the test and drop the `b`, which is exactly TWO WORDS SHORT
      per site.  An explicit `goto` recovers the first site (the arm has a real
      statement, `res = 0`); it does NOT recover the second, and the goto form, the
      `else if` form and the EMPTY-then-arm form all compile to ONE object.
   2. The second site is only recovered by a SEPARATE result variable that the
      allocator coalesces onto the node register: the middle arm is `res = node`,
      which emits no instruction yet still forces the block, so the `b <join>` keeps
      its nop delay slot.  One variable plus `node = node` does not do it.
   Also: retail FALLS THROUGH into the DListInsertBefore_42e860 call, so that is the source's
   `if` body and the head-insert is the trailing return; and the per-arm `andi 0xFF`
   (one in each arm, not one at the join) is a u8 return type with two `return`
   statements, not a joined temporary.  */

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

u32 EventRecListInsertSorted_2d27d0(s32 arg0, s32 arg1)
{
    s32 key;
    s32 node;
    s32 n;
    s32 q;
    s32 res;

    if (arg1 == 0) {
        return (u8)(0);
    }
    DListRemove_42e4e0((void *)arg0, (void *)arg1);
    if (((unsigned char)ToBool_42cac0(EventRecGetKey_2e5730(arg1 + 0x10))) == 0) {
        return (u8)(0);
    }
    key = EventRecGetKey_2e5730(arg1 + 0x10);
    node = DListGetHead_42ea60(arg0);
    if (node == 0) {
        res = 0;
    } else if (StrCmpNullSafe_42ca40(key, EventRecGetKey_2e5730(node + 0x10)) < 0) {
        res = node;
    } else {
        n = ((unsigned short)DListGetCountPow2_42ea70(arg0));
        while (n > 0) {
            n = n >> 1;
            q = ((s32)DListNodeAdvance_42eb00(node, n));
            if ((q != 0) && (StrCmpNullSafe_42ca40(key, EventRecGetKey_2e5730(q + 0x10)) >= 0)) {
                node = q;
            }
        }
        res = DListGetNext_42eb30(node);
    }
    if (res != 0) {
        return (u8)(DListInsertBefore_42e860(arg0, res, arg1));
    }
    return (u8)(DListPushBack_42e5a0(arg0, arg1));
}
