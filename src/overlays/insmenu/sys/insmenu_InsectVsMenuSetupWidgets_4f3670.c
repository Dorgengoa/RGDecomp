#include "types.h"

/* insmenu 0x004F3670 -- open the insect-menu screen.  116 instructions, 20
 * calls, ZERO conditional branches; the structural twin of the matched
 * factory_FUN_004EA1D0, and the recipes are read off that file.
 *
 * ★ `lhu 0xA / dsll32 16 / dsrl32 18` is a 14-BIT BITFIELD at bits 2..15.
 * mwcc allocates u16 bitfields from the LSB, so the 2-bit filler is declared
 * FIRST.  Both record members are read BEFORE an intervening call, so each
 * needs its own local; the pair repeats for the second record.
 *
 * ★ The overlay-data globals (D_004FAxxx) are all `const`: _gp is 0x00485170
 * so the gp window is 0x47D170..0x48D170 and none of them is in it.  The three
 * that are WRITTEN take the documented `*(T *)&D_x = v` cast form -- `const`
 * is a RELOCATION control here, not a claim about mutability.
 *
 * ★ D_004FA1C0 bit 0 is a ONE-BIT BITFIELD assigned ZERO: retail keeps the
 * whole insert (`andi $6, $0, 0x1` with $0 as the source operand, `and` with
 * ~1, `or`).  Assigning 1 would have folded to a plain store -- that asymmetry
 * is what identifies it as a bitfield rather than a masked byte write.
 *
 * ★ 0x4B2570 / 0x4B27E0 are unsymbolised main-image data addresses; taken as
 * `&extern` they get %hi/%lo, where a cast integer would compile to lui/ORI.
 * 0xF00C does not fit a signed 16-bit immediate, hence `ori`.
 */

typedef struct Rec {
    u8   pad0[4];
    void *f4;
    u8   pad8[2];
    u16  fA_fill : 2;
    u16  fA : 14;
} Rec;

typedef struct Obj Obj;

typedef struct Flags {
    u8   b0 : 1;
    u8   rest : 7;
} Flags;

extern const u8 D_004FA180[];
extern const u8 D_004FA1A0[];
extern const s32 D_004FA188;
extern const s32 D_004FA1B8;
extern const Flags D_004FA1C0;
extern const u8 D_004FA1C1;
extern const u8 D_004B2570;
extern const u8 D_004B27E0;

extern s32 D_004842E0;      /* gp - 0xE90 */
extern s16 D_004842E8;      /* gp - 0xE88 */
extern s32 D_004842EC;      /* gp - 0xE84 */
extern s32 D_004842F0;      /* gp - 0xE80 */
extern s16 D_00484300;      /* gp - 0xE70 */

extern void *func_206A40(void);
extern Rec  *func_42C500(void *a, s32 b);
extern Rec  *func_42C040(void *a, s32 b);
extern void  func_2912E0(const void *a);
extern void  func_290390(const void *a, void *b, s32 c);
extern void  func_2901D0(const void *a, void *b, s32 c, s32 d);
extern void  func_290450(const void *a);
extern void  func_28EC80(const u8 *p);
extern void  func_28E0C0(const void *a, void *b, s32 c);
extern void  func_28EB70(const void *a, void *b, const void *c);
extern s32   func_207DF0(void);
extern s32   func_42C950(void *ctx, s32 id);
extern void  func_183960(const u8 *p);
extern void  func_183D50(const u8 *p, u32 a, s32 b, s32 c);
extern void  func_183950(const u8 *p, s32 a);
extern void  func_28EDE0(void *a, s32 id, s32 c);
extern void  insmenu_InsectVsPanelsInit_4ee1d0(void);

void insmenu_InsectVsMenuSetupWidgets_4f3670(void)
{
    void *ctx;
    Rec *r;
    void *data;
    s32 id;

    ctx = func_206A40();
    r = func_42C500(ctx, 0x31);
    data = r->f4;
    id = r->fA;
    func_2912E0(D_004FA180);
    func_290390(D_004FA180, (void *)D_004842E0, id);
    func_2901D0(D_004FA180, data, 0, 0);
    *(s32 *)&D_004FA188 = 0x32D;
    func_290450(D_004FA180);

    r = func_42C040(ctx, 0x21);
    data = r->f4;
    id = r->fA;
    func_28EC80(D_004FA1A0);
    func_28E0C0(D_004FA1A0, (void *)D_004842E0, id);
    func_28EB70(D_004FA1A0, data, D_004FA180);

    *(s32 *)&D_004FA1B8 = func_207DF0();
    ((Flags *)&D_004FA1C0)->b0 = 0;
    D_004842EC = 0;
    D_004842F0 = 0;
    *(u8 *)&D_004FA1C1 = 0;
    D_004842E8 = 0;
    D_004842F0 = func_42C950(ctx, 0x20);

    func_183960(&D_004B2570);
    func_183D50(&D_004B2570, 0xF00C, 0xA, 3);
    func_183950(&D_004B2570, 0x78);
    func_183960(&D_004B27E0);
    func_183D50(&D_004B27E0, 0xF00C, 0xA, 3);
    func_183950(&D_004B27E0, 0x78);

    func_28EDE0(&D_004842E8, 0x7531, 1);
    insmenu_InsectVsPanelsInit_4ee1d0();
    D_00484300 = 2;
}
