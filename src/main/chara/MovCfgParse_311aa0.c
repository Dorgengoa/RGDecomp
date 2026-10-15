#include "types.h"

extern void MovCfgScratchInit_312040(s32, void *, void *);
extern void MovCfgScratchReset_311fd0(void);
extern s32 MovCfgScratchAllocAlign16_311eb0(s32);
extern void TextReaderCtor_15f140(void *);
extern void BuildKeywordHashTable_15f270(void *, void *);
extern void TextReaderOpen_15f1b0(void *, s32, s32);
extern void TextReaderParseAll_15f3f0(void *);
extern void CharaRefInit_312330(void *, s32, s32, s32);
extern s32 GetActionMgr_1fdb50(void);
extern void CharaRefFindOrAdd_234670(s32, void *);
extern void MovCfgScratchFree_312000(void);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004523F0[];
extern s32 D_004829A0;
extern s32 D_004829A8;
extern s32 D_004829AC;

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

s32 MovCfgParse_311aa0(s32 p0, s32 p1, s32 p2)
{
    u128 vF30;
    u128 vF10[2];
    u128 v40[237];
    s32 l0;
    struct Obj1 *l1;
    struct Obj0 *l2;
    s32 t0;
    s32 t1;
    s32 r5;
    s32 r6;
    s32 t2;
    s32 t3;
    s32 t4;
    s32 r12;

    if (p0 == 0) {
        return 0;
    }
    l1 = (struct Obj1 *)vF10;
    l2 = (struct Obj0 *)D_004523F0;
    l0 = 4;
    do {
        l1->m00 = l2->m00;
        l1->m04 = l2->m04;
        l0 = (l0 + -1);
        l2 = (struct Obj0 *)((u8 *)l2 + 8);
        l1 = (struct Obj1 *)((u8 *)l1 + 8);
    } while (l0 > 0);
    MovCfgScratchInit_312040(l0, l1, l2);
    MovCfgScratchReset_311fd0();
    r5 = MovCfgScratchAllocAlign16_311eb0(0x2800);
    D_004829A0 = r5;
    r6 = MovCfgScratchAllocAlign16_311eb0(0x600);
    D_004829A8 = r6;
    if (D_004829A0 == 0 || r6 == 0) {
        return 0;
    }
    TextReaderCtor_15f140(v40);
    BuildKeywordHashTable_15f270(v40, vF10);
    TextReaderOpen_15f1b0(v40, p0, p1);
    TextReaderParseAll_15f3f0(v40);
    t3 = D_004829A8;
    t4 = D_004829AC;
    CharaRefInit_312330(&vF30, p2, t3, t4);
    r12 = GetActionMgr_1fdb50();
    CharaRefFindOrAdd_234670(r12, &vF30);
    MovCfgScratchFree_312000();
    MovCfgScratchReset_311fd0();
    return 1;
}
