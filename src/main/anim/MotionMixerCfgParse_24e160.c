#include "types.h"

extern void TextReaderCtor_15f140(void *, void *, void *);
extern void BuildKeywordHashTable_15f270(void *, void *);
extern void TextReaderOpen_15f1b0(void *, s32, s32);
extern void TextReaderParseAll_15f3f0(void *);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0044CDD0[];
extern s32 D_00481F44;

struct Obj0;
struct Obj1;

struct Obj0 {
    s32 m00;
    s32 m04;
};

struct Obj1 {
    s32 m00;
    s32 m04;
};

void MotionMixerCfgParse_24e160(s32 p0, s32 p1, s32 p2)
{
    u128 vF10[2];
    u128 v40[237];
    s32 l0;
    struct Obj1 *l1;
    struct Obj0 *l2;

    l1 = (struct Obj1 *)vF10;
    l0 = 3;
    l2 = (struct Obj0 *)D_0044CDD0;
    do {
        l1->m00 = l2->m00;
        l1->m04 = l2->m04;
        l0 = (l0 + -1);
        l1 = (struct Obj1 *)((u8 *)l1 + 8);
        l2 = (struct Obj0 *)((u8 *)l2 + 8);
    } while (l0 > 0);
    TextReaderCtor_15f140(v40, l1, l2);
    D_00481F44 = p2;
    BuildKeywordHashTable_15f270(v40, vF10);
    TextReaderOpen_15f1b0(v40, p0, p1);
    TextReaderParseAll_15f3f0(v40);
    D_00481F44 = 0;
}
