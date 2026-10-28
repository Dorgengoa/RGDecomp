/* rgp:protos */
#define RGP_SELF_AiCmdEffectSetPos_2c2490 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Member of the 4-member clone group headed by EvCmdEffectSetRot_25cb30; the shape and
   every lever are documented there.  Members differ in the reporter and in which
   pair of argument readers is called.

   Read five arguments off the event VM cursor and hand three of them over as
   a stack vector.  The cursor is a POST-INCREMENT on an 8-byte element type,
   which is what puts each `addiu $18, $18, 0x8` in the CALL's delay slot; the
   vector's fourth word is an INTEGER zero (`sw $0`), not 0.0f. */

typedef struct R8 {
    u8 b[8];
} R8;

typedef struct Vec4 {
    f32 x;
    f32 y;
    f32 z;
    s32 w;
} Vec4;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 AiCmdEffectSetPos_2c2490(R8 *p)
{
    void *a;
    void *b;
    Vec4  v __attribute__((aligned(16)));

    a = GetEffectMgr_2d9040();
    b = ScriptSlotGetInt_2cc9c0(p++);
    v.x = ScriptSlotGetFloat_2cc9a0(p++);
    v.y = ScriptSlotGetFloat_2cc9a0(p++);
    v.z = ScriptSlotGetFloat_2cc9a0(p++);
    v.w = 0;
    EffectSetPosById_2e0b20(a, b, &v);
    return 1;
}
