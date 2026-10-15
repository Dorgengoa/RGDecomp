#include "types.h"
/* normal 0x00519C60 -- map-warp entry.  The two failing probes share one
 * `func_376B20(6); return 0;` tail, so they are a `||` (the `bnel` delay slot
 * carries the shared `addiu $4,$0,6`). */

typedef struct Ent {
    u8  pad000[0x12];
    s16 f012;
    s16 f014;
    s16 f016;
} Ent;

extern void *D_00484724;          /* gp - 0xA4C */
extern void *D_004847D8;          /* gp - 0x998 */
extern volatile s16 D_004847E8;          /* gp - 0x988 */
extern s16   D_004847EC;          /* gp - 0x984 */

extern s32   func_373540(void *p, s16 n);
extern s32   func_373480(void *p, s16 n);
extern void  func_376B20(s32 a);
extern void  func_207FE0(void);
extern void  func_37B9C0(s16 n);
extern void *func_1FEDE0(void);
extern void *func_3E4E80(void *p, s16 n);
extern s32   func_37B950(void);
extern s32   func_3EEC60(void *p);
extern void  func_28EA90(void *p, s32 id, s32 a);

s32 normal_TransSaveSlotListConfirm_519c60(Ent *e)
{
    void *h;
    s32 t;

    D_004847EC = e->f016;
    t = e->f016 + e->f012;
    D_004847E8 = t;
    if (func_373540(D_00484724, t) != 0 || func_373480(D_00484724, D_004847E8) != 0) {
        func_376B20(6);
        return 0;
    }
    func_207FE0();
    func_376B20(5);
    func_37B9C0(D_004847E8);
    h = func_3E4E80(func_1FEDE0(), D_004847E8);
    if (func_37B950() == 0 || h == 0 || func_3EEC60(h) != 0) {
        func_28EA90(D_004847D8, 5, 1);
    } else {
        func_28EA90(D_004847D8, 6, 1);
    }
    return 1;
}
