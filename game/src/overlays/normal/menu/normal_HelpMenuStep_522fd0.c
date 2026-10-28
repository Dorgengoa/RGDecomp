/* rgp:protos */
#define RGP_SELF_normal_HelpMenuStep_522fd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00522FD0 -- the shop/status screen's per-frame driver.  On the
 * first tick (D_004849BC set) it builds the two 0x32D/0x32C panels and the
 * 0x7 portrait out of func_42C500/func_42C040 records, arms the 0x4B2570 text
 * box and clears the flag; then it watches for the confirm edge, runs
 * normal_InsectEntryMenuResPoll_524680 and, in state 2, tears the three widgets down.
 *
 * `lhu 0xA / dsll32 16 / dsrl32 18` is the `u16 :2 / u16 :14` bitfield at
 * offset 0xA -- the same Rec this subsystem uses in normal_TransMenuLayoutBuild_516e20.
 * `lbu / addiu $6,$0,-2 / andi $7,$0,1 / and / or / sb` on normal_D_005281E0 is a
 * ONE-BIT BITFIELD AT BIT 0 assigned 0; the whole insert survives only because
 * the assigned value is 0 -- `= 1` folds to a plain store.
 * m2c renders func_42C950 with SIX arguments; it takes TWO.  The other four
 * are the bitfield insert's still-live registers.
 * `beql $3,$0,.L00523244 / ld $31,0x30($29)` duplicates the EPILOGUE's first
 * word into the likely slot and targets one instruction past it -- the guard
 * is a plain early return, not a branch into a block.
 *
 * THE STORE GROUP'S ORDER IS THE WHOLE RESIDUE, and it is a SIX-way search,
 * not a three-way one.  normal_D_005281D8, the bitfield and normal_D_005281E1 measured
 * 15 / MATCH / 17 / 15 / 17 / 15 over all six permutations; the winner is
 * D8, BITFIELD, E1 -- the bitfield in the MIDDLE.  normal_TransMenuLayoutBuild_516e20 is
 * parked on this same group with only three orders recorded (bitfield first,
 * bitfield last, bitfield first with one store moved up), so its sweep never
 * reached this cell.
 *
 * Every one of normal_D_00528188 / normal_D_005281A8 / normal_D_005281D8 / normal_D_005281E0 / normal_D_005281E1
 * is declared as an INCOMPLETE ARRAY: as plain scalars they are under the
 * small-data threshold and mwcc gives one `sw ..($gp)` (R_MIPS_GPREL16) where
 * retail wants `lui %hi` + `sw %lo` -- right instruction, wrong relocation,
 * and one word short at every site.
 * D_004849A8 is s16 (`sh`), and it is also address-taken. */

typedef struct Rec {
    u8    pad00[4];
    s32   f04;
    u8    pad08[2];
    __extension__ unsigned short   fA_lo : 2;
    unsigned short   fA_hi : 14;
} __attribute__((aligned(2))) Rec;
typedef struct Flags { u8 b0 : 1; u8 rest : 7; } Flags;

extern u8    normal_D_00528180[];
extern s32   normal_D_00528188[];
extern u8    normal_D_005281A0[];
extern s32   normal_D_005281A8[];
extern u8    normal_D_005281C0[];
extern s32   normal_D_005281D8[];
extern Flags normal_D_005281E0[];
extern s8    normal_D_005281E1[];
extern u8 D_004B2570[];

extern s32   D_00484998;          /* gp - 0x7D8 */
extern void *D_0048499C;          /* gp - 0x7D4 */
extern s16   D_004849A8;          /* gp - 0x7C8 */
extern s32   D_004849AC;          /* gp - 0x7C4 */
extern s32   D_004849B0;          /* gp - 0x7C0 */
extern u8    D_004849BC;          /* gp - 0x7B4 */
extern s16   D_004849C0;          /* gp - 0x7B0 */
extern s16   D_004849C4;          /* gp - 0x7AC */
extern s16   D_004807B4;          /* gp - 0x49BC */

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
/*rgp*/
/*rgp*/

void normal_HelpMenuStep_522fd0(void)
{
    void *g;
    Rec  *r;
    s32   id;
    s32   n;

    if (D_004849C0 == 0) {
        return;
    }
    if (D_004849BC != 0) {
        g = GetMenuResGroup_206a40();
        r = ((Rec *)ResGroupListFindById_42c500(g, 9));
        id = r->f04;
        n = r->fA_hi;
        UiWidgetListReset_2912e0(normal_D_00528180);
        UiInitWidgetPool_290390(normal_D_00528180, D_0048499C, n);
        UiAddWidgets_2901d0(normal_D_00528180, id, 0);
        normal_D_00528188[0] = 0x32D;
        UiTextStyleReset_290450();
        r = ((Rec *)ResGroupListFindById_42c500(g, 0xA));
        id = r->f04;
        n = r->fA_hi;
        UiWidgetListReset_2912e0(normal_D_005281A0);
        UiInitWidgetPool_290390(normal_D_005281A0, D_0048499C, n);
        UiAddWidgets_2901d0(normal_D_005281A0, id, 0);
        normal_D_005281A8[0] = 0x32C;
        UiTextStyleReset_290450();
        r = ((Rec *)ResGroupListFindById_42c040(g, 7));
        id = r->f04;
        n = r->fA_hi;
        UiEntryListReset_28ec80(normal_D_005281C0);
        UiEntryListAlloc_28e0c0(normal_D_005281C0, D_0048499C, n);
        UiEntryListLoad_28eb70(normal_D_005281C0, id, normal_D_00528180);
        normal_D_005281D8[0] = D_00484998;
        normal_D_005281E0[0].b0 = 0;
        normal_D_005281E1[0] = 0;
        D_004849AC = 0;
        D_004849B0 = 0;
        D_004849A8 = 0;
        D_004849B0 = MenuStateTableForId_42c950(g, 7);
        PadClearRepeatAll_183960(D_004B2570);
        PadSetRepeat_183d50(D_004B2570, 0xF00C, 0xA, 3);
        PadSetStickDpadThreshold_183950(D_004B2570, 0x78);
        UiSetWidgetsVisibleById_291110(normal_D_00528180, 0x2A, 0, 1);
        D_004849BC = 0;
    }
    if (D_004849C4 == 1 && D_004807B4 == 1) {
        D_004849C0 = 2;
        D_004807B4 = 0;
        StateMachineSetState_28ede0(&D_004849A8, 0x7537, 1);
    }
    normal_InsectEntryMenuResPoll_524680();
    if (D_004849C0 == 2) {
        UiUpdateWidgets_2913a0(normal_D_00528180);
        StateMachineUpdate_28ed70(&D_004849A8);
        UiUpdateWidgets_2913a0(normal_D_005281A0);
    }
}
