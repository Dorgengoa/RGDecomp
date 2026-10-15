#include "types.h"
/* normal 0x004FD140 -- the equip-compare panel's confirm handler.  The
 * func_28E170 menu call is issued twice (once inside the `b` arm, once
 * unconditionally) and its return is the three-way action code 1/2/other.
 *
 * The four `lwc1`/`swc1` at sp+0x30 are the {0,1,2,3} index table copied out
 * of small data one word at a time; sp+0x30 is then indexed by the record's
 * f12.  `lui $2,0xBF80 / mtc1 $2,$f15` is an inline -1.0f. */

typedef struct Rec { u8 pad00[0x12]; s16 f12; } Rec;
typedef struct Ent { u8 pad00[0xC]; s32 f0C; } Ent;

extern const u8 D_004B2570[];

extern f32   D_0047D278;          /* gp - 0x7EF8 */
extern f32   D_0047D35C;          /* gp - 0x7E14 */
extern f32   D_0047D51C;          /* gp - 0x7C54 */
extern f32   D_00480580;          /* gp - 0x4BF0 */
extern f32   D_00480584;          /* gp - 0x4BEC */
extern f32   D_00480588;          /* gp - 0x4BE8 */
extern f32   D_0048058C;          /* gp - 0x4BE4 */
extern void *D_00484498;          /* gp - 0xCD8  */
extern void *D_0048449C;          /* gp - 0xCD4  */
extern void *D_004844A0;          /* gp - 0xCD0  */
extern s16   D_004844E4;          /* gp - 0xC8C  */

extern Ent  *func_1FEDE0(void);
extern void  func_289EF0(s32 a);
extern s32   func_28E170(void *p, const u8 *q, s32 c, s32 d);
extern void  func_28EA90(void *p, s32 id, s32 a);
extern Rec  *func_28EC60(void *p);
extern void  func_28EDE0(void *p, s32 id, s32 a);
extern void  func_2904E0(void *p, u16 id, f32 x, f32 y, f32 z, f32 w, f32 v);
extern void  func_2905B0(void *p, u16 id, f32 x, f32 y, f32 z, f32 w);
extern void  func_3D5F50(s32 a, s32 b);

s32 normal_BtlChgMenuTacticsSelectState_4fd140(void *a, s32 b)
{
    s32  r;
    Rec *o;
    Ent *e;
    f32  v[4];

    if (b != 0) {
        func_28EA90(D_004844A0, 0x55F6, 1);
        func_28E170(D_004844A0, D_004B2570, 5, 0);
        func_28EC60(D_004844A0)->f12 = 0;
    }
    r = func_28E170(D_004844A0, D_004B2570, 5, 0);
    o = func_28EC60(D_004844A0);
    if (r == 2) {
        func_289EF0(6);
        func_28EDE0(D_00484498, 0x560A, 0);
    } else if (r == 1) {
        v[0] = D_00480580;
        v[1] = D_00480584;
        v[2] = D_00480588;
        v[3] = D_0048058C;
        e = func_1FEDE0();
        if (e == 0) {
            return 0;
        }
        func_3D5F50(e->f0C, *(s32 *)&v[o->f12]);
        func_2905B0(D_0048449C, 0x38, D_0047D35C, D_0047D35C, D_0047D35C, -1.0f);
        func_2904E0(D_0048449C, 0x38, D_0047D278, D_0047D278, D_0047D278, -1.0f,
                    D_0047D51C);
        func_289EF0(3);
        if (o->f12 == 2) {
            D_004844E4 = 2;
            func_28EDE0(D_00484498, 0x560B, 0);
        } else {
            func_28EDE0(D_00484498, 0x560A, 0);
        }
    }
    return 1;
}
