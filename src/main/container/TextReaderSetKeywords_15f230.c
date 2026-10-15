#include "types.h"

extern void BuildKeywordHashTable_15f270(s32, s32);
extern void TextReaderSetCmdCtx_15f220(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void TextReaderSetKeywords_15f230(s32 p0, s32 p1, s32 p2)
{
    BuildKeywordHashTable_15f270(p0, p1);
    TextReaderSetCmdCtx_15f220(p0, p2);
}
