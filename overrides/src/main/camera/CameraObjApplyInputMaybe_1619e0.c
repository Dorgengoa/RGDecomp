/* rg-override: replaces game/src/main/camera/CameraObjApplyInputMaybe_1619e0.c sha256 e7aca1c43453d885dd2166e4c4e99083a8bc212e8dda357f42a4905cd90e51f6
 * why: mouse camera (docs/INPUT.md "Mouse camera implementation"): add the latched look record
 * to the orbit input (modes 0 / 2 / 18); without a record the body is the generated one */
/* rgp:protos */
#define RGP_SELF_CameraObjApplyInputMaybe_1619e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x214];
    s32 unk214;
    u8 pad218[0x244 - 0x218];
    f32 unk244;
    f32 unk248;
    f32 unk24C;
    s32 unk250;
    s32 unk254;
    s32 unk258;
} Obj0Arg0;

typedef struct {
    f32 a;
    f32 b;
    s32 c;
} In;

/*rgp*/
/*rgp*/
/*rgp*/
/* rg-override: the mouse look record latched this frame (src/game/rg_game_main.c):
 * Q12 radians, yaw > 0 = turn right, pitch > 0 = look up; returns 0 when there is
 * none (Original, no motion), and consumes it (once per frame) */
extern int rg_game_look_take(s32 *yaw, s32 *pitch, int site);
/* s.a > 0 (the stick pushed right with the game's invert X off: unk258 = +1)
 * swings the camera right around the leader, i.e. the VIEW turns left (measured:
 * docs/INPUT.md "Mouse camera implementation"), so yaw > 0 (turn the view right,
 * the PC mouse-look convention) subtracts.  s.b > 0 raises the eye (looks
 * further down), so pitch > 0 (look up) lowers it.  The orbit "pitch" is the
 * eye height offset prm.x10 in world units (clamped to [-15, 40] by the
 * orbit): 1 rad of look = 20 units (CONTROLS-AUDIT.md section 6). */
#define RG_LOOK_YAW_RAD (-1.0f / 4096.0f)
#define RG_LOOK_HEIGHT_UNITS (-20.0f / 4096.0f)

void CameraObjApplyInputMaybe_1619e0(Obj0Arg0 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    In s __attribute__((aligned(16)));
    f32 f;

    s.b = 0.0f;
    f = 0.0f;
    s.a = 0.0f;
    s.c = 0;
    if (arg1 != 0) {
        if (!(arg0->unk214 & 2)) {
            f = arg0->unk244 * SysParamTableGetFloat_15fe50(arg1, 6);
        }
        if (!(arg0->unk214 & 1) && ((SysParamTableGetInt_15fe80(arg1, 3) == 0) || (SysParamTableGetInt_15fe80(arg1, 2) == 0))) {
            if (SysParamTableGetInt_15fe80(arg1, 3) != 0) {
                f = arg0->unk24C;
            } else if (SysParamTableGetInt_15fe80(arg1, 2) != 0) {
                f = -arg0->unk24C;
            }
        }
        s32 rg_locked = arg0->unk250 > 0;   /* rg-override: input lock timer (also stops mouse yaw) */
        if (arg0->unk250 > 0) {
            arg0->unk250--;
            f = 0.0f;
        }
        s.a = f * (f32)arg0->unk258;
        s.b = (f32)arg0->unk254 * (arg0->unk248 * -SysParamTableGetFloat_15fe50(arg1, 7));
        s.c = SysParamTableGetInt_15fe80(arg1, 4);
        {   /* rg-override: mouse camera */
            s32 ly, lp;
            if (rg_game_look_take(&ly, &lp, 0)) {
                if (ly != 0 && !(arg0->unk214 & 2) && !rg_locked) {
                    s.a = s.a + (f32)ly * RG_LOOK_YAW_RAD;
                }
                if (lp != 0) {
                    s.b = s.b + (f32)lp * RG_LOOK_HEIGHT_UNITS;
                }
            }
        }
    }
    CameraObjOrbitControlMaybe_161260(arg0, &s, arg2, arg3, arg4);
}
