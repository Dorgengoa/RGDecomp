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

extern void *func_207DF0(void);
extern void *func_206A60(void);
extern void *func_206A50(void);
extern void  func_14D830(void *p);
extern void *func_15DE40(void);
extern void  func_158AC0(void *p, s32 id);
extern void  normal_InsectEntryMenuResRequest_5247d0(void);
extern void  normal_InsectEntryMenuResPoll_524680(void);

void normal_HelpMenuInit_523280(void)
{
    void *h;
    void *w;

    D_00484998 = func_207DF0();
    D_004849C4 = 0;
    D_004849E8 = 0;
    D_004849EC = 0;
    D_004849F0 = 0;
    D_004849F4 = 0;
    D_004849F8 = 0;
    D_004849FC = 0;
    h = func_206A60();
    D_0048499C = h;
    func_14D830(h);
    h = func_206A50();
    D_004849A0 = h;
    func_14D830(h);
    D_004849BC = 0;
    D_004849C0 = 1;
    D_004849B8 = 1;
    D_004807B4 = 1;
    w = func_15DE40();
    func_158AC0(w, 0x32D);
    func_158AC0(w, 0x32C);
    D_004849F4 = 1;
    normal_InsectEntryMenuResRequest_5247d0();
    normal_InsectEntryMenuResPoll_524680();
}
