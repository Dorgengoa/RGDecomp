# Controls: source audit and P6 design

Date: 2026-10-12. Source: the official decomp at commit `675c07f` (the same snapshot as
`game/`, see `game/SNAPSHOT.txt`). Paths are `src/...` in that tree, which is
`game/src/...` in the port. This is a read-only design audit: nothing was run and no
code was changed. It covers PLAN.md P6 "Controls" and the open items in docs/INPUT.md
(role names, pressure, real mouse camera, prompts). Claims come from function bodies and
data values. Where a role is read off a flag whose consumer was not traced, the table says
**inferred**.

Button names below are the game's decoded word (`PadReadData_184df0`,
`((d[2] << 8) | d[3]) ^ 0xFFFF`, PADMC.md): L2 0x1, R2 0x2, L1 0x4, R1 0x8, Triangle 0x10,
Circle 0x20, Cross 0x40, Square 0x80, Select 0x100, L3 0x200, R3 0x400, Start 0x800,
Up 0x1000, Right 0x2000, Down 0x4000, Left 0x8000. Pad objects: `D_004B2570` = port 0
(`GetPad0_1c6c60`), `D_004B27E0` = port 1 (`GetPad1_1c6c50`).

## Summary

1. **One pad service, edge-based, once per logical tick.** `PadUpdate_1843a0` copies
   `cur` to `prev`, reads the report, applies the stick-to-d-pad option and key repeat, and
   cancels opposite d-pad directions. Triggered = `cur & ~prev`, released = `~cur & prev`,
   held = `cur`. There are no time-based timers: repeat delays count **PadUpdate calls**.
2. **No pressure.** The game never calls `scePadEnterPressMode`/`scePadSetButtonInfo`, and
   `PadReadData_184df0` reads only report bytes 0–7. Every action is digital. L2/R2 are
   on/off buttons. Nothing depends on pressure, so the 0/255 pressure the adapter writes is
   exact.
3. **Sticks: one fixed dead zone, applied by the game.** Every stick reader maps the raw
   byte with `|v − 128| < 50 → 0`, else `(v ∓ 49/50) · 128 / 78` (so the game's own dead
   zone is 50/128 ≈ 39% per axis, square, not radial). The port's `input.deadzone_*`
   (default 25%) runs **before** this, so the effective dead zone is the larger of the two.
4. **The game already has a logical-input table, but no remap UI.** `PadBindingsUpdate_15fcd0`
   fills 128 int slots (`held/triggered/released` of a button mask) and 32 float slots
   (stick axes) every tick from defaults in `D_0044B020`/`D_0044B270`. Only the orbit camera
   and event scripts read it; player control, battle and menus test raw masks directly. So
   remapping belongs in the port's report adapter (as INPUT.md already does), not in that
   table.
5. **Options the game has:** camera invert X and invert Y (both read for every camera
   mode) and a camera-type toggle (also on Select). No button remap and no vibration
   option.
6. **The US build never vibrates.** The driver is present, but nothing in the source
   turns a motor on (section 7).
7. **Prompts** are in-text tags drawn from one gaiji texture, `gaiji2`, so one texture
   swap per device covers almost all of them (section 8).
8. **Mouse camera is feasible** at one choke point per camera mode. Camera yaw is game state
   (player movement is camera-relative), so mouse deltas must be tick-quantised and recorded
   like pad input.

## 1. The pad service

### Read path

| Step | Function | Facts |
| --- | --- | --- |
| Boot | `PadOpenPorts_1c6bf0` | `PadSysInit_185080` (sema `D_0047E03C`, `scePadInit(0)`), `PadPortOpen_184ed0` port 0 and 1 (DMA buffers `D_004B2A80`/`D_004B2B80`), `PadWaitReady_1849e0(port 0)`. |
| Connection | `PadUpdateConnection_184a50` | Phase machine: digital pad → `scePadSetMainMode(1, 3)` (analog, **locked**); analog → `scePadInfoAct(-1)` then `scePadSetActAlign {0, 1, FF×4}` (actuator 0 = small motor, 1 = large); steady state reads. If the mode id is not 7 (analog) the sticks are forced to 0x80; on any failure buttons = 0 and sticks centred. |
| Report | `PadReadData_184df0` (port override, 0x20-byte buffer) | Bytes 0–7 only: status, mode, buttons, RX RY LX LY. |
| Service | `PadUpdate_1843a0` | `prev = cur`, read, optional key-capture record/playback (below), stick→d-pad, repeat, opposite-direction cancel (Up+Down, Left+Right both cleared), toggles parity `D_0048122C`. |
| Readers | `PadIsHeld_183a20`, `PadIsTriggered_1839f0`, `PadIsReleased_1839c0`, `PadGetHeldMask_183d30`, `PadGetTriggeredMask_183d00`, `PadGetReleasedMask_183cd0`, `PadIsRepeatTriggered_183dd0`, `PadGetAnalog{LX,LY,RX,RY}_18xxxx` (int −128..128), `PadGetAnalog{LX,LY,RX,RY}Norm_183xxx` (float −1..1), `PadAnyInput_183e80` | All return 0 while pad `+0x24C` is set; nothing in the source sets it (dead input lock). |
| Analog required | `PadIsAnalogMode_184960` | State STABLE/FINDCTP1 and `scePadInfoMode(…,1,0) == 7`. When false, `GameFrameUpdate_27c4c0` raises pause reason 4 (port 1: 5), cleared by Cross in `PauseStepUpdate_2f5fb0`; movies (`MoviePlayModal_267c60`) and loading (`LoadingScreenFrame_3435d0`) have the same gate. |

