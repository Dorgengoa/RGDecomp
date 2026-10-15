#include "types.h"
/* insect 0x00522ED0 -- 40 B / 10 words.  The zero-init ctor for the 16-byte
 * Rec16 whose field-by-field COPY is the already-matching
 * insect_InsectAiLevelCopy_522e50.c; that unit's struct (s8 f00..f02, u8 f03..f07, u64 f08)
 * is reused verbatim, and its `extern void insect_InsectAiLevelReset_522ed0(Rec16 *o)` fixes
 * the arity at ONE argument.
 *
 * The `sd $0, 0x8($4)` sits between the 0x02 and 0x03 byte stores.  Stores
 * through one struct pointer are not reordered against each other, so retail's
 * EMISSION order is the SOURCE order -- the same non-ascending shape
 * insect_InsectAiLevelCopy_522e50 already had to be written in (it copies 0x06 before
 * 0x05).  Transcribed literally rather than sorted. */
typedef struct Rec16 {
    s8  f00, f01, f02;
    u8  f03, f04, f05, f06, f07;
    u64 f08;
} Rec16;

void insect_InsectAiLevelReset_522ed0(Rec16 *o)
{
    o->f00 = 0;
    o->f01 = 0;
    o->f02 = 0;
    o->f08 = 0;
    o->f03 = 0;
    o->f04 = 0;
    o->f05 = 0;
    o->f06 = 0;
    o->f07 = 0;
}
