/* rgp:protos */
#define RGP_SELF_insect_InsectPieceAttachSubModel_515210 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00515210 -- 188 bytes, 48 instructions, 6 calls, 1 conditional
 * branch.  A guarded "reset the widget" helper.
 *
 * The four gp floats at _gp-0x4160.._gp-0x4154 (0x00481010..0x0048101C) go
 * into a contiguous 4-float local and are the [[mwcc-float-table-struct-copy]]
 * shape: ONE struct copy through a CAST, never four element assignments.
 * The first three slots are then zeroed, and the address escapes into
 * func_151110, which is what keeps the dead stores alive.
 *
 * Every call result gets its OWN named local ([[NAME THE CALL]]) -- the two
 * inner results feed the next call's $4/$5 in retail's order.
 */

typedef struct Sub {
    u8  pad000[0x448];
    f32 f448;                       /* +0x448 */
} Sub;

typedef struct Obj {
    u8   pad000[0x58];
    Sub *f58;                       /* +0x58 */
    u8   pad05C[0x6C - 0x5C];
    s16  f6C;                       /* +0x6C */
} Obj;

typedef struct V4 { f32 x, y, z, w; } V4;
typedef struct V2 { f32 x, y; } V2;

extern f32 D_00481010;
extern f32 D_00481014;
extern f32 D_00481018;
extern f32 D_0048101C;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectPieceAttachSubModel_515210(Obj *o, s32 k)
{
    f32   v[4] __attribute__((aligned(16)));
    void *a;
    void *b;
    s32   c;
    s32   d;
    s32   n;
    Sub  *s;

    if (o->f58 != 0) {
        n = o->f6C;
        a = GetCurrentScene_1f5be0();
        b = ObjRecGetLiveObject_1c4a90(a, n);
        c = ModelFindFrameIndexByName_151220(b, k);
        d = ((s32)ModelGetFrame_1511f0(b, c));
        ModelAttachRootFrames_1515b0(o->f58, d);
        s = o->f58;
        *(V2 *)&v[0] = *(V2 *)&D_00481010;
        *(V2 *)&v[2] = *(V2 *)&D_00481018;
        v[0] = 0.0f;
        v[1] = 0.0f;
        v[2] = 0.0f;
        ModelSetPos_151110(s, v);
        o->f58->f448 = 1.0f;
    }
}
