#include "types.h"

/* factory.bin overlay, 0x004FEAD0 -- allocate the panel's item array and
 * initialise every element, optionally binding each one to a scene node.
 * 492 bytes, 124 instructions, 8 conditional branches, 9 calls (br/ins 0.065).
 *
 * ★ TWIN of `factory_FactoryBeltTileGroupBuildObjs_4ff1e0` at ratio 0.944 on the mnemonic sequence --
 * found by ranking the OPEN population against ITSELF
 * ([[factory-open-population-similarity.md]]).  The whole difference is the
 * element STRIDE (0x40 here, 0x34 there), the four extra fields a 0x40 record
 * has, the setup callee and the two gp float blocks.
 *
 * ★ FRAME ORDER IS READ OFF THE LISTING, NOT GUESSED.  mwcc allocates stack
 * objects DOWNWARD in declaration order, so the object at the HIGHEST offset
 * is declared FIRST: `col` at 0x80, `name` at 0x70, `pos` at 0x60.  This is the
 * same rule `factory_FactoryPartsShowNoStockMsgMaybe_4efa60` measured (a 0x34 record at 0xE0 declared
 * before a 0xAC one at 0x30).
 *
 * ★ `cnt * 0x40` is strength-reduced to `sll $2, $16, 6`; the twin's `* 0x34`
 * comes out as the shift/add chain, which is why the two functions are the
 * same LENGTH despite the twin's record having four fewer fields to clear.
 */

typedef struct Node {
    u8  pad00[0x32];
    s16 f32;
} Node;

typedef struct Item {
    s8    f00;
    u8    pad01[0x1F];
    Node *f20;
    s8    f24;
    s8    f25;
    s8    f26;
    s8    f27;
    s16   f28;
    s16   f2A;
    u8    pad2C[0x4];
    s16   f30;
    s16   f32;
    s16   f34;
    s16   f36;
    s32   f38;
    s32   f3C;
} Item;                                         /* 0x40 */

typedef struct Panel {
    s32   f00;
    u8    pad04[0x6];
    s16   f0A;
    u8    pad0C[0x4];
    Item *f10;
} Panel;

extern f32 D_00480880;                          /* _gp - 0x48F0 */
extern f32 D_00480884;                          /* _gp - 0x48EC */
extern f32 D_00480888;                          /* _gp - 0x48E8 */
extern f32 D_0048088C;                          /* _gp - 0x48E4 */
extern f32 D_00480890;                          /* _gp - 0x48E0 */
extern f32 D_00480894;                          /* _gp - 0x48DC */
extern f32 D_00480898;                          /* _gp - 0x48D8 */
extern f32 D_0048089C;                          /* _gp - 0x48D4 */
extern u8  D_0050CE20[];

extern void  factory_FactoryPartGroupClearPool_4feac0(void);
extern void *func_100710(s32 p, s32 a, s32 b, s32 stride, s16 n);
extern void  func_1343B8(Item *it, u8 *name, s32 id, s32 i);
extern s32   func_14E1B0(s32 size, s32 heap);
extern Node *func_1890B0(s32 h, s32 id, f32 *pos, s8 *name, f32 *col, s32 a);
extern void  func_195150(Node *nd, Item *it);
extern s32   func_1E49B0(s32 w, s32 id, s32 a);
extern s32   func_1E7810(s32 t);
extern s32   func_201A90(void);

void factory_FactoryPartGroupBuildObjs_4fead0(Panel *o, s32 a)
{
    s32   h;
    f32   col[4];
    s8    name[0x10];
    f32   pos[4];
    Item *it;
    s8   *p;
    u32   n;
    s32   i;
    s32   t;
    s16   cnt;

    factory_FactoryPartGroupClearPool_4feac0();
    if (a != 0) {
        cnt = o->f0A;
        o->f10 = func_100710(func_14E1B0(cnt * 0x40 + 0x10, a), 0, 0, 0x40, cnt);
    }
    if (o->f10 != 0) {
        h = 0;
        t = func_1E49B0(func_201A90(), 0x2EE0, 0);
        if (t != 0) {
            h = func_1E7810(t);
        }
        p = name;
        n = 0x10;
        col[0] = D_00480880;
        col[1] = D_00480884;
        col[2] = D_00480888;
        col[3] = D_0048088C;
        if (p != 0) {
            do {
                *p = 0;
                n--;
                p++;
            } while (n != 0);
        }
        pos[0] = D_00480890;
        pos[1] = D_00480894;
        pos[2] = D_00480898;
        pos[3] = D_0048089C;
        it = o->f10;
        for (i = 0; i < o->f0A; i++, it++) {
            it->f24 = -1;
            it->f25 = 0;
            it->f26 = 0;
            it->f27 = 0;
            it->f28 = 0;
            it->f2A = 0;
            it->f30 = -1;
            it->f32 = -1;
            it->f34 = -1;
            it->f36 = -1;
            it->f38 = 0;
            it->f3C = 0;
            it->f00 = 0;
            it->f20 = 0;
            it->f24 = -1;
            it->f25 = 0;
            it->f26 = 0;
            it->f27 = 0;
            it->f28 = 0;
            it->f2A = 0;
            if (h != 0) {
                func_1343B8(it, D_0050CE20, o->f00, i);
                it->f20 = func_1890B0(h, o->f00, pos, name, col, a);
                if (it->f20 != 0) {
                    func_195150(it->f20, it);
                    it->f20->f32 = 0;
                }
            }
        }
    }
}
