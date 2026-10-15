#include "types.h"

/* title.bin overlay, 0x004EF3F0 -- toggle one options-screen row.
 *
 * `row` picks one of ten setting writers on the options object and `on` picks
 * both the value written and which of the row's two help-text ids is shown.
 * The two title_TitleOptionsHighlightPair_4ef890 ids are always the pair (2*row+0x4C, +1) in one
 * order or the other, which is what makes every arm a mirror of its sibling.
 *
 * ⚠ m2c reads these calls as taking FOUR arguments.  They take two: $6 and $7
 * still hold the dispatch chain's own case constants, and m2c cannot tell a
 * live leftover from an argument.  Read $4/$5 off the reference instead.
 *
 * ★ The chain CSEs its case constants into the arms -- `func_3D5FE0(x, 1)` in
 * case 1 reuses the `1` the `b == 1` test materialised, and case 6's `2` and
 * case 7's `4` come from later tests' constants.  Nothing to write for it; it
 * only matters when reading the reference, where an argument that is never
 * materialised in its own block looks like a missing instruction.
 */

typedef struct Options {
    u8 pad0[0xC];
    void *fC;
} Options;

extern Options *func_1FEDE0(void);
extern void func_1FE350(void);
extern void func_3D5F60(void *a, s32 b);
extern void func_3D5F80(void *a, s32 b);
extern void func_3D5FA0(void *a, s32 b);
extern void func_3D5FC0(void *a, s32 b);
extern void func_3D5FE0(void *a, s32 b);
extern void func_3D6000(void *a, s32 b);
extern void func_3D6040(void *a, s32 b);
extern void func_3D6060(void *a, s32 b);
extern void func_3D6080(void *a, s32 b);
extern void func_3D6160(void *a, s32 b);
extern void title_TitleOptionsHighlightPair_4ef890(s32 a, s32 b);

s32 title_TitleOptionsToggle_4ef3f0(s32 on, s32 row)
{
    Options *o;

    o = func_1FEDE0();
    if (row == 0) {
        if (on == 0) {
            func_3D6080(o->fC, 1);
            title_TitleOptionsHighlightPair_4ef890(0x4C, 0x4D);
        } else {
            func_3D6080(o->fC, 0);
            title_TitleOptionsHighlightPair_4ef890(0x4D, 0x4C);
        }
    } else if (row == 1) {
        if (on == 0) {
            func_3D5FE0(o->fC, 1);
            title_TitleOptionsHighlightPair_4ef890(0x4E, 0x4F);
        } else {
            func_3D5FE0(o->fC, 0);
            title_TitleOptionsHighlightPair_4ef890(0x4F, 0x4E);
        }
    } else if (row == 2) {
        if (on == 0) {
            func_3D6160(o->fC, 0);
            title_TitleOptionsHighlightPair_4ef890(0x50, 0x51);
        } else {
            func_3D6160(o->fC, 1);
            title_TitleOptionsHighlightPair_4ef890(0x51, 0x50);
        }
    } else if (row == 3) {
        if (on == 0) {
            func_3D5FC0(o->fC, 1);
            title_TitleOptionsHighlightPair_4ef890(0x52, 0x53);
        } else {
            func_3D5FC0(o->fC, 0);
            title_TitleOptionsHighlightPair_4ef890(0x53, 0x52);
        }
    } else if (row == 4) {
        if (on == 0) {
            func_3D5F80(o->fC, 1);
            title_TitleOptionsHighlightPair_4ef890(0x54, 0x55);
        } else {
            func_3D5F80(o->fC, 0);
            title_TitleOptionsHighlightPair_4ef890(0x55, 0x54);
        }
    } else if (row == 5) {
        if (on == 0) {
            func_3D5FA0(o->fC, 1);
            title_TitleOptionsHighlightPair_4ef890(0x56, 0x57);
        } else {
            func_3D5FA0(o->fC, 0);
            title_TitleOptionsHighlightPair_4ef890(0x57, 0x56);
        }
    } else if (row == 6) {
        if (on == 0) {
            func_3D6060(o->fC, 0);
            title_TitleOptionsHighlightPair_4ef890(0x58, 0x59);
        } else {
            func_3D6060(o->fC, 2);
            title_TitleOptionsHighlightPair_4ef890(0x59, 0x58);
        }
    } else if (row == 7) {
        if (on == 0) {
            func_3D6040(o->fC, 0);
            title_TitleOptionsHighlightPair_4ef890(0x5A, 0x5B);
        } else {
            func_3D6040(o->fC, 4);
            title_TitleOptionsHighlightPair_4ef890(0x5B, 0x5A);
        }
    } else if (row == 8) {
        if (on == 0) {
            func_3D5F60(o->fC, 1);
            title_TitleOptionsHighlightPair_4ef890(0x5C, 0x5D);
        } else {
            func_3D5F60(o->fC, 0);
            title_TitleOptionsHighlightPair_4ef890(0x5D, 0x5C);
        }
    } else if (row == 9) {
        if (on == 0) {
            func_3D6000(o->fC, 1);
            title_TitleOptionsHighlightPair_4ef890(0x5E, 0x5F);
        } else {
            func_3D6000(o->fC, 0);
            title_TitleOptionsHighlightPair_4ef890(0x5F, 0x5E);
        }
    }
    func_1FE350();
    return 1;
}
