/* rg-override: replaces game/src/main/ai/AiCmdMapRaycast_2c28e0.c sha256 2a94efe2e3294bd17cc1d0f4ee0a6217966887c960561a5253440567cd88ab9e
 * why: in both raycast scopes `lo` / `hi` are ONE {lo, hi} box in retail's frame (first scope sp+0x6090 / 0x60A0):
 * MapEvCollectCollPolysMaybe_1ff270(.., &lo, ..) reaches 0x20 bytes through &lo.  Declared as two locals
 * (nested scopes, missed by the protos stack-block rule) the callee got hi only while clang placed it
 * right above lo (static census tools/census/localsize_census.py, lane localsize 2026-11-09).
 * Each pair is now one struct, retail's order. */
/* rgp:protos */
#define RGP_SELF_AiCmdMapRaycast_2c28e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct V4 { f32 x, y, z, w; } V4;
typedef struct Hit { u8 b[0x6000]; } Hit;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 AiCmdMapRaycast_2c28e0(u64 *p, s32 n)
{
    f32 r;
    s32 k;
    s32 cnt;
    s32 res;

    if (n >= 11) {
        Hit buf __attribute__((aligned(16)));
        V4 a __attribute__((aligned(16)));
        V4 b __attribute__((aligned(16)));
        V4 out __attribute__((aligned(16)));
        struct { V4 lo; V4 hi; } rgp_box __attribute__((aligned(16)));   /* rg-override: one retail {lo, hi} box (lo, then hi 16 bytes above) */

        a.x = ScriptSlotGetFloat_2cc9a0(p++);
        a.y = ScriptSlotGetFloat_2cc9a0(p++);
        a.z = ScriptSlotGetFloat_2cc9a0(p++);
        b.x = ScriptSlotGetFloat_2cc9a0(p++);
        b.y = ScriptSlotGetFloat_2cc9a0(p++);
        b.z = ScriptSlotGetFloat_2cc9a0(p++);
        b.w = 1.0f;
        a.w = 1.0f;
        k = ScriptSlotGetInt_2cc9c0(p++);
        r = VecDistance_13d3d0(&a, &b);
        VecMinMax_1cb570(&rgp_box.lo, &rgp_box.hi, &a, &b);
        rgp_box.hi.w = 1.0f;
        rgp_box.lo.w = 1.0f;
        rgp_box.hi.x -= r;
        rgp_box.hi.y -= r;
        rgp_box.hi.z -= r;
        rgp_box.lo.x += r;
        rgp_box.lo.y += r;
        rgp_box.lo.z += r;
        cnt = MapEvCollectCollPolysMaybe_1ff270(&buf, 0x100, &rgp_box.lo, -1);
        res = MeshRaycastWrapper_16f610(&buf, cnt, &a, &b, &out, 1, k);
        if (res >= 0) {
            ScriptSlotStoreIntRef_2cc900(p++, 1);
        } else {
            ScriptSlotStoreIntRef_2cc900(p++, 0);
        }
        ScriptSlotStoreFloatRef_2cc8e0(p++, out.x);
        ScriptSlotStoreFloatRef_2cc8e0(p++, out.y);
        ScriptSlotStoreFloatRef_2cc8e0(p, out.z);
    } else {
        Hit buf __attribute__((aligned(16)));
        V4 a __attribute__((aligned(16)));
        V4 b __attribute__((aligned(16)));
        V4 out __attribute__((aligned(16)));
        struct { V4 lo; V4 hi; } rgp_box __attribute__((aligned(16)));   /* rg-override: one retail {lo, hi} box (lo, then hi 16 bytes above) */

        a.x = ScriptSlotGetFloat_2cc9a0(p++);
        a.y = ScriptSlotGetFloat_2cc9a0(p++);
        a.z = ScriptSlotGetFloat_2cc9a0(p++);
        b.x = ScriptSlotGetFloat_2cc9a0(p++);
        b.y = ScriptSlotGetFloat_2cc9a0(p++);
        b.z = ScriptSlotGetFloat_2cc9a0(p++);
        b.w = 1.0f;
        a.w = 1.0f;
        r = VecDistance_13d3d0(&a, &b);
        VecMinMax_1cb570(&rgp_box.lo, &rgp_box.hi, &a, &b);
        rgp_box.hi.w = 1.0f;
        rgp_box.lo.w = 1.0f;
        rgp_box.hi.x -= r;
        rgp_box.hi.y -= r;
        rgp_box.hi.z -= r;
        rgp_box.lo.x += r;
        rgp_box.lo.y += r;
        rgp_box.lo.z += r;
        cnt = MapEvCollectCollPolysMaybe_1ff270(&buf, 0x100, &rgp_box.lo, -1);
        res = MeshRaycastWrapper_16f610(&buf, cnt, &a, &b, &out, 1, 0);
        if (n == 9) {
            ScriptSlotStoreFloatRef_2cc8e0(p++, out.x);
            ScriptSlotStoreFloatRef_2cc8e0(p++, out.y);
            ScriptSlotStoreFloatRef_2cc8e0(p, out.z);
        } else if (n == 7) {
            if (res < 0) {
                ScriptSlotStoreIntRef_2cc900(p, 0);
            } else {
                ScriptSlotStoreIntRef_2cc900(p, 1);
            }
        }
    }
    return 1;
}
