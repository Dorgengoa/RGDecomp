#include "types.h"
/* normal 0x00500780 -- re-skins the 0x30/0x33 widgets when the selected index
 * changes, then positions 0x2B at `index * 0x7D + 0x73`.  The index is held in
 * a local for the compare and the first call and RE-READ off the object
 * afterwards -- retail issues a second `lh 0x10($16)`, which is the
 * recompute-vs-reuse discrimination read off the listing.
 * `sll 5 / subu / sll 2 / addu` is mwcc strength-reducing `* 0x7D`. */

typedef struct Obj { u8 pad000[0x10]; s16 f010; } Obj;

extern void *D_00484454;          /* gp - 0xD1C */
extern void *D_0048449C;          /* gp - 0xCD4 */
extern s16   D_004844DC;          /* gp - 0xC94 */
extern s16   D_004844E0;          /* gp - 0xC90 */
extern f32   D_0047D280;          /* gp - 0x7EF0 */
extern f32   D_0047D278;          /* gp - 0x7EF8 */
extern const u8 D_00527020[];

extern s32  normal_BtlChgPageGetMember_505f90(void *a);
extern void normal_BtlChgPageSetMember_505fa0(void *a, s16 n);
extern void normal_BtlChgMenuSetMemberFace_501d40(s32 id, s16 n);
extern void normal_FieldHudPanelSelectHide_4f4eb0(const void *a, s16 n);
extern void func_2907A0(void *a, s32 id, f32 x);
extern void func_290690(void *a, s32 id, f32 x, f32 y, f32 z);
extern void func_290F50(void *a, s32 id, s32 c, s32 d, s32 e, f32 x);

s32 normal_BtlChgMenuCommandCursorMoveCb_500780(Obj *p)
{
    s16 n;

    n = p->f010;
    if (n != normal_BtlChgPageGetMember_505f90(D_00484454)) {
        normal_BtlChgMenuSetMemberFace_501d40(0x30, n);
        func_2907A0(D_0048449C, 0x30, 0.0f);
        func_290690(D_0048449C, 0x30, 1.0f, D_0047D280, -1.0f);
        normal_FieldHudPanelSelectHide_4f4eb0(D_00527020, p->f010);
        func_2907A0(D_0048449C, 0x33, 0.0f);
        func_290690(D_0048449C, 0x33, 1.0f, D_0047D280, -1.0f);
        D_004844DC = 0;
        D_004844E0 = -1;
    }
    normal_BtlChgPageSetMember_505fa0(D_00484454, p->f010);
    func_290F50(D_0048449C, 0x2B,
                normal_BtlChgPageGetMember_505f90(D_00484454) * 0x7D + 0x73, 0xDB, 0,
                D_0047D278);
    return 1;
}