Pad struct (`0x264` bytes): `+0x4` cur report (buttons, LY, LX, RY, RX as s32, then the
vibration block), `+0x5C` prev report, `+0xB4/+0xB8` port/slot, `+0xC0` repeat block
(`mask`, `active`, `count[32]`, `delay[32]`, `interval[32]`), `+0x248` stick→d-pad
threshold, `+0x24C` input lock, `+0x254` vibration enable, `+0x258` vibration watchdog,
`+0x25C/+0x260` key-capture mode/index. Note that `PadUpdate_1843a0`'s local struct names
the stick fields `lx, ly` in the wrong order; the getters are right (LX at `+0xC`, LY at
`+0x8`, RX at `+0x14`, RY at `+0x10`).

### When it runs (edge semantics)

- `MainLoop_1c2c10` calls `PadUpdate_1843a0` for **both** ports once per outer frame, after
  the mode callback and `GfxEndFrame_141c20`, plus port 0 once per mode change.
- `GameFrameUpdate_27c4c0` calls `PadUpdate(port 0)` again when the task list changed, and
  `PauseStepUpdate_2f5fb0`, `FieldExploreModeUpdate_2833a0`, `AbilityModeRun_2790e0`,
  `TransporterWarpModeUpdate_27f140`, `LoadingScreenFrame_3435d0`, `MoviePlayModal_267c60`,
  `title_TitleFrameStep_4f0b20` call it at their own transitions to **consume** an edge
  (so the press that closed a menu does not also act in the field).
- Frame pacing: gameplay runs at a two-VBlank interval, menus/title at one
  (docs/FRAMERATE-AUDIT.md). So "one tick" is about 33 ms in the field and 17 ms in
  menus, and repeat delays and timeouts (below) change real-time length between the two.
- Consequence for the port: edges are per PadUpdate call, not per VBlank. The press latch
  (`input.min_press_fields` = 2) is the right minimum at a two-VBlank interval; a host
  must never call `PadUpdate_1843a0` more than the game does (it would eat edges).

### Repeat and stick→d-pad

- `PadSetRepeat_183d50(pad, mask, delay, interval)` (both clamped to ≥ 2) arms per-button
  auto-repeat. While held, `count` increments per PadUpdate; at `delay` the button becomes
  "active"; then every `interval` calls the bit is **cleared from `cur` for one call**, so
  the next call sees a fresh trigger. `PadIsRepeatTriggered_183dd0` reports the active
  bit. Repeat is therefore implemented as synthetic release/press pairs inside the game, and
  it is driven by tick count.
- `PadSetStickDpadThreshold_183950(pad, t)` makes the left stick press the d-pad bits when
  the game-mapped value exceeds `t` (0..128). `PadClearStickDpadThreshold_183940` turns it
  off. Menus set it on open and clear it on close (callers in `main/menu`, every overlay's
  menu open/close).
- `PadSaveRepeatConfig_1838f0` / `PadApplyRepeatConfig_183800` / `PadRestartRepeat_28e900`
  save and restore the whole repeat block (used by `MenuGridCursorInput_28e170` and text
  entry).
- Typical values: see section 4 (menus).

Port rule: the host's own UI auto-repeat (`rg_ui_nav_update`, 400/90 ms) is for the
overlay only. The game's repeat must stay the game's; the adapter must deliver a held
button as held, never pulse it.

### Key capture (dormant)

`PadUpdate_1843a0` mode 1 records `{buttons, LY, LX, RY, RX}` (6 bytes) per call to the
fixed EE address `0x3000000`; mode 2 plays them back. `MainLoop_1c2c10` dumps the buffer to
`host0:key_cap.bin` (`PadKeyCapDump_1837d0`) when `D_00481550 == 1`. No C source sets
`D_00481550` or pad `+0x25C` to a non-zero value (`SysBootInit_1c2ee0` zeroes it;
`GetKeyCapModeMaybe_1c3540` only reads it, in `title_TitleSessionInit_4f0cb0` and
`LoaderUseSyncRead_1cd890`). Treat it as dead; the port's input scripts replace it. If it
is ever enabled, `0x3000000` must be mapped through the port's address layer.

### Idle timer

