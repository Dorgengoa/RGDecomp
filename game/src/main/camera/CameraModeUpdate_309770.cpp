/* rgp:protos */
#line 1
#include "types.h"

/* The camera mode switch: pick the driver for this frame.

   Before dispatching it hands the camera a pair of axis signs read out of the
   options block -- bit 1 flips one axis, bit 2 the other -- so this is where
   the invert-look settings reach the camera.

   The mode comes from the camera's own byte at +0x26C unless that is -1, in
   which case CameraModeGetCurrent_309370 resolves it from the active mode record. A camera
   with neither (-1 and no record) just lerps and returns.

   ★ Mode 5 is the town's driver, CameraModeTrackUpdate_307b30 -> CameraTrackUpdate_305960, which is the
   link the camera investigation spent a while chasing. Mode 14 is the only
   case that SKIPS the whole tail: it uploads the view matrix and returns.

   The tail re-reads the mode and lerps unless it is 5 -- mode 5 has already
   done its own chase inside the driver.

   ⚠ CameraModeGetCurrent_309370 is prototyped here as returning s8: retail sign-extends its
   result at both call sites with `dsll32/dsra32 24`, which is what a `signed
   char` return does. The matched definition returns the same byte as s32.

   MATCHED on b210, from 98.64% / 11 bad words. Three separate defects, and
   the objdiff percentage ranked none of them usefully:

   1. SEVEN of the eleven words were the two sign locals mirrored across
      $f20/$f21. The lever is DECLARATION ORDER, and it runs BACKWARDS: mwcc
      gives the callee-saved FPRs out in reverse declaration order here, so
      `signB` must be declared FIRST for `signA` to land in $f20. (The old note
      that "swapping the two sign locals costs 1.5%" was about swapping the
      ASSIGNMENTS, which is a different edit and is still wrong.)
   2. `CameraApplyLookAt_1773d0` was prototyped `(void)` and called with no
      argument. It takes the camera -- our own matched definition says so. The
      tell is in the branch, not the call: retail's case-14 test is
      `beql` with `daddu $4, $17, $0` in the DELAY SLOT, which is the case
      body's argument setup MOVED out of a block that has one predecessor.
      A block whose first instruction has migrated into a likely branch's
      delay slot is an argument setup, so the case body takes an argument.
   3. The last two words -- retail's `bne` + bare `nop` where we emitted `bnel`
      duplicating the switch's first `li $3, 0x12` -- are an explicit `else`.
      Writing the fall-through assignment as `else { mode = self->mode; }`
      rather than seeding `mode` before the `if` suppresses the duplication.
      ⚠ This is a second counterexample to the old "an explicit `else` changes
      nothing" note. Also measured: `goto dispatch` past the switch (2 words,
      unchanged), inverting the hasMode test into if/else (12), and folding the
      two guards into `mode == -1 && !hasMode` (three words LONG).

   ⚠ Declaring `mode` as s8 costs 2.3% -- extra sign extensions through the
   switch -- and is still wrong.

   ★ The switch's comparison order is the SOURCE order reversed, group by
   group: retail tests 18, 14, (32, 31), (13..9), (17..15), (8..0), which is
   what the case order below produces. */

typedef struct Camera {
    u8 pad000[0x268];
    s32 hasMode;     /* +0x268 */
    s8 mode;         /* +0x26C, -1 = ask CameraModeGetCurrent_309370 */
} Camera;

typedef struct Options {
    u8 pad00[0x1A];
    s16 flags;       /* +0x1A, bit 1 and bit 2 are the axis inversions */
} Options;

typedef struct Config {
    u8 pad00[0xC];
    Options *options; /* +0x0C */
} Config;

