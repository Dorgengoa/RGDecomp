#include "types.h"

/* title.bin overlay, 0x004EC030 -- load the title screen's archives and hand
 * the decoded pieces to the three display objects.
 *
 * Reads either a single archive (when func_207F20() reports the alternate
 * path) or two from the gp table at D_004803C0, then builds the two sprite
 * objects and the model object from func_42C500/func_42C040 records.
 *
 * D_004803C0 is declared `[2]` deliberately: at 8 bytes it is under mwcc's
 * small-data threshold and takes `addiu $2, $28, %gp_rel(...)`, which is what
 * the reference has.  Sized [4] it would be 16 bytes, over the threshold, and
 * compile to `lui`/`%lo`.  The declared size is a RELOCATION CONTROL here, not
 * a bound.
 *
 * ⚠ func_207F20 takes NO arguments.  m2c gives it two at 0x004EC4F4 because
 * $4 and $5 still hold the preceding bitfield insert's operands.
 *
 * The `bgez / sra 4 / addiu 0xF / sra 4` block is just a signed divide by 16;
 * writing it out longhand as m2c does is the same code.
 *
 * THREE THINGS MOVED THIS FROM `len` TO BYTE-IDENTICAL, in order of value:
 *  1. The 14-bit field at +0xA has to be read into a LOCAL before the call it
 *     precedes.  Left inline in the argument list mwcc computes the
 *     `lhu / dsll32 / dsrl32` triple AFTER the call; retail computes it before
 *     and holds it in a callee-saved register.  Worth 6 words across the three
 *     identical blocks.
 *  2. `dev` must be assigned AFTER `func_207DF0()`, not before.  Assigned
 *     first its live range crosses the call, so it needs a callee-saved
 *     register and the later field writes go through that; retail re-loads the
 *     global into `$5` after the call and never keeps it across one.  Write
 *     `t = func_207DF0(); dev = D_0048415C; dev->field018 = t;`.
 *     ⚠ `volatile` on the extern does NOT do this -- the value was never CSE'd
 *     across a call, it was simply live too early.
 *  3. ★ THAT REORDER THEN COSTS 40 WORDS OF PURE REGISTER NAMING, and the fix
 *     is the DECLARATION ORDER of the pointer locals.  Once `dev` stops
 *     needing a callee-saved register the whole pool shifts one place; the
 *     pointers are handed $19, $18, $17, $16 in DECLARATION order, so `buf`
 *     has to be declared first to land in $19.  Moving `dev`'s own
 *     declaration does nothing -- it is the surviving callee-saved locals'
 *     order that matters.
 */

typedef struct Rec_title_FUN_004ec030 {
    u8 pad000[0x4];
    s32 field004;
    u8 pad008[0x2];
    u16 bits00A_0 : 2;
    u16 field00A : 14;             /* (v << 48) >>> 50 == bits 2..15 */
} Rec_title_FUN_004ec030;

typedef struct Wk_title_FUN_004ec030 {
    u8 pad000[0x8];
    s32 field008;
} Wk_title_FUN_004ec030;

typedef struct Dev_title_FUN_004ec030 {
    u8 pad000[0x18];
    s32 field018;
    u8 pad01C[0x4];
    u8 bit020 : 1;
    u8 field021;
} Dev_title_FUN_004ec030;

typedef struct Blk_title_FUN_004ec030 {
    u8 pad000[0x7C];
} Blk_title_FUN_004ec030;

extern s32 D_004802CC;
extern s32 D_004803A0;
extern u8 D_004803A4;
extern s32 D_004803C0[2];
extern const u8 D_004B2570;
extern void *D_00484150;
extern void *D_00484158;
extern void *D_0048415C;
extern Wk_title_FUN_004ec030 *D_00484170;
extern void *D_00484174;
extern s32 D_00484180;
extern const u8 D_004F1550;
extern const u8 D_004F1570;
extern const u8 D_004F1590;
extern const u8 D_004F15B0;
extern const u8 D_004F15C8;
extern const u8 D_004F15E0;

extern void func_1319A8(void *dst, void *src, s32 n);
extern void func_14D8E0(void *a);
extern void *func_14DA10(void *a, s32 n);
extern void func_14DAD0(void *a);
extern void *func_14DB10(void *a, s32 b, s32 c, s32 d);
extern void func_14DCB0(void *a, void *b);
extern void func_15DE40(void);
extern void func_1849E0(const void *a);
extern s32 func_1C2800(void *a, const void *b, s32 *n);
extern s32 func_1C2860(s32 a, void *b, s32 *n);
extern void *func_2025E0(void);
extern s32 func_202A50(void *a, const void *b, void *c);
extern void func_202BE0(void *a, const void *b, void *c, s32 d, s32 e);
extern void *func_206A40(void);
extern s32 func_207DF0(void);
extern s32 func_207F20(void);
extern void func_28E0C0(void *a, void *b, s32 c);
extern void func_28EB70(void *a, s32 b, void *c);
extern void func_28EC80(void *a);
extern void func_28EDE0(void *a, s32 b, s32 c);
extern void func_28F670(void *a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g);
extern void func_28F970(void *a, s32 b, s32 c, s32 d, s32 e);
extern void func_2901D0(void *a, s32 b, s32 c, s32 d);
extern void func_290390(void *a, void *b, s32 c);
extern void func_290450(void *a);
extern void func_2912E0(void *a);
extern void func_373110(s32 a, s32 b);
extern s32 func_373150(void);
extern void func_376B40(void *a, s32 b, s32 c);
extern void func_37BBD0(void *a, void *b);
extern void func_42B840(void *a, s32 b, s32 c, void *d, void *e);
extern Rec_title_FUN_004ec030 *func_42C040(void *a, s32 b);
extern Rec_title_FUN_004ec030 *func_42C500(void *a, s32 b);
extern s32 title_TitleDemoPvRowEnabledMaybe_4ed340(void);
extern void title_TitleSaveIconDataSet_4ede80(void *a);
extern void title_TitleEnablePadCheck_4f13e0(void);

