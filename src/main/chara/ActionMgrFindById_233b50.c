#include "types.h"

/* Head of a 5-member clone group (204 B each): ActionMgrFindById_233b50 / ActionMgrFindTableByScopeId_233c20 /
   Members differ in the container
   offset `o + K` and in which key-extractor / comparator pair is called.

   A halving search over a SINGLY-LINKED list: DListNodeAdvance_42eb00 walks `n` links
   from a base, so each step costs the remaining span and the span halves.
   DListGetHead_42ea60 is begin(), DListGetCountPow2_42ea70 is size() (u16), CharaGetId_214a80 reads
   the s16 key out of the payload and IntCompare_42ca30 is `a - b`. */

typedef struct Cont233 {
    u8  pad000[0x20];
    s32 m20;                    /* the container sub-object */
} Cont233;

extern void *DListGetHead_42ea60(void *c);
extern s32   DListGetCountPow2_42ea70(void *c);
extern void *DListNodeAdvance_42eb00(void *node, s32 n);
extern s32   CharaGetId_214a80(void *payload);
extern s32   IntCompare_42ca30(s32 a, s32 b);

void *ActionMgrFindById_233b50(Cont233 *o, s32 key)
{
    void *found;
    void *base;
    s32   n;
    void *cur;
    s32   c;

    if ((base = DListGetHead_42ea60(&o->m20)) == 0) {
        found = 0;
    } else {
        found = 0;
        n = DListGetCountPow2_42ea70(&o->m20);
        while (n > 0) {
            n >>= 1;
            cur = DListNodeAdvance_42eb00(base, n);
            if (cur != 0) {
                c = IntCompare_42ca30(key, CharaGetId_214a80((u8 *)cur + 0x10));
                if (c == 0) {
                    found = cur;
                    break;
                }
                if (c > 0) {
                    base = cur;
                }
            }
        }
    }
    return found == 0 ? 0 : (u8 *)found + 0x10;
}
