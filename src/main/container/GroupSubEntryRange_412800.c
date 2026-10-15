#include "types.h"

/* Linear search of a 100-entry 6-byte table for a (s16) key, then a pool
   lookup with stride 28 (sll 3, subu, sll 2).  The default entry sits at
   0x2F0 = 0x98 + 100*6, immediately after the array, and is the value `e`
   starts at.  `dsll32 $3,$5,16 / dsra32 $3,$3,16` is the (s16) cast of the
   id, threaded into the `bgtzl` likely slot. */

typedef struct E412800 {
    s16 m0;
    s16 m2;
    s16 m4;
} E412800;

typedef struct P412800 {
    u8       pad000[0x7C];
    s16      m7C;
    u8       pad07E[0xE];
    u8      *m8C;
    u8       pad090[0x8];
    E412800  ents[100];
    E412800  dflt;
} P412800;

void *GroupSubEntryRange_412800(P412800 *p, s32 id, s32 *out)
{
    E412800 *e;
    E412800 *it;
    s16      key;
    s32      j;
    s32      a;
    s32      b;

    /* TWO `||`s, and each one prints its own signature: op1 gives
       `beql`/`bltzl` STRAIGHT TO THE EXIT with `daddu $2,$0,$0` threaded into
       the likely slot, op2 gives a likely branch to the ELSE carrying the
       else's first instruction, and the shared THEN falls out as the 3-word
       `daddu / b / nop`.  Spelling either pair as two separate `if`s costs the
       threading on op1 and folds the THEN to 2 words. */
    *out = 0;
    if (p->m8C == 0 || p->m7C <= 0) return 0;

    key = (s16)id;
    e = &p->dflt;
    it = &p->ents[0];
    /* retail threads `addiu $5,$5,1` (j++) into the `bnel` slot and puts
       `addiu $7,$7,6` after it; `it++` as the last statement of the BODY
       threads the pointer instead and swaps the two words. */
    for (j = 0; j < 100; j++, it++) {
        if (it->m0 == key) {
            e = it;
            break;
        }
    }
    if (e == 0) return 0;
    a = e->m2;
    if (a < 0 || (b = e->m4) < 0) return 0;
    *out = b - a + 1;
    return p->m8C + e->m2 * 28;
}
