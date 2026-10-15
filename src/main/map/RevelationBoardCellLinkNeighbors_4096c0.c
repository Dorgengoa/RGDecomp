#include "types.h"

extern s32 RevelationBoardGetCell_409910(s32, s32, s32);
extern s32 RevelationBoardCellSetLinkDir_409aa0(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 RevelationBoardCellLinkNeighbors_4096c0(s32 p0, s32 p1, s32 p2)
{
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 r4;
    s32 r5;
    s32 r6;
    s32 r7;
    s32 rv9;
    s32 r8;
    s32 rv13;
    s32 r10;
    s32 r11;
    s32 r12;
    s32 rv15;
    s32 r14;
    s32 rv19;
    s32 r16;
    s32 r17;
    s32 r18;
    s32 rv23;
    s32 r20;
    s32 r21;
    s32 r22;
    s32 rv25;
    s32 r24;
    s32 rv29;
    s32 r26;
    s32 r27;
    s32 r28;
    s32 rv31;
    s32 r30;

    r0 = RevelationBoardGetCell_409910(p0, (p1 + -1), (p2 + -1));
    r1 = RevelationBoardGetCell_409910(p0, (p1 + -1), p2);
    r2 = RevelationBoardGetCell_409910(p0, (p1 + -1), (p2 + 1));
    r3 = RevelationBoardGetCell_409910(p0, p1, (p2 + -1));
    r4 = RevelationBoardGetCell_409910(p0, p1, (p2 + 1));
    r5 = RevelationBoardGetCell_409910(p0, (p1 + 1), (p2 + -1));
    r6 = RevelationBoardGetCell_409910(p0, (p1 + 1), p2);
    r7 = RevelationBoardGetCell_409910(p0, (p1 + 1), (p2 + 1));
    rv9 = r7;
    if (r0 != 0) {
        r8 = RevelationBoardCellSetLinkDir_409aa0(r0, 7, 1);
        rv9 = r8;
    }
    rv13 = rv9;
    if (r1 != 0) {
        r10 = RevelationBoardCellSetLinkDir_409aa0(r1, 5, 1);
        r11 = RevelationBoardCellSetLinkDir_409aa0(r1, 6, 1);
        r12 = RevelationBoardCellSetLinkDir_409aa0(r1, 7, 1);
        rv13 = r12;
    }
    rv15 = rv13;
    if (r2 != 0) {
        r14 = RevelationBoardCellSetLinkDir_409aa0(r2, 5, 1);
        rv15 = r14;
    }
    rv19 = rv15;
    if (r3 != 0) {
        r16 = RevelationBoardCellSetLinkDir_409aa0(r3, 2, 1);
        r17 = RevelationBoardCellSetLinkDir_409aa0(r3, 4, 1);
        r18 = RevelationBoardCellSetLinkDir_409aa0(r3, 7, 1);
        rv19 = r18;
    }
    rv23 = rv19;
    if (r4 != 0) {
        r20 = RevelationBoardCellSetLinkDir_409aa0(r4, 0, 1);
        r21 = RevelationBoardCellSetLinkDir_409aa0(r4, 3, 1);
        r22 = RevelationBoardCellSetLinkDir_409aa0(r4, 5, 1);
        rv23 = r22;
    }
    rv25 = rv23;
    if (r5 != 0) {
        r24 = RevelationBoardCellSetLinkDir_409aa0(r5, 2, 1);
        rv25 = r24;
    }
    rv29 = rv25;
    if (r6 != 0) {
        r26 = RevelationBoardCellSetLinkDir_409aa0(r6, 0, 1);
        r27 = RevelationBoardCellSetLinkDir_409aa0(r6, 1, 1);
        r28 = RevelationBoardCellSetLinkDir_409aa0(r6, 2, 1);
        rv29 = r28;
    }
    rv31 = rv29;
    if (r7 != 0) {
        r30 = RevelationBoardCellSetLinkDir_409aa0(r7, 0, 1);
        rv31 = r30;
    }
    return 1;
}
