/* rgp:protos */
#define RGP_SELF_normal_InsectEntryMenuResRequest_5247d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005247D0 -- opens the shop's stream: takes the 0x32D slot, asks for
 * the file, and tears the reader down again if the request was refused.
 * Pass-33 LIST rank: 116 bytes, 29 instructions, ONE conditional branch,
 * 5 calls.  `bne` is a PLAIN branch, so `D_004807B8 = r;` in its delay slot
 * runs on both paths and the guard is only the early `return 1`. */

extern s32   D_004802C0;          /* gp - 0x4EB0 */
extern s32   D_004807B8;          /* gp - 0x49B8 */
extern s32   D_004807BC;          /* gp - 0x49B4 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern s32 normal_InsectEntryMenuResRequest_5247d0(void);

s32 normal_InsectEntryMenuResRequest_5247d0(void)
{
    void *q;
    s32   r;

    NameTableFreeGroup_158ac0(GetDrawCtxNameTable_15de40(), 0x32D);
    q = GetLoaderMgr_1f59d0();
    D_004807B8 = -1;
    D_004807BC = 0;
    r = LoaderRequestFile_1cd870(q, D_004802C0, 0);
    D_004807B8 = r;
    if (r == -1) {
        return 1;
    }
    LoaderQueueAppendSeparator_1cd670(q);
    return 0;
}
