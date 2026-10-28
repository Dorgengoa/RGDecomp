/* rgp:protos */
#define RGP_SELF_normal_HelpMenuInit_523280 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00523280 -- the long sibling of normal_InsectEntryMenuInit_5245b0.  The func_15DE40
 * result is used by TWO calls, so it is a named local held in `$16`; the
 * func_206A60 / func_206A50 results are each used once and passed straight on.
 * One of the 55 unnamed functions. */
extern void *D_00484998;
extern void *D_0048499C;
extern void *D_004849A0;
extern u8    D_004849B8;
extern u8    D_004849BC;
extern s16   D_004849C0;
extern s16   D_004849C4;
extern s32   D_004849E8;
extern s32   D_004849EC;
extern s32   D_004849F0;
extern s16   D_004849F4;
extern s16   D_004849F8;
extern u8    D_004849FC;
extern s16   D_004807B4;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void normal_HelpMenuInit_523280(void)
{
    void *h;
    void *w;

    D_00484998 = SceneSoundGetSlot0HandleCur_207df0();
    D_004849C4 = 0;
    D_004849E8 = 0;
    D_004849EC = 0;
    D_004849F0 = 0;
    D_004849F4 = 0;
    D_004849F8 = 0;
    D_004849FC = 0;
    h = GetMenuTransdataStack_206a60();
    D_0048499C = h;
    MemStackReset_14d830(h);
    h = GetMenuTranstempStack_206a50();
    D_004849A0 = h;
    MemStackReset_14d830(h);
    D_004849BC = 0;
    D_004849C0 = 1;
    D_004849B8 = 1;
    D_004807B4 = 1;
    w = GetDrawCtxNameTable_15de40();
    NameTableFreeGroup_158ac0(w, 0x32D);
    NameTableFreeGroup_158ac0(w, 0x32C);
    D_004849F4 = 1;
    normal_InsectEntryMenuResRequest_5247d0();
    normal_InsectEntryMenuResPoll_524680();
}
