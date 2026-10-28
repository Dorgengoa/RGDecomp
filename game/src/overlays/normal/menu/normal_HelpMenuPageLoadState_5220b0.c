/* rgp:protos */
#define RGP_SELF_normal_HelpMenuPageLoadState_5220b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005220B0 -- the item/skill description box.  `b != 0` opens it:
 * the 0x7534 frame, the caption built out of the 0x76-byte record at
 * D_004849E8[D_004849F8], and the request handle parked in D_004849E0.  Every
 * call then polls func_1CD4F0, and on state 1 the measured text is laid into
 * the box, the request is closed and the 0x753B hand-off fires.
 *
 * `daddu $16,$5,$0` is in func_1F59D0's DELAY SLOT, so the FIRST statement is
 * `g = func_1F59D0();` and the guard on `b` comes after it.
 * `sll 4 / subu / sll 2 / subu / sll 1` is a 0x76-byte array stride, i.e.
 * `&base[i]` with an s16 index -- recomputed at both use sites, so the record
 * pointer is NOT a shared local.
 * `bgez $3, .L / sra $2,$3,4` with the `addiu $2,$3,0xF` bias is a SIGNED
 * `/ 16`, not a shift.
 * `slti $1, $2, 0x2` writes $at at BOTH sites: the source token is `> 1`,
 * not `>= 2` ([[at-compare-class]]).
 * The two `bne` guards are PLAIN, not likely, and each carries its own gp
 * store in the delay slot -- the store is the statement before the test. */

typedef struct Rec { u8 pad00[4]; s16 f04; u8 pad06[0x76 - 6]; } Rec;
typedef struct Cap { u8 b[0x4C]; } Cap;
typedef struct Lbl { u8 b[0x20]; } Lbl;

extern u8 normal_D_005268B0[];
extern u8 normal_D_005281A0[];
extern u8 normal_D_005281C0[];

extern s32   D_004849A0;          /* gp - 0x7D0 */
extern s32   D_004849A8;          /* gp - 0x7C8 */
extern s32   D_004849E0;          /* gp - 0x790 */
extern s32   D_004849E4;          /* gp - 0x78C */
extern Rec  *D_004849E8;          /* gp - 0x788 */
extern s16   D_004849F8;          /* gp - 0x778 */
extern u8    D_004849FC;          /* gp - 0x774 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void  strcpy(void *a, const void *b);
extern void  strcat(void *a, const void *b);
extern void  Sprintf_1343b8(void *a, const void *b, u8 c);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void  memcpy(s32 a, s32 b, s32 c);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_HelpMenuPageLoadState_5220b0(void *a, s32 b)
{
    s32  g;
    s32  box;
    s32  txt;
    s32  h;
    s32  n;
    Cap  cap __attribute__((aligned(16)));
    Lbl  lbl __attribute__((aligned(16)));

    g = ((s32)GetLoaderMgr_1f59d0());
    if (b != 0) {
        UiEntryListSelectByTag_28ea90(normal_D_005281C0, 0x7534, 0);
        NameTableFreeGroup_158ac0(GetDrawCtxNameTable_15de40(), 0x32C);
        h = ((s32)GetLoaderMgr_1f59d0());
        MemStackReset_14d830(D_004849A0);
        D_004849E0 = -1;
        D_004849E4 = 0;
        strcpy(&cap, normal_D_005268B0);
        strcat(&cap, (const u8 *)&D_004849E8[D_004849F8] + 0x46);
        if (D_004849E8[D_004849F8].f04 > 1) {
            Sprintf_1343b8(&cap, &cap, D_004849FC);
        }
        D_004849E0 = LoaderRequestFile_1cd870(h, &cap, 0);
        if (D_004849E0 == -1) {
            return 0;
        }
        LoaderQueueAppendSeparator_1cd670(h);
    }
    D_004849E4 = LoaderGetStatus_1cd4f0(g, D_004849E0);
    if (D_004849E4 == 1) {
        box = GetDrawCtxNameTable_15de40();
        MemStackAlign64_14d8e0(D_004849A0);
        h = MemStackPeekQw_14d9d0(D_004849A0, 1);
        txt = ((s32)LoaderGetData_1cd490(g, D_004849E0, &n));
        MemStackAllocAligned64_14da10(D_004849A0, (n / 16) + 1);
        memcpy(h, txt, n);
        NameTableRegisterImArchive_1594d0(box, h, 0x32C, D_004849A0, 0);
        LoaderReleaseById_1cd340(g, D_004849E0);
        D_004849E0 = -1;
        if (D_004849E8[D_004849F8].f04 > 1) {
            Sprintf_1343b8(&lbl, (const u8 *)&D_004849E8[D_004849F8] + 0x66,
                        D_004849FC);
        } else {
            strcpy(&lbl, (const u8 *)&D_004849E8[D_004849F8] + 0x66);
        }
        UiSetWidgetTexName_290ac0(normal_D_005281A0, 0x32, &lbl);
        StateMachineSetState_28ede0(&D_004849A8, 0x753B, 1);
    }
    return 1;
}
