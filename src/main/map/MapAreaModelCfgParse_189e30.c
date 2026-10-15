#include "types.h"

extern void TextReaderCtor_15f140(void *);
extern void BuildKeywordHashTable_15f270(void *, void *);
extern void TextReaderOpen_15f1b0(void *, s32, s32);
extern void TextReaderParseAll_15f3f0(void *);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0044A7F0[];
extern s32 D_00481250;
extern s32 D_0048125C;
extern s32 D_004812EC;
extern s32 D_004812F0;

void MapAreaModelCfgParse_189e30(s32 p0, s32 p1, s32 p2, s32 p3)
{
    u128 v30[237];

    D_00481250 = p0;
    D_0048125C = p3;
    D_004812EC = 0;
    D_004812F0 = 0;
    TextReaderCtor_15f140(v30);
    BuildKeywordHashTable_15f270(v30, D_0044A7F0);
    TextReaderOpen_15f1b0(v30, p1, p2);
    TextReaderParseAll_15f3f0(v30);
}
