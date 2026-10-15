#include "types.h"

/* insmenu 0x004EA600 (524 bytes, 131 instructions) -- the help-caption layout
 * table.  A compiled `switch` over the page kind (jtbl_004F9FB0, 7 entries,
 * index 0 = default) selecting a set of s16 geometry writes on the widget
 * returned by func_28FE10(D_004FA180, 0x39, 0).
 *
 * The `bnel`/`bne` PAST the arm inside case 6 is an if/else-if chain written in
 * source order (0x259, 0x263 || 0x267, 0x26D, 0x277); the `beql` INTO the arm
 * at 0x004EA784 with the shared `$4 = 0x100` in its delay slot is the `||`
 * join, not a second switch.
 *
 * !! DO NOT ADD TO config/ocunits/insmenu.txt UNTIL scripts/i_olink.py RUNS A
 * JUMP-TABLE RETARGET.  This object emits its own 28-byte `.rodata` table
 * (7 words, an internal @N label) plus a `.rel.rodata`; i_olink's lcf collects
 * `*(.rodata)` into .data (scripts/i_olink.py:232), so the table would be
 * APPENDED instead of reusing retail's jtbl_004F9FB0 at 0x004F9FB0 -- a WRONG
 * image.  The tool exists for the sibling overlays (scripts/f_jtbl.py,
 * scripts/x_jtbl.py) and the port to insmenu was DECLINED, not measured.
 * insmenu's whole jtbl class is 2 functions: this one (524 B) and
 * insmenu_InsectVsRegSavePanelFocus_4ef7b0 (488 B, already at bad=0), i.e. 1,012 B behind one port.
 *
 * BYTE-IDENTICAL at 131 words (declared 0x20C / 4 = 131), scored by
 * build/dv_osbuild.py insmenu --tag im07 (which retargets the table onto
 * retail's before comparing) on 2026-08-26.  Matched on the FIRST build.
 */

typedef struct Cell Cell;
struct Cell {
    u8  pad000[0x6A];
    s16 field06A;
    u8  pad06C[0x14];
    s16 field080;
    u8  pad082[0x6];
    s16 field088;
    u8  pad08A[0x16];
    s16 field0A0;
    u8  pad0A2[0x6];
    s16 field0A8;
    u8  pad0AA[0x16];
    s16 field0C0;
    u8  pad0C2[0xA];
    s16 field0CC;
    s16 field0CE;
    u8  pad0D0[0x10];
    s16 field0E0;
    u8  pad0E2[0x1E];
    s16 field100;
};

typedef struct Node Node;
struct Node {
    s32 field00;
    u8  pad04[0x4];
    s32 field08;
};

typedef struct Sys Sys;
struct Sys {
    u8    pad0000[0x1188];
    Node *field1188;
};

typedef struct Handle Handle;
struct Handle {
    u8   pad00[0x24];
    Sys *field24;
};

extern const u8 D_004FA180[];

extern Handle *func_1FEDE0(void);
extern Cell *func_28FE10(const void *a, s32 b, s32 c);

void insmenu_InsectVsTitleBannerLayout_4ea600(void)
{
    Handle *hnd;
    Node *n;
    Cell *c;
    s32 kind;
    s32 code;

    hnd = func_1FEDE0();
    n = hnd->field24->field1188;
    kind = n->field00;
    code = n->field08;
    c = func_28FE10(D_004FA180, 0x39, 0);
    if (c == 0) {
        return;
    }
    c->field0CC = 0x14;
    c->field0CE = 0xE;
    c->field0E0 = -1;
    switch (kind) {
    case 1:
    case 2:
        if (code == 0xCA) {
            c->field06A = 0xC8;
            c->field080 = 0xE2;
            c->field088 = 0x78;
            c->field0A0 = 0x120;
            c->field0A8 = 0x5C;
            c->field0CE = 0;
            c->field0CC = 0;
            c->field0E0 = 0xFD;
            c->field100 = 0xFD;
        } else {
            c->field06A = 0x58;
            c->field080 = -1;
        }
        break;
    case 3:
        c->field06A = 0x74;
        c->field080 = 0xE8;
        c->field088 = 0x5C;
        c->field0A0 = 0x116;
        c->field0A8 = 0x5C;
        c->field0C0 = 0x103;
        break;
    case 4:
        c->field06A = 0x90;
        c->field080 = 0xE8;
        c->field088 = 0x5C;
        c->field0A0 = 0x116;
        c->field0A8 = 0x78;
        c->field0C0 = 0x103;
        break;
    case 5:
        c->field06A = 0xAC;
        c->field080 = 0xE8;
        c->field088 = 0x78;
        c->field0A0 = 0x116;
        c->field0A8 = 0x78;
        c->field0C0 = 0x103;
        break;
    case 6:
        if (code == 0x259) {
            c->field06A = 0xE4;
            c->field080 = -1;
        } else if ((code == 0x263) || (code == 0x267)) {
            c->field06A = 0x100;
            c->field080 = -1;
        } else if (code == 0x26D) {
            c->field06A = 0x11C;
            c->field080 = 0x116;
            c->field088 = 0x94;
            c->field0A0 = -1;
        } else if (code == 0x277) {
            c->field06A = 0x138;
            c->field080 = 0x126;
            c->field088 = 0xB0;
            c->field0A0 = -1;
        }
        break;
    }
}
