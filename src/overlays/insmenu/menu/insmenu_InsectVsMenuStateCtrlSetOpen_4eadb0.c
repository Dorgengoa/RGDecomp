/* SESSION 10 (2026-08-26, lane L4): BYTE-IDENTICAL at 165 words.
 * The session-9 park ("2 words, scheduling class, do not sweep further",
 * 488 pragmas + 19 spellings) is OVERTURNED.  The residue was NOT scheduling:
 * retail's `lbu 0x4C6 / lbu 0x4C7 / sb -0xE5C / sb -0xE5B` is BATCHED
 * loads-then-stores, which is ONE sub-struct assignment, not two statements
 * (main-pass34-substructs).  Declaring 0x4C6/0x4C7 as a 2-byte `Pair` member
 * and the gp pair as `extern Pair D_00484314` turns the arm into the single
 * statement `D_00484314 = it->pair;` and every word matches.  A `u8 v[2]`
 * spelling of Pair gives the IDENTICAL object.  Measured negatives on the same
 * round trip: `const Item *` on the pointer is INERT (same object as the
 * baseline), `const` locals score 4, and volatile on a standalone local
 * (one or both) breaks the LENGTH (0x29c / 0x2a4 vs 0x294).
 */
#include "types.h"

/* insmenu 0x004EADB0 (660 bytes, 168 instructions, 28 calls) -- open the
 * detail page for the selected entry.
 *
 * The opening guard is an EARLY RETURN in the positive sense: retail falls
 * through into `D_00484304 = 1; return 1;` and branches away to the body, so
 * the source condition is `!= 0`, not the `== 0` m2c would give.
 *
 * `$16` holds two different locals with disjoint live ranges -- the panel from
 * func_28EC60, then the handle from func_1FEDE0, which is copied into it in
 * func_430BD0's delay slot.  They are two variables, not one.
 *
 * PARKED AT 2 WORDS.  The residue is a single transposition in the bit0 arm:
 * retail issues `lbu $2, 0x4C7($2)` and THEN `sb $3, -0xE5C($28)`, we issue
 * them the other way round.  Everything else, including which byte lands in
 * $2 and which in $3 and which store fills insmenu_InsectVsCtrlSetRefreshRows_4eb050's delay slot,
 * is right.  Nine spellings measured, all 165 words: the 2x2 of load-statement
 * order x store-statement order (4 / 2 / 4 / 2 -- the LOAD order changes
 * nothing and the STORE order picks the registers, the same asymmetry
 * 004EB230 records for struct members), one local instead of two in either
 * position (4 / 2), no locals at all (2, this file), and the two gp bytes
 * declared as a 2-element array (2).  Scheduling class; do not sweep further.
 *
 * The two counters written through `dsll32 16 / dsra32 16` before their uses
 * are s16 LOCALS: that pair is mwcc re-normalising a narrow local, exactly the
 * cost the s8 rule warns about -- and here retail pays it, so the type is real.
 */

typedef struct Panel Panel;
struct Panel {
    s16 field00;
    s16 field02;
    u8 pad04[0xE];
    s16 field12;
};

typedef struct Handle Handle;
struct Handle {
    u8 pad00[0x24];
    void *field24;
};

typedef struct Pair Pair;
struct Pair { u8 a; u8 b; };

typedef struct Item Item;
struct Item {
    s32 field00;
    u8 bit0 : 1;
    u8 pad05[0x4C1];
    Pair pair;
};

extern const u8 D_004FA180[];
extern const u8 D_004FA1A0[];
extern const u8 D_004B27E0[];
extern s32 D_004842FC;      /* gp - 0xE74 */
extern u8 D_00484304;       /* gp - 0xE6C */
extern Pair D_00484314;     /* gp - 0xE5C */
extern u8 D_004842E8;       /* gp - 0xE88, passed by address */
extern f32 D_0047D488;

extern s32 insmenu_InsectVsTwoPlayerPanelIsVisible_4f1b20(void);
extern void insmenu_InsectVsFrameSetTintMaybe_4ea290(s32 a, s32 b, f32 t);
extern void *func_28FE10(const void *a, s32 b, s32 c);
extern void func_28BBB0(void *a, s32 b, s32 c);
extern void func_290010(const void *a, s32 b, s32 c, s32 d);
extern void func_290690(const void *a, s32 b, f32 x, f32 y, f32 z);
extern void func_290F60(const void *a, s32 b, s32 c, s32 d);
extern void func_28EA90(const void *a, s32 b, s32 c);
extern Panel *func_28EC60(const void *a);
extern Handle *func_1FEDE0(void);
extern void func_430BD0(void *a, s32 b);
extern void func_28FC30(const void *a, s32 b, s32 c, s32 d, s32 e);
extern s32 func_28AA30(s32 a, s32 b);
extern void func_28F510(const void *a, s32 b, s32 c, s32 d);
extern Item *func_430B70(void *a);
extern void insmenu_InsectVsCtrlSetRefreshRows_4eb050(void);
extern void func_28F930(const void *a, s32 b, s32 c, s32 d);
extern s32 func_184960(const void *a);
extern void func_28EDE0(void *a, s32 b, s32 c);

s32 insmenu_InsectVsMenuStateCtrlSetOpen_4eadb0(void)
{
    Panel *p;
    Handle *hnd;
    Item *it;
    s16 label;
    s16 pos;

    if (insmenu_InsectVsTwoPlayerPanelIsVisible_4f1b20() != 0) {
        D_00484304 = 1;
        return 1;
    }
    D_00484304 = 0;
    insmenu_InsectVsFrameSetTintMaybe_4ea290(0xC, 0x28, 2.0f);
    func_28BBB0(func_28FE10(D_004FA180, 0xC, 0), 0x118, 0x28);
    func_290010(D_004FA180, 0xA, 1, -1);
    func_290690(D_004FA180, 0xA, 1.0f, D_0047D488, 0.0f);
    func_290F60(D_004FA180, 0xA, 0x26, 0x50);
    func_28EA90(D_004FA1A0, 0x7533, 1);
    p = func_28EC60(D_004FA1A0);
    func_290F60(D_004FA180, 0xF, p->field00, p->field02);
    hnd = func_1FEDE0();
    func_430BD0(hnd->field24, p->field12);
    func_28FC30(D_004FA180, 0xB, 0x10C, 0x1C, 0);
    func_290F60(D_004FA180, 0xB, 0, 0);
    func_28F510(D_004FA180, 0xC, func_28AA30(D_004842FC, 6), 0);
    func_28F510(D_004FA180, 0xC, func_28AA30(D_004842FC, 7), 1);
    it = func_430B70(hnd->field24);
    if (it != 0) {
        if (it->bit0) {
            D_00484314 = it->pair;
            insmenu_InsectVsCtrlSetRefreshRows_4eb050();
        } else {
            D_00484314.a = 0;
            func_28F930(D_004FA180, 0x44, 0xE8, 1);
            func_28F510(D_004FA180, 0xC, func_28AA30(D_004842FC, 8), 2);
            D_00484314.b = 0;
            label = 8;
            pos = 0xE8;
            if (func_184960(D_004B27E0) != 0) {
                D_00484314.b = 1;
                label = 9;
                pos = 0x104;
            }
            func_28F930(D_004FA180, 0x44, pos, 2);
            func_28F510(D_004FA180, 0xC, func_28AA30(D_004842FC, label), 3);
        }
    }
    func_28EDE0(&D_004842E8, 0x7538, 0);
    return 1;
}
