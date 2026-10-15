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

extern u8 D_0044A110[];
extern s32 D_0048112C;
extern s32 D_00481130;
extern s32 D_00481134;
extern s32 D_00481138;
extern s32 D_0048113C;
extern s32 D_00481140;
extern s32 D_00481144;
extern s32 D_00481148;
extern s32 D_0048114C;

void TexAnimeCfgParse_162780(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    u128 v30[237];

    D_00481138 = p0;
    D_00481130 = p4;
    D_0048113C = p3;
    D_00481148 = -1;
    D_00481134 = -1;
    D_0048112C = 0;
    D_00481140 = 0;
    D_00481144 = 0;
    D_0048114C = 0;
    TextReaderCtor_15f140(v30);
    BuildKeywordHashTable_15f270(v30, D_0044A110);
    TextReaderOpen_15f1b0(v30, p1, p2);
    TextReaderParseAll_15f3f0(v30);
}
