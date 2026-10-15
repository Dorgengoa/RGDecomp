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

extern void *func_207DF0(void);
extern void *func_206A60(void);
extern void  func_14D830(void *p);
extern void *func_15DE40(void);
extern void  func_158AC0(void *p, s32 id);
extern void  normal_InsectEntryMenuResRequest_5247d0(void);
extern void  normal_InsectEntryMenuResPoll_524680(void);

void normal_InsectEntryMenuInit_5245b0(void)
{
    void *h;

    D_00484998 = func_207DF0();
    D_004849C4 = 0;
    h = func_206A60();
    D_0048499C = h;
    func_14D830(h);
    D_004849BC = 0;
    D_004849C0 = 1;
    D_004849B8 = 1;
    D_004807B4 = 1;
    func_158AC0(func_15DE40(), 0x32D);
    D_004849F4 = 0;
    normal_InsectEntryMenuResRequest_5247d0();
    normal_InsectEntryMenuResPoll_524680();
}