s32 title_TitleStateLoadRes_4ec030(void)
{
    Blk_title_FUN_004ec030 blk;
    s32 size;
    Rec_title_FUN_004ec030 *r;
    void *buf;
    void *arch;
    void *fs;
    void *disc;
    void *mem;
    s32 id;
    s32 bits;
    s32 i;
    Dev_title_FUN_004ec030 *dev;

    func_15DE40();
    buf = 0;
    arch = func_206A40();
    disc = func_2025E0();
    if (disc != 0) {
        buf = func_14DB10(disc, 2, 0, 0x40);
        func_14DAD0(disc);
        func_14DCB0(disc, buf);
    }
    fs = D_00484150;
    if (func_207F20() != 0) {
        func_14D8E0(fs);
        if (func_1C2860(D_004802CC, buf, &size) != 0) {
            func_1849E0(&D_004B2570);
            func_42B840(arch, 2, 0xD, fs, buf);
            func_1849E0(&D_004B2570);
            D_00484180 = func_202A50(buf, &D_004F1550, fs);
            func_1849E0(&D_004B2570);
            func_202BE0(buf, &D_004F1570, fs, 0x32D, 0);
            func_202BE0(buf, &D_004F1590, fs, 0x32D, 0);
            func_202BE0(buf, &D_004F15B0, fs, 0x32D, 0);
            func_1849E0(&D_004B2570);
        }
    } else {
        i = 0;
        do {
            func_14D8E0(fs);
            if (func_1C2860(D_004803C0[i], buf, &size) != 0) {
                func_1849E0(&D_004B2570);
                if (i == 1) {
                    func_42B840(arch, 2, 0xD, fs, buf);
                    func_1849E0(&D_004B2570);
                    func_376B40(fs, func_1C2800(buf, &D_004F15C8, &size), size);
                    func_1849E0(&D_004B2570);
                    D_00484180 = func_202A50(buf, &D_004F1550, fs);
                    func_1849E0(&D_004B2570);
                    func_202BE0(buf, &D_004F1570, fs, 0x32D, 0);
                    func_202BE0(buf, &D_004F1590, fs, 0x32D, 0);
                    func_202BE0(buf, &D_004F15E0, fs, 0x32D, 0);
                    func_1849E0(&D_004B2570);
                } else {
                    mem = func_14DA10(fs, size / 16 + 1);
                    if (mem != 0) {
                        func_1319A8(mem, buf, size);
                        func_37BBD0(&blk, mem);
                        title_TitleSaveIconDataSet_4ede80(&blk);
                        func_1849E0(&D_004B2570);
                    }
                }
            }
            i = i + 1;
        } while (i < 2);
    }
    D_004803A4 = 1;
    r = func_42C500(arch, 0xD);
    id = r->field004;
    bits = r->field00A;
    func_2912E0(D_00484170);
    func_290390(D_00484170, D_00484150, bits);
    func_2901D0(D_00484170, id, 0, 0);
    D_00484170->field008 = 0x32D;
    func_290450(D_00484170);
    if (title_TitleDemoPvRowEnabledMaybe_4ed340() != 0) {
        func_28F970(D_00484170, 0x63, 0, 0x127, 0);
        func_28F970(D_00484170, 0x64, 0, 0x9C, 0);
        func_28F670(D_00484170, 0x64, 0x200, 0x8A, 0x200, 0x8A, 0);
    } else {
        func_28F970(D_00484170, 0x63, 0, 0x9C, 0);
        func_28F970(D_00484170, 0x64, 0, 0x126, 0);
        func_28F670(D_00484170, 0x64, 0x200, 0x9A, 0x200, 0x9A, 0);
    }
    r = func_42C500(arch, 0xC);
    id = r->field004;
    bits = r->field00A;
    func_2912E0(D_00484174);
    func_290390(D_00484174, D_00484150, bits);
    func_2901D0(D_00484174, id, 0, 0);
    ((Wk_title_FUN_004ec030 *)D_00484174)->field008 = 0x32D;
    func_290450(D_00484174);
    r = func_42C040(arch, 9);
    id = r->field004;
    bits = r->field00A;
    func_28EC80(D_0048415C);
    func_28E0C0(D_0048415C, D_00484150, bits);
    func_28EB70(D_0048415C, id, D_00484170);
    id = func_207DF0();
    dev = D_0048415C;
    dev->field018 = id;
    dev->bit020 = 0;
    dev->field021 = 0;
    if (func_207F20() != 0) {
        func_373110(0, 0);
        func_373110(0, 1);
    }
    if (func_373150() != 0 && func_207F20() == 0) {
        func_28EDE0(D_00484158, 0xE, 1);
    } else {
        func_28EDE0(D_00484158, 4, 1);
    }
    D_004803A0 = -1;
    title_TitleEnablePadCheck_4f13e0();
    return 1;
}
