/* rgp:protos */
#define RGP_SELF_normal_InsectEntryMenuInit_5245b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005245B0 -- a scene/state initialiser: eight gp publishes and six
 * calls, straight-line.  Four stores are written BEFORE their call and fill
 * its delay slot (the recorded shape); the func_206A60 result is held in a
 * local because retail passes `$2` on rather than re-reading the global it
 * just wrote.  One of the 55 unnamed functions; see scripts/n_unnamed.py. */
extern void *D_00484998;
extern void *D_0048499C;
extern u8    D_004849B8;
extern u8    D_004849BC;
extern s16   D_004849C0;
extern s16   D_004849C4;
extern s16   D_004849F4;
extern s16   D_004807B4;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void normal_InsectEntryMenuInit_5245b0(void)
{
    void *h;

    D_00484998 = SceneSoundGetSlot0HandleCur_207df0();
    D_004849C4 = 0;
    h = GetMenuTransdataStack_206a60();
    D_0048499C = h;
    MemStackReset_14d830(h);
    D_004849BC = 0;
    D_004849C0 = 1;
    D_004849B8 = 1;
    D_004807B4 = 1;
    NameTableFreeGroup_158ac0(GetDrawCtxNameTable_15de40(), 0x32D);
    D_004849F4 = 0;
    normal_InsectEntryMenuResRequest_5247d0();
    normal_InsectEntryMenuResPoll_524680();
}
