#include "types.h"

extern void DynClothDefInit_169420(void *);
extern void TextReaderCtor_15f140(void *);
extern void BuildKeywordHashTable_15f270(void *, void *);
extern void TextReaderOpen_15f1b0(void *, s32, s32);
extern void TextReaderParseAll_15f3f0(void *);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0044A280[];
extern struct Obj0 * D_00481154;
extern s32 D_00481158;
extern s32 D_0048115C;
extern s32 D_00481160;
extern s32 D_00481164;
extern s32 D_00481168;
extern s32 D_0048116C;
extern s32 D_00481170;
extern s32 D_00481174;

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
};

void DynClothCfgParse_167350(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    u128 v60[237];

    DynClothDefInit_169420(p0);
    D_00481158 = p4;
    D_00481154 = p0;
    D_0048115C = p3;
    D_00481160 = 0;
    D_00481164 = 0;
    D_00481168 = 0;
    D_0048116C = 0;
    D_00481170 = 0;
    D_00481174 = 0;
    if (p3 != 0) {
        p0->m04 = p3;
        TextReaderCtor_15f140(v60);
        BuildKeywordHashTable_15f270(v60, D_0044A280);
        TextReaderOpen_15f1b0(v60, p1, p2);
        TextReaderParseAll_15f3f0(v60);
    }
}
