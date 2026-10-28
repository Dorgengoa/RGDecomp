/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsMenuSetupWidgets_4f3670 1
#include "port/game_protos.h"
#line 1
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
 * ★ insmenu_D_004FA1C0 bit 0 is a ONE-BIT BITFIELD assigned ZERO: retail keeps the
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
    __extension__ unsigned short  fA_fill : 2;
    unsigned short  fA : 14;
} __attribute__((aligned(2))) Rec;

typedef struct Obj Obj;

typedef struct Flags {
    u8   b0 : 1;
    u8   rest : 7;
} Flags;

extern u8 insmenu_D_004FA180[];
extern u8 insmenu_D_004FA1A0[];
extern s32 insmenu_D_004FA188;
extern s32 insmenu_D_004FA1B8;
extern Flags insmenu_D_004FA1C0;
extern u8 insmenu_D_004FA1C1;
extern u8 D_004B2570;
extern u8 D_004B27E0;

extern s32 D_004842E0;      /* gp - 0xE90 */
extern s16 D_004842E8;      /* gp - 0xE88 */
extern s32 D_004842EC;      /* gp - 0xE84 */
extern s32 D_004842F0;      /* gp - 0xE80 */
extern s16 D_00484300;      /* gp - 0xE70 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insmenu_InsectVsMenuSetupWidgets_4f3670(void)
{
    void *ctx;
    Rec *r;
    void *data;
    s32 id;

    ctx = GetMenuResGroup_206a40();
    r = ((Rec *)ResGroupListFindById_42c500(ctx, 0x31));
    data = r->f4;
    id = r->fA;
    UiWidgetListReset_2912e0(insmenu_D_004FA180);
    UiInitWidgetPool_290390(insmenu_D_004FA180, (void *)D_004842E0, id);
    UiAddWidgets_2901d0(insmenu_D_004FA180, data, 0);
    *(s32 *)&insmenu_D_004FA188 = 0x32D;
    UiTextStyleReset_290450();

    r = ((Rec *)ResGroupListFindById_42c040(ctx, 0x21));
    data = r->f4;
    id = r->fA;
    UiEntryListReset_28ec80(insmenu_D_004FA1A0);
    UiEntryListAlloc_28e0c0(insmenu_D_004FA1A0, (void *)D_004842E0, id);
    UiEntryListLoad_28eb70(insmenu_D_004FA1A0, data, insmenu_D_004FA180);

    *(s32 *)&insmenu_D_004FA1B8 = SceneSoundGetSlot0HandleCur_207df0();
    ((Flags *)&insmenu_D_004FA1C0)->b0 = 0;
    D_004842EC = 0;
    D_004842F0 = 0;
    *(u8 *)&insmenu_D_004FA1C1 = 0;
    D_004842E8 = 0;
    D_004842F0 = MenuStateTableForId_42c950(ctx, 0x20);

    PadClearRepeatAll_183960(&D_004B2570);
    PadSetRepeat_183d50(&D_004B2570, 0xF00C, 0xA, 3);
    PadSetStickDpadThreshold_183950(&D_004B2570, 0x78);
    PadClearRepeatAll_183960(&D_004B27E0);
    PadSetRepeat_183d50(&D_004B27E0, 0xF00C, 0xA, 3);
    PadSetStickDpadThreshold_183950(&D_004B27E0, 0x78);

    StateMachineSetState_28ede0(&D_004842E8, 0x7531, 1);
    insmenu_InsectVsPanelsInit_4ee1d0();
    D_00484300 = 2;
}
