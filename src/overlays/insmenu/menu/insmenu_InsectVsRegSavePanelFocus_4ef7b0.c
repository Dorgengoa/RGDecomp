#include "types.h"

/* insmenu 0x004EF7B0 -- the 004F0A00 family again, but with SIX contiguous
 * cases (0x264..0x269), which mwcc compiles to a real JUMP TABLE:
 *   addiu $2, $2, -0x264 / sltiu $1, $2, 0x6 / beql / lui %hi(jtbl_004F9FD0)
 * Four flag bits are counted (1, 2 and 3, starting from 1) and the multiplier
 * is the literal 57.
 *
 * !! THIS UNIT IS EXPECTED TO BE UNADMISSIBLE, AND THE REASON IS STRUCTURAL,
 * NOT A MATCHING PROBLEM: retail's `jtbl_004F9FD0` already exists in the
 * overlay's own data assembly (asm/overlays/insmenu/data/insmenu_data.data.s
 * at 0x004F9FD0), while a compiled switch emits its OWN table into the
 * object's read-only data -- which olink's lcf collects into .data.  The
 * overlay would then carry the table twice and every byte after it shifts.
 * See the write-up in overlay-c-pipeline.md; this file is the measurement.
 *
 * RE-MEASURED 2026-08-26 (L3): 122/122 words BYTE-IDENTICAL, bad = 0, on the
 * standard overlay scorer (build/dv_osbuild.py insmenu, which applies
 * x_jtbl.retarget exactly as x_olink does).  Two independent artefacts agree:
 * build/i_knob_batch2.log block 7 records baseline bad = 0 as well.  So this is
 * NOT a matching residue and never was -- it is a DECLINED TOOL PORT.
 * scripts/f_jtbl.py / scripts/x_jtbl.py exist for factory and insect; insmenu
 * has exactly two jump-table functions, this one (488 B) and 004ea600 (524 B),
 * so the port is worth 1,012 B and this unit is already paid for.
 */

typedef struct {
    s16 field00;
    s16 field02;
    u8 pad04[2];
    s16 field06;
    u8 pad08[2];
    s16 field0A;
    u8 pad0C[6];
    s16 field12;
} Panel;

typedef struct {
    s32 field00;
    u8 bit0 : 1;
    u8 bit1 : 1;
    u8 bit2 : 1;
    u8 bit3 : 1;
} Item;

typedef struct {
    u8 pad00[0x24];
    void *field24;
} Handle;

extern const u8 D_004FA1A0[];
extern const u8 D_004FA180[];
extern const s32 D_004F99C0[];

extern void func_28EA90(const void *a, s32 b, s32 c);
extern Panel *func_28EC60(const void *a);
extern Handle *func_1FEDE0(void);
extern Item *func_430AF0(void *a);
extern u8 insmenu_InsectVsTakeCancelFlag_4ea0d0(void);
extern void func_290F60(const void *a, s32 b, s32 c, s32 d);
extern void func_2907A0(const void *a, s32 b, f32 t);
extern void insmenu_InsectVsListSetRowColors_4ea110(s32 a, s32 b, s32 c);
extern void insmenu_InsectVsRegSavePanelBright_4efae0(void);
extern void insmenu_InsectVsRegSaveCursorFadeIn_4efa90(void);

void insmenu_InsectVsRegSavePanelFocus_4ef7b0(void)
{
    Panel *p;
    Item *h;
    s32 n;
    s32 k;

    func_28EA90(D_004FA1A0, 0x7535, 0);
    p = func_28EC60(D_004FA1A0);
    p->field06 = 0x39;
    p->field0A = 4;
    h = func_430AF0(func_1FEDE0()->field24);
    n = 1;
    if (h != 0) {
        if (h->bit1) {
            n++;
        }
        if (h->bit2) {
            n++;
        }
        if (h->bit3) {
            n++;
        }
        p->field0A = n;
    }
    if (insmenu_InsectVsTakeCancelFlag_4ea0d0() == 0) {
        k = 0;
        if (h != 0) {
            h->field00 = D_004F99C0[n];
            switch (h->field00) {
            case 0x264:
                k = 0;
                break;
            case 0x265:
                k = 1;
                break;
            case 0x266:
                k = 2;
                break;
            case 0x267:
                k = 3;
                break;
            case 0x268:
                k = 4;
                break;
            case 0x269:
                k = 4;
                break;
            }
        }
        p->field12 = k;
        func_290F60(D_004FA180, 0x29, p->field00, p->field02 + p->field12 * 57);
        func_290F60(D_004FA180, 0x26, 0, p->field12 * 57);
        func_2907A0(D_004FA180, 0x26, 1.0f);
    }
    insmenu_InsectVsRegSavePanelBright_4efae0();
    insmenu_InsectVsListSetRowColors_4ea110(0x4E, 5, n);
    insmenu_InsectVsRegSaveCursorFadeIn_4efa90();
}
