#include "types.h"
/* normal 0x00516AA0 -- the gameplay scene's one-shot bring-up: the 0x7FB
 * resource pair, the five 0x14-byte widget records allocated in one block by
 * func_100710 and reset one by one, the HUD handles taken off D_004846E0, the
 * 0x4B2570 text box, then the camera hand-off that reads the actor's transform
 * into the frame Vec and pushes it at func_321910.
 *
 * The tail's `addiu $2,$28,-0xA70` is the ADDRESS of a gp global -- i.e.
 * &D_00484700 -- and it is DUPLICATED into the `beql $17,$0` delay slot: the
 * shared-tail duplicate that reads as a per-arm `return`, so the two guards
 * are NESTED ifs, not a `&&` and not an early return.
 *
 * `sw $2, -0xA4C($28)` and `sw $2, -0xA14($28)` each sit in the NEXT call's
 * delay slot and capture the PREVIOUS call's result -- three times here.
 * `lui $2,0x4170 / mtc1 $2,$f12` is the literal 15.0f. */

typedef struct Obj { u8 pad00[0x14]; } Obj;
typedef struct Ent { u8 pad00[0x10]; void *f10; u8 pad14[4];
                     struct Act *f18; } Ent;
typedef struct Act { u8 pad00[0x30]; s16 f30; } Act;
typedef struct Xf  { u8 pad00[0x20]; f32 f20; f32 f24; f32 f28;
                     u8 pad2C[0x40 - 0x2C]; s32 f40; } Xf;
typedef struct Cam { u8 pad00[0x510]; s32 f510; } Cam;
typedef struct Vec { f32 x; f32 y; f32 z; f32 w; } Vec;

extern const u8 D_00527EE0[];
extern const u8 D_00527F10[];
extern const u8 D_004B2570[];

extern f32   D_004806F0;          /* gp - 0x4A80 */
extern f32   D_004806F4;          /* gp - 0x4A7C */
extern f32   D_004806F8;          /* gp - 0x4A78 */
extern f32   D_004806FC;          /* gp - 0x4A74 */
extern s16   D_004806C8;          /* gp - 0x4AA8 */
extern s16   D_004806CC;          /* gp - 0x4AA4 */
extern void *D_004846E0;          /* gp - 0xA90  */
extern void *D_004846E4;          /* gp - 0xA8C  */
extern Obj  *D_004846E8;          /* gp - 0xA88  */
extern Obj  *D_004846EC;          /* gp - 0xA84  */
extern Obj  *D_004846F0;          /* gp - 0xA80  */
extern Obj  *D_004846F4;          /* gp - 0xA7C  */
extern Obj  *D_004846F8;          /* gp - 0xA78  */
extern s16   D_00484700;          /* gp - 0xA70  */
extern s32   D_00484704;          /* gp - 0xA6C  */
extern s32   D_00484708;          /* gp - 0xA68  */
extern void *D_0048470C;          /* gp - 0xA64  */
extern Obj  *D_00484710;          /* gp - 0xA60  */
extern Obj  *D_00484714;          /* gp - 0xA5C  */
extern Obj  *D_00484718;          /* gp - 0xA58  */
extern Obj  *D_0048471C;          /* gp - 0xA54  */
extern const u8 *D_00484720;      /* gp - 0xA50  */
extern void *D_00484724;          /* gp - 0xA4C  */
extern void *D_00484728;          /* gp - 0xA48  */
extern s8    D_0048472C;          /* gp - 0xA44  */
extern s8    D_00484730;          /* gp - 0xA40  */
extern s32   D_00484738;          /* gp - 0xA38  */
extern void *D_00484740;          /* gp - 0xA30  */
extern s32  *D_00484744;          /* gp - 0xA2C  */
extern s8    D_00484748;          /* gp - 0xA28  */
extern s16   D_0048474C;          /* gp - 0xA24  */
extern s16   D_00484750;          /* gp - 0xA20  */
extern s16   D_00484754;          /* gp - 0xA1C  */
extern void *D_0048475C;          /* gp - 0xA14  */
extern s32   D_00484768;          /* gp - 0xA08  */
extern s8    D_0048476C;          /* gp - 0xA04  */
extern s32   D_00484770;          /* gp - 0xA00  */
extern s8    D_00484778;          /* gp - 0x9F8  */
extern void *D_00484788;          /* gp - 0x9E8  */
extern void *D_0048478C;          /* gp - 0x9E4  */
extern s32   D_00484794;          /* gp - 0x9DC  */

