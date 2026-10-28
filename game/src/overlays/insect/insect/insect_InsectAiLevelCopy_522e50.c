/* rgp:protos */
#define RGP_SELF_insect_InsectAiLevelCopy_522e50 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00522E50 -- a 16-byte record copy written out field by field, NOT a
 * struct assignment (that would be one `lq`/`sq`).  The `ld`/`sd` pair at +0x08
 * is one 8-byte member; +0x00..+0x02 are SIGNED (`lb`) and +0x03..+0x07
 * UNSIGNED (`lbu`), which is what names the two halves' types.
 * ⚠ Retail copies +0x06 BEFORE +0x05, so the block is written in retail's
 * emission order rather than ascending offset.
 * insect_InsectAiLevelReset_522ed0 takes ONE argument: 0x00522DE0 marshals only $4
 * (`addu $4,$2,$3`) and sets no $5 in that block. */
typedef struct Rec16 {
    s8 f00, f01, f02;
    u8 f03, f04, f05, f06, f07;
    u64 f08;
} Rec16;

/*rgp*/

void insect_InsectAiLevelCopy_522e50(Rec16 *d, const Rec16 *s)
{
    insect_InsectAiLevelReset_522ed0(d);
    d->f08 = s->f08;
    d->f00 = s->f00;
    d->f01 = s->f01;
    d->f02 = s->f02;
    d->f03 = s->f03;
    d->f04 = s->f04;
    d->f06 = s->f06;
    d->f05 = s->f05;
    d->f07 = s->f07;
}
