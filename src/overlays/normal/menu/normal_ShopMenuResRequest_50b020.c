#include "types.h"
/* normal 0x0050B020 -- two-slot loader loop over the 8-byte gp table at
 * gp-0x4B30; slot 0 takes the F081/F080 path, every other slot the plain one. */

typedef struct Ent { s32 f00; s32 f04; } Ent;

extern Ent   D_00480640[1];       /* gp - 0x4B30 */
extern s32   D_004845F0[2];       /* gp - 0xB80  */
extern s32   D_004845FC;          /* gp - 0xB74  */

extern void  func_15DE40(void);
extern void *func_1F59D0(void);
extern s32   func_1CDB10(void *p, u32 a);
extern s32   func_1CD6C0(void *p, s32 id, s32 a, u32 b, s32 c);
extern s32   func_1CD870(void *p, s32 id, s32 a);
extern void  func_1CD670(void *p);

s32 normal_ShopMenuResRequest_50b020(void)
{
    void *w;
    s32   i;
    Ent  *e;

    func_15DE40();
    w = func_1F59D0();
    for (i = 0; i < 2; i++) {
        e = &D_00480640[i];
        e->f00 = -1;
        e->f04 = 0;
        if (i == 0) {
            D_004845FC = func_1CDB10(func_1F59D0(), 0xF081);
            e->f00 = func_1CD6C0(w, D_004845F0[i], D_004845FC, 0xF080, 0);
        } else {
            e->f00 = func_1CD870(w, D_004845F0[i], 0);
        }
        if (e->f00 == -1) {
            return 1;
        }
    }
    func_1CD670(w);
    return 0;
}
