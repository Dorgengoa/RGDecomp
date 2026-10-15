/* DataTableCompareById_4180c0 -- byte-identical clone of DataTableCompareById_417d40 (112 B), symbol renamed,
   nothing else changed.  Group verified by sha1 over the
   retail bytes; see build/zz/s23_bhash.json. */
#include "types.h"

/* Head of a 5-member byte-identical group (112 B each):
   DataTableCompareById_4180c0 / DataTableCompareById_417f00 / DataTableCompareById_4180c0 / DataTableCompareById_418290 / DataTableCompareById_418430.
   A three-way comparator that defers to a base comparator first.
   All three early exits are ONE `||` chain: the tell is that the r != 0 test
   is a `bnel` straight to the epilogue (with `ld $31` hoisted into the
   likely slot), not a branch around a `b`. */

struct Rec7d40 {
    s32 key;
};

extern s32 CompareNullness_368070(void *a);

s32 DataTableCompareById_4180c0(void *a, struct Rec7d40 *x, struct Rec7d40 *y)
{
    s32 r;

    r = CompareNullness_368070(a);
    if (r != 0 || x == 0 || y == 0) {
        return r;
    }
    if (x->key < y->key) {
        return -1;
    }
    return y->key < x->key;
}