extern "C" {
extern void *GetCurrentScene_1f5be0(void);
extern f32 GameSceneGetTimeStep_1ceba0(void *owner);
extern Config *GetGameData_1fede0(void);
extern void CameraSetAxisSigns_160470(Camera *self, f32 a, f32 b);
extern s8 CameraModeGetCurrent_309370(Camera *self);
extern void CameraChaseStep_161b60(Camera *self, f32 dt);
extern void CameraShakeTimerStep_305860(Camera *self, f32 dt);
extern void CameraApplyLookAt_1773d0(Camera *self);

extern void CameraFollowLeaderStepMaybe_3081e0(Camera *self, void *owner, s32 a, s32 b, s32 c, s32 d);
extern void CameraFirstPersonUpdate_307f00(Camera *);
extern void CameraModePresetToggleUpdate_307e50(Camera *self, void *owner);
extern void CameraModeUpdateNop_307e40(void);
extern void CameraTwoTargetFollow_307b40(Camera *self, void *owner);
extern void CameraModeTrackUpdate_307b30(Camera *self, void *owner);
extern void CameraModeUpdateNop_307b20(void);
extern void CameraModeUpdateNop_307b10(void);
extern void CameraModeUpdateNop_307b00(void);
extern void CameraModeInsectBattleUpdate_307ac0(void);
extern void CameraModeFactoryUpdateThunk_3679c0(void);
extern void CameraModeUpdateNop_307aa0(void);
extern void CameraModeDebugFreeUpdate_307af0(Camera *, void *, int, int);
extern void CameraModeLockTargetUpdateMaybe_3062e0(Camera *self, void *owner);
extern void CameraTargetFollowUpdate_307340(Camera *self, void *owner);
extern void CameraModeZoomUpdate_306200(Camera *self, void *owner);
}

extern "C" void CameraModeUpdate_309770(Camera *self)
{
    void *owner;
    f32 dt;
    f32 signB;
    f32 signA;
    s16 flags;
    s32 mode;

    owner = GetCurrentScene_1f5be0();
    dt = GameSceneGetTimeStep_1ceba0(owner);

    signB = 1.0f;
    signA = signB;
    flags = GetGameData_1fede0()->options->flags;
    if (flags & 2) {
        signA = -1.0f;
    }
    if (flags & 4) {
        signB = -1.0f;
    }
    CameraSetAxisSigns_160470(self, signA, signB);

    if (self->mode == -1) {
        if (self->hasMode == 0) {
            CameraChaseStep_161b60(self, dt);
            return;
        }
        mode = CameraModeGetCurrent_309370(self);
    } else {
        mode = self->mode;
    }

    switch (mode) {
    case 0:
        CameraFollowLeaderStepMaybe_3081e0(self, owner, 0, 0, 0, 0);
        break;
    case 1:
        CameraFirstPersonUpdate_307f00(self);
        break;
    case 2:
        CameraModePresetToggleUpdate_307e50(self, owner);
        break;
    case 3:
        CameraModeUpdateNop_307e40();
        break;
    case 4:
        CameraTwoTargetFollow_307b40(self, owner);
        break;
    case 5:
        CameraModeTrackUpdate_307b30(self, owner);
        break;
    case 6:
        CameraModeUpdateNop_307b20();
        break;
    case 7:
        CameraModeUpdateNop_307b10();
        break;
    case 8:
        CameraModeUpdateNop_307b00();
        break;
    case 15:
        CameraModeInsectBattleUpdate_307ac0();
        break;
    case 16:
        CameraModeFactoryUpdateThunk_3679c0();
        break;
    case 17:
        CameraModeUpdateNop_307aa0();
        break;
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
        CameraModeDebugFreeUpdate_307af0(self, owner, 0, 0);
        break;
    case 31:
        CameraModeLockTargetUpdateMaybe_3062e0(self, owner);
        break;
    case 32:
        CameraTargetFollowUpdate_307340(self, owner);
        break;
    case 14:
        CameraApplyLookAt_1773d0(self);
        return;
    case 18:
        CameraModeZoomUpdate_306200(self, owner);
        break;
    }

    if (CameraModeGetCurrent_309370(self) != 5) {
        CameraChaseStep_161b60(self, dt);
    }
    CameraShakeTimerStep_305860(self, dt);
}
