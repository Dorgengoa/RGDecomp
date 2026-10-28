/* rgp:protos */
#define RGP_SELF_insect_InsectBattlePlayerCursorPick_509b00 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00509B00 -- 352 bytes, 88 instructions, 14 calls, 4 conditional
 * branches, br/ins 0.045.  The drop-target resolver: it reads the cursor's
 * cell, looks the cell up in the board, and picks one of three result codes.
 *
 * ★ x and y are `s32` locals loaded by `lb` from `s8` members.  They pass to
 * insect_InsectCursorSetPageSetCell_511c20's `s32` parameters with no instruction and to
 * insect_InsectBoardGetPiece_4ee9a0's `s16` parameters with a `dsll32 16 / dsra32 16` pair
 * each -- the CALLEE's parameter width is what emits the narrowing, and
 * declaring the locals `s8` would make both calls free and lose four words.
 *
 * `o->f5B28 = NULL;` sits in the following `jal`'s DELAY SLOT because it is
 * written BEFORE the call in the source.
 *
 * ★ The NULL arm passes `4` and its `code` is also 4, so mwcc shares the one
 * register (`daddu $5, $17, $0`); the `code = 2` arm materialises the literal 4
 * separately.  Both sites are the literal in the source -- an argument that
 * arrives as a `move` from another local is a CSE, not a variable.
 *
 * `o->f5EF1` is read AFTER insect_InsectBoardGetPiece_4ee9a0 returns: mwcc cannot sink a
 * member load past a call, so the listing's position is the source's.
 */

typedef struct Card {
    u8 pad00[8];
    s8 f8;                      /* +0x08 */
    s8 f9;                      /* +0x09 */
} Card;

typedef struct Cell {
    u8 pad00[0x71];
    s8 f71;                     /* +0x71 */
} Cell;

typedef struct Ins {
    u8    pad000[0x4960];
    u8    f4960[0x4F90 - 0x4960]; /* +0x4960 */
    u8    f4F90[0x2C];          /* +0x4F90 */
    u8    pad4FBC[0x5B28 - 0x4FBC];
    Cell *f5B28;                /* +0x5B28 */
    u8    pad5B2C[0x5EF1 - 0x5B2C];
    u8    f5EF1;                /* +0x5EF1 */
} Ins;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattlePlayerCursorPick_509b00(Ins *o)
{
    Card *c;
    Cell *p;
    s32 x;
    s32 y;
    s32 kind;
    s32 code;
    s32 m;

    c = ((Card *)insect_InsectCursorSetFindPage_511e60(o->f4F90, 2));
    x = c->f8;
    y = c->f9;
    insect_InsectCursorSetPageSetCell_511c20(o->f4F90, ((Card *)insect_InsectCursorSetFindPage_511e60(o->f4F90, 3)), x, y);
    p = ((Cell *)insect_InsectBoardGetPiece_4ee9a0(o->f4960, x, y));
    kind = o->f5EF1;
    o->f5B28 = NULL;
    if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x80) != 0) {
        insect_InsectBattleClearFlag_50da90(o, 0x34);
        if (p != NULL) {
            if (kind == p->f71) {
                code = 2;
                insect_InsectCursorSetPushPage_511cf0(o->f4F90, 4, 1);
                o->f5B28 = p;
            } else {
                code = 3;
                insect_InsectCursorSetPushPage_511cf0(o->f4F90, 5, 1);
            }
        } else {
            code = 4;
            insect_InsectCursorSetPushPage_511cf0(o->f4F90, 4, 1);
        }
        insect_InsectBattleSetState_50d8c0(o, code, 2, -1);
        insect_InsectBattlePlaySe_4f45b0(o, 5);
    }
    m = insect_InsectCursorSetGetEvents_5119f0(o->f4F90, -1) & 0x900;
    if (m != 0) {
        insect_InsectBattlePlaySe_4f45b0(o, 4);
        insect_InsectBattleCursorNextPiece_4f0bd0(o, 2, 0, 1, m, 0);
    }
}