extern Ent  *func_1FEDE0(void);
extern s32   func_3CCD70(void *a, s32 b);
extern void  func_3CCB70(void *a, s32 b, s32 c, s32 d);
extern void  func_178490(const void *a);
extern s32   func_206A60(void);
extern s32   func_206A50(void);
extern void  func_14D830(s32 a);
extern void *func_28C2A0(void *a);
extern void *func_14E230(s32 a, void *b);
extern void *func_14E1B0(s32 a, void *b);
extern Obj  *func_100710(void *a, s32 b, s32 c, s32 d, s32 e);
extern void  func_2912E0(Obj *a);
extern void  func_28EC80(const void *a);
extern s32  *func_14D950(void *a, s32 b);
extern void  func_183960(const void *a);
extern void  func_183D50(const void *a, s32 b, s32 c, s32 d);
extern void  func_183950(const void *a, s32 b);
extern void  func_28B160(void *a, s32 b);
extern void  normal_TransWarpListAlloc_51a9a0(void *a);
extern void *func_15DE40(void);
extern void  func_158AC0(void *a, s32 b);
extern void  normal_TransMenuResRequest_518370(void);
extern void  normal_TransMenuResPoll_5181d0(void);
extern s32   func_201A90(void);
extern s8    func_3CB120(struct Act *a);
extern void  func_1E49B0(s32 a, s16 b, s32 *c);
extern void  func_1DCB50(s32 a);
extern Xf   *func_3C97E0(struct Act *a);
extern Cam  *func_201A70(void);
extern void  func_321E60(Cam *a, f32 b);
extern void  func_321910(Cam *a, Vec *b);
extern s32   func_324270(s32 a, s32 b);
extern void  normal_TransMenuBobIconReset_518570(Obj *a);

void normal_TransMenuInit_516aa0(void)
{
    Ent *e;
    Obj *arr;
    s32  i;
    Xf  *xf;
    Cam *cam;
    s32  h;
    s32  sel;
    Vec  v;

    D_00484778 = 0;
    e = func_1FEDE0();
    if (e != 0) {
        if (func_3CCD70(e->f10, 0x7FB) != 0) {
            D_00484778 = 1;
        }
        func_3CCB70(e->f10, 0x7FB, 0, 0);
    }
    D_00484794 = 0;
    func_178490(D_00527F10);
    D_00484750 = 0;
    D_004806CC = -1;
    D_00484754 = 0;
    D_004846E0 = (void *)func_206A60();
    func_14D830((s32)D_004846E0);
    D_004846E4 = (void *)func_206A50();
    func_14D830((s32)D_004846E4);
    D_00484728 = func_28C2A0(D_004846E0);
    D_00484724 = func_14E230(0x528, D_004846E0);
    D_0048475C = func_14E230(0x78, D_004846E0);
    arr = func_100710(func_14E1B0(0x74, D_004846E0), 0, 0, 0x14, 5);
    i = 0;
    D_004846E8 = arr;
    D_004846EC = arr + 1;
    D_004846F0 = arr + 2;
    D_004846F4 = arr + 3;
    D_004846F8 = arr + 4;
    do {
        func_2912E0(&arr[i]);
        i = i + 1;
    } while (i < 5);
    func_28EC80(D_00527EE0);
    D_00484704 = 0;
    D_00484708 = 0;
    D_00484700 = 0;
    D_00484744 = func_14D950(D_004846E0, 0x1D);
    *D_00484744 = 0;
    func_183960(D_004B2570);
    func_183D50(D_004B2570, 0xF00C, 0xC, 7);
    func_183950(D_004B2570, 0x78);
    D_0048474C = 1;
    D_00484748 = 1;
    D_004806C8 = 1;
    D_00484740 = func_14E230(0x1B4, D_004846E0);
    D_00484788 = func_14E1B0(0x38, D_004846E0);
    D_0048478C = func_14E1B0(0x1F8, D_004846E0);
    func_28B160(D_0048478C, 9);
    normal_TransWarpListAlloc_51a9a0(D_004846E0);
    func_158AC0(func_15DE40(), 0x32D);
    normal_TransMenuResRequest_518370();
    normal_TransMenuResPoll_5181d0();
    e = func_1FEDE0();
    h = func_201A90();
    D_00484768 = -1;
    D_0048476C = func_3CB120(e->f18);
    sel = 0;
    func_1E49B0(h, e->f18->f30, &sel);
    if (h != 0) {
        if (sel != 0) {
            func_1DCB50(sel);
            if (func_3C97E0(e->f18) != 0) {
                v.x = D_004806F0;
                v.y = D_004806F4;
                v.z = D_004806F8;
                v.w = D_004806FC;
                xf = func_3C97E0(e->f18);
                if (xf != 0 && (xf->f40 & 1)) {
                    v.x = xf->f20;
                    v.y = xf->f24;
                    v.z = xf->f28;
                }
                cam = func_201A70();
                if (cam != 0) {
                    func_321E60(cam, 15.0f);
                    func_321910(cam, &v);
                    if (cam->f510 != 0) {
                        D_00484768 = func_324270(cam->f510, 1);
                    }
                }
            }
        }
    }
    D_0048470C = &D_00484700;
    D_00484710 = D_004846E8;
    D_00484720 = D_00527EE0;
    D_00484714 = D_004846F0;
    D_00484770 = 0;
    D_00484718 = D_004846F4;
    D_0048472C = 0;
    D_00484730 = 0;
    D_0048471C = D_004846F8;
    D_00484738 = 0;
    normal_TransMenuBobIconReset_518570(D_004846E8);
}
