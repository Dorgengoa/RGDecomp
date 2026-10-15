#include "types.h"
/* normal 0x00517D40 (768 B / 192 words) -- pumps one page of the 0x38-byte
 * record ring (the same ring normal_TransMenuSubResRequest_518040 fills) and hands each ready
 * record to the renderer the way the current page mode D_004806CC wants it.
 * Returns 1 only when the page is finished AND the retry counter has run out.
 *
 * Read off the listing:
 *  - `sll $3,$19,3 / subu $3,$3,$19 / sll $16,$3,3` is i * 0x38, i.e.
 *    &((Rec *)D_0048478C)[i] with sizeof(Rec) == 56 -- the base pointer is
 *    RELOADED from gp at every use, only the scaled index is CSE'd.
 *  - `bgez / sra 4 / addiu 0xF / sra 4` is a signed `w / 16`.
 *  - the eight `beq` against 2,3,4,5,6,7,8,1 followed by `bnel $3,$0` is ONE
 *    `||` chain in SOURCE ORDER, not a jump table; the last term is the
 *    `(mode == 0 && i == 0)` pair.
 *  - `beql $2,$3,.L00517FC4` with the increment in the delay slot is the FIRST
 *    predecessor of the shared continue being threaded
 *    (levers.d/mwcc-branch-likely-duplication.md FIX 3); the other two guards
 *    reach the increment label plainly.
 */
typedef struct Rec { u8 pad000[56]; } Rec;

extern void *D_004846E4;          /* gp - 0xA8C  */
extern s16   D_00484750;          /* gp - 0xA20  */
extern s16   D_00484754;          /* gp - 0xA1C  */
extern void *D_0048475C;          /* gp - 0xA14  */
extern void *D_00484784;          /* gp - 0x9EC  */
extern void *D_0048478C;          /* gp - 0x9E4  */
extern void *D_00484794;          /* gp - 0x9DC  */
extern s16   D_004806CC;          /* gp - 0x4AA4 */
extern s8    D_00526590[];

extern s32   func_28B220(void *p);
extern s32   func_28B210(void *p);
extern s32   func_28B2E0(void *p);
extern void  func_28B230(void *p);
extern s32   func_28B070(void *p, s32 n);
extern void *func_28B270(void *p, s32 *out);
extern void *func_15DE40(void);
extern void  func_14D8E0(void *p);
extern void *func_14DA10(void *p, s32 n);
extern void  func_1319A8(void *a, void *b, s32 c);
extern void  func_1594D0(void *a, void *b, s32 c, void *d, s32 e);
extern void  func_289C60(void *a, s32 b, void *c, s32 d);
extern void  func_37BBD0(void *a, void *b);
extern void  normal_TransMenuIconClutBuild_518590(void);
extern void  normal_TransSaveIconSysInit_518a50(void *a);

s32 normal_TransMenuSubResPoll_517d40(void)
{
    void *p;
    s32   n;
    s32   i;
    void *h;
    void *q;
    void *r;
    s32   w;

    if (D_004806CC < 0) {
        return 0;
    }
    p = D_004846E4;
    n = D_00526590[D_004806CC];
    for (i = 0; i < n; i++) {
        if (func_28B220(&((Rec *)D_0048478C)[i]) == -1) {
            continue;
        }
        if (func_28B210(&((Rec *)D_0048478C)[i]) == 0) {
            continue;
        }
        if (func_28B2E0(&((Rec *)D_0048478C)[i]) != 1) {
            continue;
        }
        h = func_15DE40();
        q = func_28B270(&((Rec *)D_0048478C)[i], &w);
        func_14D8E0(p);
        if (D_004806CC == 2 || D_004806CC == 3 || D_004806CC == 4 ||
            D_004806CC == 5 || D_004806CC == 6 || D_004806CC == 7 ||
            D_004806CC == 8 || D_004806CC == 1 ||
            (D_004806CC == 0 && i == 0)) {
            if (D_004806CC == 0) {
                r = func_14DA10(p, w / 16 + 1);
                func_1319A8(r, q, w);
                D_00484794 = r;
                func_1594D0(h, r, 0x32D, p, 0);
            } else if (D_004806CC == 1) {
                func_289C60(q, w, D_00484784, 0xF081);
                func_1594D0(h, D_00484784, 0x32C, p, 0);
                normal_TransMenuIconClutBuild_518590();
            } else {
                r = func_14DA10(p, w / 16 + 1);
                func_1319A8(r, q, w);
                func_1594D0(h, r, 0x32C, p, 0);
            }
        } else {
            r = func_14DA10(p, w / 16 + 1);
            func_1319A8(r, q, w);
            func_37BBD0(D_0048475C, r);
            normal_TransSaveIconSysInit_518a50(D_0048475C);
        }
        func_28B230(&((Rec *)D_0048478C)[i]);
    }
    if (func_28B070(D_0048478C, n) == 1) {
        if (D_00484754 < 10) {
            D_00484754 = D_00484754 + 1;
        } else {
            D_00484750 = 1;
            D_00484754 = 10;
            return 1;
        }
    }
    return 0;
}
