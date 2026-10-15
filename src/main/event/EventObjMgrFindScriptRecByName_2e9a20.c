#include "types.h"

/* Member of the 5-clone group headed by ActionMgrFindById_233b50 (204 B each).
   This member differs from the head in the container offset `o + K` and
   the key-extractor / comparator pair.  The reading is written up in
   ActionMgrFindById_233b50.c. */

typedef struct Cont233 {
    u8  pad000[0x30];
    s32 m20;                    /* the container sub-object */
} Cont233;

extern void *DListGetHead_42ea60(void *c);
extern s32   DListGetCountPow2_42ea70(void *c);
extern void *DListNodeAdvance_42eb00(void *node, s32 n);
extern s32   EventRecGetKey_2e5730(void *payload);
extern s32   StrCmpNullSafe_42ca40(s32 a, s32 b);

void *EventObjMgrFindScriptRecByName_2e9a20(Cont233 *o, s32 key)
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
                c = StrCmpNullSafe_42ca40(key, EventRecGetKey_2e5730((u8 *)cur + 0x10));
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