`PadIdleTimerUpdate_2f5a60` adds the scene timestep to `D_0048277C` unless
`PadAnyInput_183e80` (any button, or any stick past the game's dead zone). Only
`title_TitleDemoMenuTick_4ea000` reads it (attract demo). Mouse motion that is not mapped
to a stick will not reset it.

## 2. The game's logical-input table

`GameFrameUpdate_27c4c0` → `PadBindingsUpdateFromSysParams_2f75f0` →
`PadBindingsUpdate_15fcd0(GetSysParamTable_1c6be0() = D_004B2C80, port 0)` every tick:

- floats `+0..+0xC` = RX, RY, LX, LY (normalised);
- 128 int slots at `+0x10` (`{value, key}`), `key = mode | mask`, mode `0x00000` held,
  `0x10000` triggered, `0x20000` released;
- 32 float slots at `+0x410` (`{value, type}`), type 1 LX, 2 LY, 3 RX, 4 RY.

Defaults (`SysParamTableLoadDefaults_1c6b20` from `D_0044B020` triplets `{slot, mode, mask}`
and `D_0044B270` pairs `{slot, type}`):

| Slots | Binding |
| --- | --- |
| 0, 0x10, 0x14, 0x32, 0x66, 0x67, 0x68, 0x78 | Cross triggered |
| 0x13, 0x38, 0x79 | Cross held |
| 0x3A | Cross released |
| 1, 0x11, 0x15, 0x34 | Circle triggered |
| 0x16, 0x17, 0x33, 0x3B, 0x6B, 0x6D | Square triggered |
| 0x18, 0x7A | Square held |
| 5 | Triangle triggered |
| 2, 0x35, 0x36 | R1 held |
| 0x12 | R1 triggered |
| 0x39 | R1 released |
| 3 | L1 held |
| 4, 0x64, 0x69 | R2 triggered |
| 0x65, 0x6A | L2 triggered |
| 6 | R3 triggered |
| 7–0xA | Up, Down, Right, Left triggered |
| 0xB–0xE | Up, Down, Right, Left held |
| 0xF | Start triggered |
| 0x37, 0x6C | Select triggered |
| float 0–3 | LX, LY, RX, RY; float 4 LY, 5 LX, 6 RX, 7 RY |

Readers: `CameraObjApplyInputMaybe_1619e0` (slots 2, 3, 4, float 6, 7) and the event-script
command `EvCmdSysParamGetInt_25d240` (any slot, by number from script data). Nothing writes
the table after the defaults. **So there is no in-game remap, and the table is not a
useful remap point**: it covers the orbit camera and scripts only, while player control,
battle, menus and minigames test raw masks.

Event scripts also read raw masks: `EvCmdPadGetHeld_26a150`, `EvCmdPadGetTriggered_26a100`,
`EvCmdPadGetReleased_26a0b0`, `EvCmdPadIsHeld_2440e0`, `EvCmdPadIsTriggered_244130`,
`EvCmdPadGetTriggered_2420b0`, `EvCmdPadGetAnalog_242100`/`_269fe0`, and two "logical"
tests, `EvCmdPadCheckButton_242420` / `EvCmdPadTestTriggered_2676f0` (kind 0 = Circle,
1 = Cross or Triangle, 2 = Square, 3 = Select; the latter ORs port 1 because it tests the
*address* of `IsPad2Enabled_2882c0`, always true). Script data therefore embeds PS2
button masks, which is another reason to remap only at the report.

## 3. Action table (field, battle, system)

"T" = triggered, "H" = held.

### Field (`FieldExploreModeUpdate_2833a0`, `PlayerControlUpdateMaybe_1fc4a0`, camera)

| Button | Action | Evidence |
| --- | --- | --- |
| Left stick | Move (camera-relative) | `PlayerControlUpdateMaybe_1fc4a0`: `mv = R(cam yaw)·(LX, LY)`, clamped to length 1; walk when `|mv|² ≥ 0.0256` (`D_0047DC3C`, |mv| ≥ 0.16), run when `≥ 0.81` (`D_0047DC40`, |mv| ≥ 0.9). Analog speed has three bands, not a continuum. |
| Right stick X | Rotate camera | orbit: `0.075 rad/tick × RX` (`D_0047D350`) |
| Right stick Y | Camera height | orbit: `3.0 units/tick × RY` (see section 6) |
| L1 / R1 (H) | Rotate camera left / right | `CameraObjApplyInputMaybe_1619e0` slots 3 / 2, ±0.075 rad/tick, ignored when both are held |
| R2 (T) | Recentre camera behind the leader | slot 4 → `CameraObjOrbitControlMaybe_161260` `x218` |
| Cross (T) | Examine / talk / use | `FieldExploreModeUpdate_2833a0` → `MapAreaTriggerEventsMaybe_200950`, func points, target object; `TaskControlObject_2cff20` |
| Circle (T) | Jump (retail tutorial, 2026-10-18) | `PlayerControlUpdateMaybe_1fc4a0` sets chara flags `0x10000`/`0x20000`/`0x40000`; refused with SE 0x2B on a moving lift. Cross also sets `0x2000`/`0x80000`/`0x20000` there; the flag consumers were not traced. |
| Triangle (T) | Main menu | GameReq 0x11 (or a "can't" message by leader control state) |
| Select (T) | Full-screen map, again to close | phase 0x190, `MapMgrMinimapEnterFullView_1e2760` |
| Select (T), camera mode 2 | Toggle camera type (options `+0x1A` mask 1) | `CameraModePresetToggleUpdate_307e50` |
| L3 (T) | Leader switch menu | `EasyMenuOpen_2030d0`, phase 0x1F4 |
| R3 (T) | First-person look, again to leave | `CameraSwitchTo3Fixed_30a2a0`, phase 0x12C; `CameraFirstPersonUpdate_307f00` uses **both** sticks |
| R1 (H) + Square (T) | Lift / chain action on a liftable target in front (**inferred**) | `PlayerControlUpdateMaybe_1fc4a0`, `FieldHudWidget80LiftOpenMaybe_203f60`, GameReq 9 |
| Start (T) | Pause (event skip menu during events) | `GameFrameUpdate_27c4c0`: Start without Select held |
| L1 / R1 (H), stick | Insect-cage view (`InsectCageMgrUpdate_39a620`) | context only |

### Battle (`BattleModeUpdate_280220`, `PlayerControlUpdateMaybe_1fc4a0`, lock camera)

| Button | Action | Evidence |
| --- | --- | --- |
| Cross (T / H) | Sword attack (main weapon; held = continue / charge, inferred); R1 (H) + Cross (T) on a target in front = pick up/throw | flags `0x0080…`, held `0x0040…`; `CharaGetFrontTargetRefMaybe_214a20` |
| Square (T / H) | Gun (sub-weapon) | flags `0x0100…`, `0x200000`, held `0x1000…` |
| Circle (T) | Jump | flag `0x400000` |

**Corrected 2026-10-18** (docs/BRINGUP.md 2026-10-18 (f)/(g)): the retail "Basic Battle Controls"
tutorial (PCSX2, `out/retail/cb1` first run) shows **X = sword, SQUARE = gun, CIRCLE = jump**.
The earlier table had the roles inferred from the flag bits as Square = attack, Circle =
sub-weapon, Cross = jump; the button -> flag rows above are unchanged, only the roles moved.
The field's Circle = jump agrees with the tutorial.
| R1 (H) | Guard (**inferred**) | flag `0x1_0000_0000`; R1 (T) with a lock-on target snaps the camera behind (`CameraQueueEyeYaw_161220`) |
| Triangle (T) | Battle command menu (pauses action) | `BtlChgMenuOpen_204b50` |
| Left / Right (T) | Cycle lock-on target | `TargetMngCycleAndSetTarget_313a10`, `TargetMngPickTarget_31faf0` |
| Up or Down (T) | Cancel lock-on / re-acquire | `TargetMngCancel_313a70` / `TargetMngSetTarget_313ad0` (mask 0x5000) |
| R2 (T) | Recentre lock-on camera (20 ticks) | `CameraModeLockTargetUpdateMaybe_3062e0` |
| Select (T) | Toggle camera type | same function, options `+0x1A` mask 1 |
| R3 (T) | First-person look (free-move state) | `BattleModeUpdate_280220` |
| L1 / L2 / L3 (T) | Ally suggestion: accept / decline / dismiss (**inferred** from result 0/1/2; 150-tick timeout) | `normal_FieldHudAllySuggestStep_4ef070` |
| Face buttons (T) | Attack-chain timing prompt: press the shown button within ±8 ticks of its mark | `AttackChainStep_382270` (`e->h8` ∈ {Triangle, Circle, Cross, Square}; a wrong face button fails) |
| Right stick | Lock-on camera orbit | `CameraModeLockTargetUpdateMaybe_3062e0` |
| R2 (H) + right stick Y | Zoom (camera mode 18) | `CameraModeZoomUpdate_306200`: distance −10/tick × RY, min 30 |

### System

| Context | Buttons | Function |
| --- | --- | --- |
| Pause | Start resume; Square "return to title" menu; Triangle skip event (pause type 1); Cross resume after the analog-mode prompt | `PauseStepUpdate_2f5fb0` (Triangle + R1 + R2 = debug event abort, dead: `ReturnZero_207fe0`) |
| Movie | Start pause/resume; Triangle skip (when allowed); Cross after analog prompt | `MoviePlayModal_267c60` |
| Loading | Cross or Start to continue | `LoadingScreenFrame_3435d0` |
| Ability mode | Triangle | `AbilityModeRun_2790e0` |
| Debug (dead) | Select, R1+R3 etc. | `CharaDataMgrUpdate_1ed9e0`, `MenuMainUpdate_297180`, `main/dbg` — all behind `ReturnZero_207fe0` |

## 4. Menus, Insectron, Factory, title, text entry

Confirm and cancel are hard-wired: `MenuGridCursorInput_28e170` (the shared cursor
handler, reads both ports) returns 1 on Cross (SE 5), 2 on Circle (SE 6), and 6 ("other")
on any of L2/R2/L1/R1/Triangle/Square (mask 0x9F) when the item allows it. The save screens
keep the pair in data: `D_004847F0` = 0x40, `D_004847F4` = 0x20
(`normal_TransSaveOpenState_51a3c0`); the title load screen uses `D_004841FC`/`D_00484200`
(`title_TitleSaveSysInit_4ef2b0`).

| Context | Roles |
| --- | --- |
| Main menu (`main/menu`) | d-pad or left stick move (stick→d-pad threshold 0x78); Cross confirm; Circle back; L1/R1 previous/next tab or character (`MenuTabCycleWrap_2b15a0`, `MenuCycleCharaSel_341220`, `MenuTactics*`, `RevelationCharaSelect_341fd0`); Triangle info/help or a sub-action (`MenuInfoBoxInputState_3414b0`, `MenuCharaAbilityPageSelectState_341980`); in the item grid Triangle, Square and Select open different sub-states (`MenuItemGridState_2b1e10`, not identified); L2/R2 page in `MenuModelPageSelectState_3575d0`; L2/R2 held change Revelation-board cursor motion (`RevelationBoardCursorUpdateMaybe_34d080`); Left/Right in yes/no dialogs (`MenuYesNoCursorInput_377180`) |
| Shop, transporter, think, help (`overlays/normal`) | d-pad lists with repeat; L1/R1 tabs (`normal_ShopMenuSellTabsSwitchCb_5103f0`, `normal_ThinkMenuTabsCursorMoveCb_520850`); Cross/Circle |
| Text entry (`main/ui`) | Cross types, Circle backs out, L1/R1 move the name cursor, L2 switches the character page (`TextEntryHandlePadInput_434060`), Triangle switches focus, Select jumps to the commit key (`TextEntryPaletteSelectState_435270`) |
| Insectron battle (`overlays/insect`) | `insect_InsectCursorSetInput_511090` turns every button into an event bit (Triangle 0x10, Circle 0x20, Square 0x40, Cross 0x80, L1 0x100, L2 0x200, L3 0x400, R1 0x800, R2 0x1000, R3 0x2000, Start 0x4000, Select 0x8000); consumers use Cross confirm, Circle cancel, Triangle, Square and L1/R1. The d-pad is rotated by camera yaw (`insect_InsectCursorSetUpdatePadRotation_510ed0`). Right stick orbits the camera and L2/R2 held zoom (`insect_InsectBattleCamUpdate_4f2100`, zoom inferred); Cross or Down held fast-forwards the log (`insect_InsectBattleLogUpdate_51bd80`, inferred). Input comes from the pad of the player whose turn it is (`insect_InsectCursorSetGetPad_511000`), so versus mode uses port 1. |
| Insectron menus (`overlays/insmenu`) | Cross/Circle, Triangle info, L1/R1 cycle cages, Left/Right in the controller-setup step (`insmenu_InsectVsMenuStateCtrlSetStep_4eabb0`, which checks analog mode on both pads; closing it calls `SetPad2Enabled_2882b0`) |
| Factory (`overlays/factory`) | `factory_FactoryStep_5069e0`: left stick (d-pad fallback) moves the cursor, right stick the camera; Cross places/commits; Circle or Triangle cancel; L1/R1 rotate the part. `factory_FactoryCameraUpdate_5050c0`: R2 − L2 held = zoom. Menus: L1/R1 material tabs, Triangle clear-confirm, Square move/remove (inferred), Up/Down quantity |
| Title | Movies skip on Triangle/Cross/Square/Circle/Start; Cross or Start confirms in `title_TitleMenuTick_4eaf70` |

Repeat set-ups (`PadSetRepeat_183d50(pad, mask, delay, interval)`, in PadUpdate calls;
stick→d-pad threshold 0x78, about 94% of the game-mapped range, where set):

| Caller | Mask | Delay | Interval |
| --- | --- | --- | --- |
| `MenuMainInitMaybe_297ac0`, `normal_ShopMenuStep_50a6f0`, `normal_TransMenuInit_516aa0`, `normal_SpaceMenuObjInit_5146b0`, `title_TitleStateInit_4ec660`, `insmenu_InsectVsSaveScreenOpen_4f8ef0` | d-pad + L1/R1 (0xF00C) | 12 | 7 |
| `MenuMainClose_296de0`, `CompleteCheckMenuStep_39e890`, `InsectMenuOpen_397ee0`, `normal_HelpMenuStep_522fd0`, `normal_ThinkMenuInit_5212b0`, `normal_InsectEntryMenuStep_524320`, `insmenu_InsectVsMenuSetupWidgets_4f3670` | 0xF00C | 10 | 3 |
| `normal_BtlChgMenuOpen_4fa3c0` | d-pad | 10 | 3 |
| `MenuModelPageOpenState_358840` | d-pad; L2/R2 | 10; 10 | 3; 7 |
| `factory_FactoryMenuOpen_4ec5e0` | 0xF00C | 10 | 4 |
| `insect_InsectCursorSetInit_511f00` (both ports) | d-pad + shoulders (0xF00F) | 15 | 4 |

`MainMenuModeUpdate_27d460` saves and restores the whole repeat block around the main menu
(`D_004D7E90`).

## 4b. Proposed action names (INPUT.md)

The ids stay; the labels change. Default PS2 positions are unchanged.

| Action id | Label | PS2 |
| --- | --- | --- |
| `confirm` | Confirm / Examine / Talk / Sword (battle) | Cross |
| `cancel` | Cancel / Jump | Circle |
| `attack` | Gun (battle) / Lift (with R1, field) | Square |
| `menu` | Menu / Battle commands | Triangle |
| `shoulder_left` | Camera left / Accept suggestion / Previous tab | L1 |
| `shoulder_right` | Camera right / Guard / Next tab | R1 |
| `trigger_left` | Decline suggestion | L2 |
| `trigger_right` | Recentre camera / Zoom (hold) | R2 |
| `stick_left_click` | Switch leader | L3 |
| `stick_right_click` | First-person look | R3 |
| `select` | Map / Camera type | Select |
| `start` | Pause / Skip | Start |

Sword / gun / jump are confirmed by the retail tutorial (2026-10-18); guard (R1) is still
inferred. Because confirm/cancel are hard-wired to Cross/Circle (section 4), a
"Japanese layout" (Circle confirms) option can only be a report-level swap of the two
buttons everywhere, which also swaps the field and battle actions on those buttons.

## 5. Analog details

- Game dead zone and curve (all twelve stick getters and `PadAnyInput_183e80`):
  `v = raw − 128; |v| < 50 → 0; v > 0 → (v − 49)·128/78; else (v + 50)·128/78`, integer
  division, then `/128.0f` for the Norm versions. The result reaches ±1 at raw 0 / 255
  (approximately; 127·… rounds to 128 at 255, −128 at 0). Per axis.
- Movement thresholds on the combined vector: 0.16 (walk) and 0.9 (run).
- Camera "push" decay starts when either left axis exceeds 0.01 (`D_0047D88C`).
- Port consequences:
  - Effective dead zone = `max(input.deadzone_move, ~39%)`. A port deadzone setting below
    39% does nothing unless the adapter **compensates**: a "modern response" option can
    pre-map the host value so that host 0 maps to raw 128 ± 50 and host 1 to raw 255/0,
    i.e. `raw = 128 ± (50 + |h|·78)` for `|h| >` the host dead zone. This changes how small
    deflections act, so it is a gameplay option, off in Original.
  - Square vs radial: the game's per-axis dead zone makes diagonals snap toward axes at
    small deflections. The compensation above can be radial on the host side.
  - Keyboard movement gives full deflection (run). A "walk" modifier binding (scale to,
    say, 0.6) is needed to reach the walk band.

## 6. Mouse camera

### What the camera reads

| Mode (`CameraModeUpdate_309770` switch) | Function | Input → state, per tick |
| --- | --- | --- |
| 0 follow leader, 2 preset, 18 zoom | `CameraFollowLeaderStepMaybe_3081e0` → `CameraObjApplyInputMaybe_1619e0` → `CameraObjOrbitControlMaybe_161260` | yaw: `in.a = 0.075 × RX × signX` (or ±0.075 for L1/R1), applied as `v60(in.a × min_dist / max(dist, min_dist))` = `CameraRotateEyeYaw_176ef0` (radians, rotation of the eye about the target). Pitch: `in.b = 3.0 × −RY × signY` world units added to the eye-height offset `prm.x10`, clamped to [−15, 40]; with no input it eases back into [−15, 20] by 1/20 per tick. R2 = recentre. |
| 1 first person | `CameraFirstPersonUpdate_307f00` | `yaw −= 0.06545 × (LX + RX)`, `pitch −= 0.06545 × (LY + RY)` radians (`D_0047D614` = 3.75°), pitch clamped to ±1.555 rad; yaw also turns the character (`CharaSetYaw_2138f0`). |
| 31 lock target (battle) | `CameraModeLockTargetUpdateMaybe_3062e0` | `f26 = signX × RX`, `f22 = signY × RY` into its own orbit math |
| 32 target follow | `CameraTargetFollowUpdate_307340` | same pattern (`kx`, `ky`) |
| 15 Insectron, 16 Factory | `insect_InsectBattleCamUpdate_4f2100`, `factory_FactoryCameraUpdate_5050c0` | own stick handling (L2/R2 held modifiers) |

`signX`/`signY` are camera `+0x258`/`+0x254`, set every tick by `CameraModeUpdate_309770`
→ `CameraSetAxisSigns_160470` from options `+0x1A` bits 4 (invert X) and 2 (invert Y)
(`OptionsSetCameraInvertX_3d6040`, `OptionsSetCameraInvertY_3d6060`). The first-person
mode reads the same bits directly. None of this is scaled by the scene timestep: rates are
per tick.

### Why it must be deterministic

`PlayerControlUpdateMaybe_1fc4a0` rotates the stick by `cam->Yaw()`, so the camera yaw
decides where the leader walks; first-person yaw sets the character's yaw. Camera state is
game state. A mouse delta applied at presentation time would change logic results with the
frame rate, which the P6 gate forbids.

### Design

1. **Host side.** Capture the mouse in relative mode while the game has focus and no
   overlay is open. Accumulate raw counts between pumps. At each `rg_host_pump` (field
   boundary), move the accumulator into a per-port "pending look" value, quantised to an
   integer unit (proposal: 1/4096 rad for yaw and pitch angle, 1/256 world unit for orbit
   height), after `input.mouse_sensitivity` and the invert settings.
2. **Tick latch.** Latch the pending value when the game calls `PadUpdate_1843a0` for
   port 0 from `MainLoop_1c2c10` (the per-frame call), into a port-side `look` record next
   to the pad (not inside the game's 0x264-byte struct). Extra PadUpdate calls do not
   latch again. Input scripts gain two optional columns (yaw, pitch units per tick), so
   replays reproduce mouse play exactly and the script-bypass rule still holds.
3. **Injection (overrides).** Consume-once per tick, and discard when the camera did not
   run that tick (pause, menus, events), so no burst on resume:
   - `CameraObjApplyInputMaybe_1619e0`: add yaw radians to `s.a` **divided** by the
     distance factor the orbit applies (`min_dist / max(dist, min_dist)`), or add it after
     that scaling by overriding `CameraObjOrbitControlMaybe_161260`; add the height delta to
     `s.b`. Optional "mouse holds pitch": skip the ease-back while mouse look is active
     (a camera-only behaviour change, still deterministic).
   - `CameraFirstPersonUpdate_307f00`: add yaw/pitch radians directly.
   - `CameraModeLockTargetUpdateMaybe_3062e0`, `CameraTargetFollowUpdate_307340`: convert
     to their stick units (they take −1..1 per tick) or leave them on the stick path at
     first.
   - Insectron and Factory cameras stay on the stick path (mouse bound to `camera_*`).
4. **Units.** Orbit yaw has a natural unit (radians, the stick's full rate is 0.075/tick).
   Orbit pitch is not an angle: it is an eye-height offset in world units with a hard range
   of 55 units, so mouse Y should map to units, e.g. 1 count = 0.05 units at sensitivity 1.
5. **Settings** (all non-gameplay, all off or neutral in Original): `input.mouse_look`
   (on/off), `input.mouse_yaw_scale`, `input.mouse_pitch_scale`, `input.mouse_invert_y`,
   "mouse holds camera height".

## 7. Vibration

**Nothing in the US build turns a motor on.** The driver is complete, but every write to
the motor bytes and durations is a zero-write.

- `PadUpdateConnection_184a50` maps the motors once (`scePadSetActAlign {0, 1, FF...}`:
  actuator 0 = small, on/off; 1 = large, 0..255).
- `PadUpdateVibration_184250(pad, dt)`: motor bytes at `+0x2C` (small) and `+0x2D`
  (large), durations at `+0x44`/`+0x48` counted down by `dt`, sent with
  `scePadSetActDirect` only when they differ from the last values sent (`+0x38`/`+0x39`)
  and the pad is STABLE or FINDCTP1. `+0x254` = enable (only `PadStateInit_184f90` writes
  it, to 1; no option). `+0x258` is a watchdog that zeroes both motors after 1000 ticks.
- Callers: with `dt = 0` (a flush) next to the edge-consuming `PadUpdate` calls of
  section 1; with `dt = 1` from `PadVibrationTick_1837a0` in the per-VBlank tick thread
  (`SysTickThreadMain_1c33f0`, woken by `SysVblankCallback_1c33a0`), but only through the
  pointer `D_00481230`, which nothing writes, so that tick never runs.
- Searched by offset, by absolute address (`D_004B259C`, `D_004B259D`, `D_004B25B4`,
  `D_004B25B8` and the port-1 twins) and by name: no setter, no EvCmd vibration command,
  no option.

So the port's `input.vibration` setting and rumble hook are correct but never exercised
by the game. Rumble on hits or explosions would be a new feature; it could be driven from
game events on the host side without touching logic, and stays off in Original.

## 8. Button prompts

### Mechanism

Button icons are **ASCII tags in the message text**. Every text path
(`FontDrawText_26cdc0`, `FontDrawTextGradient_26c6e0`, `FontMeasureString_26daf0`,
`FontWrapText_26d5a0`, `FontMeasureWordWidth_26d8d0`, `MesWinLayoutText_274e70`,
`MesWinMeasureText_272b80`) matches them before ordinary characters through
`FontMatchGaijiTag_26ef90` → `TextGaijiTagFind_26f060`, a linear `strncmp` over
`D_0044EA00` (`{name, len, code}`; names in `D_0045F208`). Each code is drawn as a quad from
one "gaiji" texture (`FontDrawGaiji_26dd50`; sprites `FontDrawGaijiSprite_26fa50`), with
rects and advances from `D_0044E680` (12-byte `{code, u, v, w, h, dx, dy}`, looked up by
`FontFindGaijiMetric_26f8c0`; width = pen advance via `FontGetGaijiWidth_26f890`).

| Tag | Code | Button | Rect in `gaiji2` (u, v, w×h) |
| --- | --- | --- | --- |
| `[l2]` | FD04 | L2 | 0, 0, 32×20 |
| `[l1]` | FD02 | L1 | 32, 0, 32×20 |
| `[r1]` | FD03 | R1 | 64, 0, 32×20 |
| `[r2]` | FD05 | R2 | 96, 0, 32×20 |
| `(O)` | FD06 | Circle | 0, 20, 22×22 |
| `(A)` | FD07 | Triangle | 22, 20, 22×22 |
| `(#)` | FD09 | Square | 44, 20, 22×22 |
| `(X)` | FD08 | Cross | 66, 20, 22×22 |
| `(R)` | FD3E (FD3F for font type 2) | not a button: the registered-trademark sign ® (corrected from the atlas, docs/PROMPTS.md) | 0, 234, 16×22 |

`[+]` (FD40) is a plain white plus sign, not a d-pad icon (docs/PROMPTS.md). So the
button glyphs are the eight above.

There is **no Start, Select, d-pad or left-stick gaiji**. Text naming those uses symbol tags
(`FontMatchSymbolTag_26ef40` → `TextSymbolTagFind_26efe0`, table `D_0044EB20`: the arrows
`[ar-r]`, `[ar-l]`, `[ar-u]`, `[ar-d]` and the shapes `[cir-*]`, `[box-*]`, `[tri-*]`, drawn
from the normal font pages) or plain words in the message files. The other gaiji are
status and element icons, `[back]`, `[atg]`, and the message-window page icon and choice
arrow.

Texture: `gaiji2.img` (`D_0045F688`, at most 0x10800 bytes) inside
`meswin/fontset_main_?.pak` (`D_0045F660`; launcher variant `D_0045F640`), loaded by
`FontResLoadAll_205540` → `MesFontPakRead_2703f0` → `GaijiLoadImage_2705a0`, registered
as `gaiji2` by `GaijiRegister_270520`, handle in `D_004820E0` (`GaijiGetTex_270510`).

Prompts outside the tag path:

- `InsectCageButtonHintDraw_388ee0` binds `GaijiGetTex_270510()` and draws L1 and R1 from
  hard-coded rects `D_0047FC90..9C` ({32,0,32,20}, {64,0,32,20}).
- `MesWinDrawPageIcon_2713f0` and `MesWinDrawChoiceArrow_271730` use fixed gaiji rects
  (`D_0045F6F0`, `D_0045F6E0`); they are not buttons.
- `AttackChainMarkersShow_382c40` shows the attack-chain button marks (the required button
  is a face-button mask in `e->h8`); its art source was not traced.
- Menu and battle HUD art in `menu/rc/*.pac` and `*_def_?.res` may contain baked button
  pictures (not verified). The message files may spell button names in words (not
  audited; the executable contains none).

### Swap plan

1. **Texture swap (the main lever).** Ship one `gaiji2` replacement per prompt set
   (PlayStation = original, Xbox, Nintendo, keyboard and mouse) with the **same rects**, and
   choose it at `GaijiGetTex_270510`, or in the host renderer by texture identity, from
   `rg_host_active_device`. That covers all tagged text and the insect-cage hint with no
   layout change. Switching is presentation-only, so it is safe under the state-trace
   gate.
2. **Rect and advance swap** where art needs a different size (a key cap reading
   "Space"): hook `FontFindGaijiMetric_26f8c0`, so drawing, measuring and wrapping all see
   the same width. Wider glyphs reflow text; the single lookup keeps all seven text paths
   consistent.
3. **Keyboard prompts follow the bindings.** Render each glyph from the key currently bound
   to the action at that PS2 position (key name on a key-cap background) into the
   replacement atlas at runtime, so rebinding updates prompts. Mouse buttons get icons.
   With several bindings, show the first.
4. **Nintendo layout.** With positional default bindings (South = Cross), the Nintendo atlas
   shows B in Cross's slot. A "label" layout (A confirms) swaps atlas and bindings
   together.
5. **Not covered by the texture:** symbol-tag arrows, words in message files (a text
   override pass if they name buttons) and any baked HUD or menu art (asset replacement
   through the override layer). A text and texture dump decides how much of this exists.

### Risks

- Changing `w` reflows text, and fixed-UV draws (`D_0047FC90`) need their own patch if
  rects move.
- `gaiji2` is a single small PS2 texture with a size cap. High-resolution replacement art
  must go through the host texture-replacement path, not the 0x10800-byte buffer.
- A literal `(O)` or `(X)` in any string always becomes an icon (the gaiji match runs
  first).

## 9. Risks

- **Inferred roles.** Guard (and the held / charge meanings) come from flag bits set in
  `PlayerControlUpdateMaybe_1fc4a0` whose consumers were not traced. Confirm in a
  recorded run before renaming the labels in INPUT.md.
- **Edges are per PadUpdate.** Any host-side change that adds PadUpdate calls, or that
  pulses held buttons, breaks triggered/released and repeat timing. Keep the adapter a pure
  report function and keep the latch.
- **Repeat rates depend on the frame interval**: menus at a one-VBlank interval repeat
  twice as fast as two-VBlank screens. That is original behaviour; an unlocked presentation
  rate must not change it.
- **Dead zone stacking.** The port's 25% default sits inside the game's 39%, so changing the
  port setting below 39% looks broken. Either document it or add the compensation curve as
  a gameplay option.
- **Report-level confirm/cancel swap** also moves field and battle actions; script data
  hard-codes masks, so it cannot be done per screen.
- **Second controller.** Port 1 is live in the Insectron versus mode (`SetPad2Enabled_2882b0`
  from `insmenu_InsectVsMenuStateCtrlSetClose_4eaa80`), and the pause and analog checks
  read it when `IsPad2Enabled_2882c0`. INPUT.md's "single-player" note should be corrected;
  `input.players = two` matters for Insectron versus.
- **Mouse camera** changes logic state; it must go through the recorded per-tick channel.
  A presentation-only mouse camera would break the P6 gate.
- **No vibration in the original.** Any rumble is a new feature; keep it out of the
  Original preset.
- **Prompt coverage.** The texture swap covers tagged text only; words in message files and
  baked HUD art need separate text and asset passes.
- **Analog lock.** `scePadSetMainMode(1, 3)` locks analog mode; the port's DS2 model must
  keep reporting mode 0x73, or the game raises the "analog required" pause.
