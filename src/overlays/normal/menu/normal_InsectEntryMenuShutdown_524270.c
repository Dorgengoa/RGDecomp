#include "types.h"
/* normal 0x00524270 -- the shop screen's light teardown: drops both archives
 * and the cached buffer, then resets four gp state cells.  Pass-33 LIST rank:
 * 92 bytes, 23 instructions, ZERO branches, 5 calls.  The heavy twin is
 * normal_FUN_00522EB0, which also frees the two handles. */

extern const u8 D_004B2570[];

extern s16 D_004807B4;            /* gp - 0x49BC */
extern s8  D_004849B8;            /* gp - 0x7B8  */
extern s16 D_004849C0;            /* gp - 0x7B0  */
extern s16 D_004849C4;            /* gp - 0x7AC  */

extern void  func_183940(const u8 *p);
extern void  func_183960(const u8 *p);
extern void *func_206A40(void);
extern void  func_42B650(void *p, s32 k);
extern void  normal_InsectEntryMenuFileRelease_524620(void);

extern void normal_InsectEntryMenuShutdown_524270(void);

void normal_InsectEntryMenuShutdown_524270(void)
{
    normal_InsectEntryMenuFileRelease_524620();
    func_183960(D_004B2570);
    func_183940(D_004B2570);
    func_42B650(func_206A40(), 2);
    D_004849C0 = 0;
    D_004807B4 = 1;
    D_004849B8 = 0;
    D_004849C4 = 0;
}
