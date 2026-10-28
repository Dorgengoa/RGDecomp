# Widescreen and internal resolution: source audit and plan

Date: 2026-10-12. Source: the official decomp at commit `675c07f` (the same snapshot as
`game/`, see `game/SNAPSHOT.txt`). Paths below are `src/main/...` in that tree, which is
`game/src/main/...` in the port. This is a read-only design audit. Nothing was run, and no
code was changed. It covers PLAN.md P6 "Aspect ratio" and "Internal resolution scale".
Claims are taken from function bodies and data values, not from names or comments.

## Summary

1. **The game already has a hidden 16:9 mode.** `D_00481638` (set by `SetAspectMode_1c6a90`,
   read by `GetAspectMode_1c6aa0` and `IsWidescreen_1c6ab0`) switches the projection aspect
   from 0.75 to 0.5625. It also narrows some 2D sprites by 0.75. It is an **anamorphic**
   mode: the frame buffer stays 512x448 and a 16:9 TV stretches it. Only a boot-config
   command (`SysCfgTvModeCmd_1c2b10`, string `"WIDE"` at `D_0045B008`) and the key-capture
   mode (`GameSessionInit_1f5d80`, `title_TitleSessionInit_4f0cb0`) turn it on. The source
   has no user-facing option for it.
2. **The native frame is 512x448, not 640x448.** `SysBootInit_1c2ee0` calls
   `GfxSysInit_15dd20(2)`, and mode 2 in `GfxSetVideoMode_1451f0` sets `w=0x200`,
   `h=0x1C0`, interlaced NTSC. Pixels are non-square: all 2D sprite heights are multiplied
   by `D_0047D7EC = 7/6`, and centred heights by `D_0047D7E4 = 7/12`.
3. **Culling follows the projection.** `ViewSetPerspective_1564a0` derives the frustum and
   guard-band planes from the projection matrix, so a wider aspect widens culling without
   further changes.
4. **A wider logical frame buffer does not fit.** The GS address space is 4 MB, and there
   is no room for it (see "Rejected").
5. **Recommended approach.** Use the anamorphic route, generalised to any aspect. Override
   the aspect choke point, add per-axis upscaling in the renderer, and move 2D elements
   with a renderer-side layout transform driven by in-stream class markers.

## 1. Projection

| Step | Function | Facts |
| --- | --- | --- |
| Per frame, gameplay | `TaskUpdateDrawInfo_2f6ff0` (task 93, the first draw task) | Copies the live scene camera (`scene+0x4344`), applies shake, then calls `ViewSetProjectionBasic_143180(dl, pi*fov/180, near 1, far 60000, aspect 0.75)`, then `SceneCameraApplyAspect_1c6a10`. |
| Aspect choke point | `SceneCameraApplyAspect_1c6a10` | `GetAspectMode()==1` → `ViewSetAspect_142f50(ctx, 0.5625)`, else 0.75. |
| Core | `ViewSetProjection_143000` | Builds the screen params from the gfx record at `ctx+0x270`: `sx=w`, `sy=h`, centre `0x800+...`, guard `2047`. The aspect becomes `r = d * h2 / m20`, which is `d` for NTSC because `m20 = 448`. Calls `ViewSetScreenMatrix_1562b0`, then `ViewSetPerspective_1564a0`. |
| Matrix | `ViewSetPerspective_1564a0` | `proj[0][0] = aspect * cot(fov/2)`, `proj[1][1] = cot(fov/2)`: **Hor+** (the vertical FOV is fixed and the aspect widens the horizontal). |
| Screen matrix | `ViewSetScreenMatrix_1562b0` | `m[0]=sx/2`, `m[5]=-sy/2`, `m[12..13]` = screen centre (GS coords). Guard ratios `m240=sx/(2047-8)`, `m244=sy/(2047-8)`. |
| FOV-only changes | `ViewSetFov_142f10`, `ViewSetDepthRangeMaybe_142f90`, `ViewReapplyCameraRec_142e90` | Re-pass the stored aspect (`rec+0x44`), so event/track cameras (`CameraTrackUpdate_305960`, `CameraScenePopApplyFov_309f10` from `EventPlayerEnd_249480`) and the plane-shadow pass keep it. |
| FOV authoring | `FovHorizToVert_13fbe0` (already in `overrides/`), `CameraObjInit_309ab0` | Converts an authored *horizontal* FOV to vertical with a fixed 0.75: 52° horizontal becomes about 40.2° vertical. Leave this as is. It is how Hor+ keeps the authored vertical framing. |

Projection setups that bypass the choke point and hard-code 0.75:

- `GameSessionInit_1f5d80` and `title_TitleSessionInit_4f0cb0` set the initial projection
  (`D_0047D4A0` = 0.9076 rad = 52°). The title loop does not run task 93, so title 3D stays
  at 0.75.
- `CompassHudRender_370fb0` has its own screen matrix and perspective (aspect 0.75,
  centre `D_0047D830/834` = GS (1866.9, 2212.2), which is pixel (75, 388)) and is **not**
  WIDE-aware.
- `DrawModelWithCamera_28bf80` draws menu model previews at 0.75.
- `ShadowMapRender_146680` uses aspect 1.0. It is an off-screen pass; leave it alone.
- The insect overlay's `insect_InsectBattleDrawPreviewModel_4f5fc0` divides by 0.75.

Hor+ field of view for the default 40.2° vertical: 52° at 4:3, 66° at 16:9, 61° at 16:10,
81° at 21:9 (2.33), 105° at 32:9.

## 2. Culling and LOD

- **View frustum.** `ViewSetPerspective_1564a0` builds planes `pl[0..5]` from the
  transposed projection, stored as `cam+0x3D0`/`+0x410`. `ModelPrepareDrawMaybe_14f760`
  culls on them. `CameraBoundsInView_15cd20` → `AabbInFrustum_13be60` (overridden) serves
  `NodeObjIsInView_194200` → `MapAreaModelCollectVisibleObjsMaybe_188060` and
  `MapAreaModelUpdateVisibility_1886b0`. **All of these widen with the aspect.**
- **Guard band.** Planes `pl[6..11]` (`+0x450`/`+0x490`) come from the projection scaled by
  `m240/m244`. They pick the VU no-clip path (`info.mode = 0`) when a box lies inside the
  GS ±2047 window. They depend on `sx`/`sy`, not on the aspect, so the anamorphic route
  leaves them unchanged.
- **Stubs and other culling.** `BoundsInViewStub_15cd10` and `CameraBoxInViewStub_15cd00`
  return 1. Occluders (`OcclusionPlaneBuildFrustumMaybe_1971d0`) are built in world space.
  Far clip (`MapCfgFarClip_18c7e0`, `FarClipRec*`) is distance-based. None of them
  assumes 4:3.
- **Visual risk.** At 21:9 and wider, the frame edges show more of the scene. Pop-in at the
  far-clip fade and set-dressing that was only built for 4:3 framing (especially in event
  scenes) become visible. This needs checking scene by scene. It is not a code defect.

## 3. 2D, HUD, menus and text

**Coordinate system.** 2D goes through the `GsPkt*` emitters (the port already overrides
most of them in `overrides/src/main/gs/`). `GsPktInit_13f7f0` caches the centre
(`0x800<<4`) and `w<<4`/`h<<4`. `GsPktSetOriginMode_13e2f0` selects one of three modes:

- **0:** frame top-left. The offset is the centre minus w/2, so x runs over 0..511 in the
  frame buffer.
- **1:** raw GS coordinates, used with projected points.
- **2:** frame centre.

XYOFFSET comes from `DrawEnvSetCenter_157560(0,0)`, which puts 0x800 at the frame
centre. Full-frame scissors use `DrawEnvGetWidth/Height`
(`GsPktSetScissorFull_26fe60`). Text clips through `GsPktSetScissor_28c2e0`,
`MesWinSetScissor_271fa0`, `FontSetScissor_26e380` and `TextClipRectDrawCb_*`. Most 2D
reads W and H from `DrawEnvGetWidth_1451e0`/`DrawEnvGetHeight_1451d0` instead of
literals:

- message windows place themselves at fractions of W/H (`MesWinCalcPos_2710b0`);
- the minimap defaults to `(W-210, H-178)` with a 160x144 window
  (`MinimapSetScreenAnchorPos_324ca0`, `MinimapMgrResetView_321770`);
- the attack chain and target slots centre on W/2 and H/2.

**What retail WIDE fixes.** The game's WIDE mode squeezes element *widths* by 0.75 and
leaves positions unchanged. It does this at all 13 call sites of the flag (from
`asm/main.s`):

- `GsDrawSpriteCentered_3834d0`, `GsDrawSpriteAnchorBR_3836a0`,
  `GsDrawSpriteAnchorBL_383860`, `DrawRotatedQuad_383c70`
- `HpGaugeDraw_31d090`, `HpGaugeDrawThin_31d2d0`, `MinimapDrawEntries_329460`,
  `TargetSlotDraw_320b00`
- `AttackChainDraw_380660`, `AttackChainStartMaybe_382910`, `LensFlareDraw_2ed830`,
  `DoorCursorDraw_304aa0`
- `SceneCameraApplyAspect_1c6a10`

**No overlay checks the flag.** In retail WIDE the battle menu (normal overlay), every
menu, fonts, message windows, captions, the compass and the title are stretched by 4/3.
So retail WIDE is only a starting point, not something to ship as is.

**Anchor classes.** I propose these, applied by the renderer in frame-pixel space. `s` is
`(4/3)/DAR`; `W` is 512.

| Class | Transform | Use |
| --- | --- | --- |
| `3D` | none (projection already widened) | world |
| `STRETCH` | none | anything that covers 0..W-1: fades, filters, letterbox bars |
| `CENTER` | `x' = W/2 + (x-W/2)*s` | menus, dialogue, title, movies (gives 4:3 pillarbox) |
| `LEFT` / `RIGHT` | `x' = x*s` / `x' = W-(W-x)*s` | corner HUD |
| `WORLD` | keep the position; squeeze each sprite about its own centre by `s` | 2D attached to projected points |

The transform must also apply to **SCISSOR** values set inside a region, and to all
primitives in it, including VU1 3D output (the compass, menu model previews).

**Main elements**, from draw-task registry indices 93–174
(`private/pc-port-research-01a116f0/frame-rate/task-registry.tsv`):

| Element | Draw function | Position source | Class |
| --- | --- | --- | --- |
| HP gauges over heads, damage numbers, screen markers | `TaskDrawStatus_2058b0` → `HpGaugeDraw*`, `DamagePopupDrawAll_2d2ea0`, `ScreenMarkerDrawAll_31af50` | `ProjectToScreenOffset_15d160` | WORLD (HpGauge already WIDE-aware) |
| Target slots / lock-on | `TaskDrawTargetMng1_313590` → `TargetMngDraw1_31edf0`, `TargetSlotDraw_320b00` | billboard projection | WORLD |
| Attack chain | `TaskDrawAttackChain2_1f93a0` → `AttackChainDraw_380660` | W/2, H/2 | CENTER (or WORLD with WIDE scale) |
| Door cursors, event icons, NPC icons | `TaskDrawObjectCursor_2cee40` → `DoorCursorDraw_304aa0`; `DrawEventIconTask_27aac0`; `TaskDrawNpc_3127e0` → `NpcObjDrawIcons_2fbb20` | projected | WORLD |
| Lens flare / sun | `TaskDrawLensFlare_1ffcf0` → `LensFlareDraw_2ed830`; `TaskDrawSunLight_1ffd50` | projected | WORLD |
| Compass | `CompassHudDraw_1f6f60` → `CompassHudRender_370fb0` | own screen matrix, pixel (75,388) | LEFT |
| Minimap | `MinimapDraw_1ffbc0` → `MinimapMgrDraw_321fa0` | `(W-210, H-178)` | RIGHT |
| Stealth icon | `TaskDrawIconStealth_202630` | origin-mode 2D | to place per element (LEFT/RIGHT) |
| Area caption, warp menu | `TaskDrawCaption_1ffb00` → `MapMgrCaptionDraw_1e2620`; `TaskDrawMenuWarp_1ffb60` | 2D | CENTER |
| Battle menu / party HUD | `BattleMenuDraw_203e70` → normal overlay `0x506BC0`, `0x4F54E0` | overlay 2D | per element (LEFT/RIGHT/CENTER), needs overlay overrides |
| Menus (main, shop, help, insect, factory, ...) | tasks 149–166 (`TaskDrawMenu*`) | 2D | CENTER |
| Message windows | `TaskDrawMessage_27a8b0` → `MesMgrDrawAll_277a50` → `MesWinDraw_270cb0` | fractions of W/H | CENTER |
| Letterbox | `DrawEventFrameTask_27a870` → `LetterboxDraw_277ff0` | 0..W-1 | STRETCH |
| Fade / pause / gray / DOF / glare / focus | tasks 128–132, 167, 172 | W/H-sized | STRETCH |
| Loading icon | `LoadingIconDraw_2ee320` | 2D | RIGHT (check where it sits) |

## 4. Full-screen effects

- **Sized from W and H.** DOF (`DofWorkTexRegister_2f6a30`, `DofFilterDrawMaybe_17d150`),
  glare (`GlareWorkTexRegister_2f6be0`), lens (`LensWorkTexRegister_2f7620`), screen
  fades (`ScreenFadeBlockDraw_177540`, `...DrawWipeStrips_177a70`,
  `GsPktTileScreenSprites_177cf0`), the letterbox, the focus filter and the CBlur passes
  all take their size from `DrawEnvGetWidth/Height`. Bloom/blur work textures are fixed
  64/128 downsamples.
- **No 640 literals.** None of them uses 640, so the anamorphic route needs no changes
  here.
- **Radial effects stretch.** `FocusFilterDrawMaybe_17c000` and lens-flare ghost spacing
  become elliptical when stretched. This is minor.
- **Final copy.** `GfxFlipBuffersMaybe_143650` copies the draw buffer (FBP 0) into the
  display buffer every frame with 16-column textured sprites (a 1:1 CT32 → CT24 copy).
  Under the current GPU renderer this is a sampled target, so **it is read from the
  native-resolution mirror**. With `--gpu-scale` above 1, every frame passes through a
  512x448 sample at this point (see GPU.md, "Render targets as textures"). Internal
  resolution scaling does nothing visible until this copy samples the upscaled target
  directly.

## 5. Movies

- **The game's player.** `MoviePlayModal_267c60` decodes into a W×448 or W×336 texture and
  draws it with `DrawTexturedRect_26a920(0,0,0x200,0x1C0,...)`. Mode 1 is the 336-line
  letterboxed movies, with `y = -0x20`.
- **No aspect logic.** Nothing in it checks the aspect flag, so retail WIDE stretched the
  movies.
- **Plan.** Tag the movie draw `CENTER` (4:3 pillarbox). Make the port's movie service
  (PLAN P4 "Movie layer override") use the same placement, as MVI.md recommends.

## 6. GS display and internal resolution

- **Video mode.** Mode 2 calls `sceGsResetGraph(0, interlace=1, NTSC, ffmode=0)` with a
  full-height 448-line buffer (FIELD mode). There are 3 buffers: draw CT32, display CT24
  and Z24 (`m38 = 0x31`). The texture area runs from `m170` to block `0x3FC0`, about
  1.4 MB.
- **Latent modes.** Modes 3–14 (640-wide, 480p via `omode 0x50`) exist but are unused.
- **Presentation.** Present the whole 448-line `DISPFB` progressively. Don't emulate
  per-field line selection, or the image drops to 224 effective lines.
- **Screen adjust.** `GsDbufPutEnv_144150` adds a screen-adjust offset (`ctx+0xF08/0xF0C`)
  to DISPLAY DX/DY. Host presentation should ignore DX/DY.
- **Native-semantics readbacks.** These must keep native semantics, and the renderer's
  write-back already samples native pixels:
  - `GfxEndFrame_141c20` reads four depth-probe slots (`ctx+0x3CD0`): an 8x8 PSMZ32
    `sceGsExecStoreImage` at slot (x,y), keeping the minimum z. `LensFlareDraw_2ed830`
    uses slot 0 for sun occlusion, at pixel coordinates `ProjectToScreenOffset/16`.
  - `ScreenFadeBlockCaptureFrame_177ed0` and `MenuCaptureScreenTex_298810` copy the frame
    into EE memory with `GsDownloadImage_140f20`, for transitions and menu backgrounds.
    These stay native by construction. A host-side high-resolution copy could be an
    "enhanced" toggle later.
  - `RefractionCaptureFrame_13ffd0` (overridden) captures on the GS.
- **No pixel-readback picking.** All screen-space logic projects on the CPU
  (`ProjectToScreenOffset_15d160`, `CameraProjectBillboardRect_15cde0`).
- **Logic-tick consumers of the projection.** Changing the aspect changes their state:
  - `TaskStepStatus_205e30` adds screen markers when a point projects.
  - `EventObjMgrUpdateDoorCursors_2e8060` fades door cursors when they leave `W<<4 × H<<4`.
  - `TargetMngSetAimOffscreen_31ed50`.

  The state-trace corpus must classify these as presentation state. They do not feed
  gameplay. `AiWarpToWaypointOffscreenMaybe_2bc6c0` → `AiRouteCheckCameraViewMaybe_2bcaa0`
  uses a fixed cone (dot > `D_0047D94C` = 0.3, a half-angle of about 72.5°) and **not**
  the projection. AI warps therefore stay identical, and remain hidden up to 32:9 (52.4°
  half-FOV).

## Rejected: a wider logical frame buffer

Making `w` wider (683 → FBW 11, 704 px, for 16:9) would make every W-relative layout and
effect correct for free. It does not fit the GS budget:

- **Memory.** Three 704x448 32-bit buffers take 3.8 MB of the 4 MB, which leaves about
  0.4 MB for textures instead of about 1.4 MB.
- **Addressing.** TBP0 has 14 bits and FBP 9 bits, so no register can address past 4 MB.
  The port cannot simply grow VRAM.
- **640-wide mode 4.** It also breaks the texture budget, and the 7/6 pixel-aspect
  constants assume 512.

## Plan

**Stage 0: retail WIDE preset (16:9 only, small).** A settings toggle calls
`SetAspectMode_1c6a90(1)` after boot, and the host presents the 512x448 frame at 16:9.
This gives a ground-truth reference: PCSX2 with `D_00481638 = 1` must match the port
frame-for-frame. Use it to validate projection and culling.

*Revised when implemented (2026-10-17, docs/WIDESCREEN.md "Revisions to the audit's
stage 0"):* the setting is `graphics.aspect` (4:3 / 16:9); the flag is written between
fields every field instead of once after boot (the boot config and
`SceneCameraApplyAspect_1c6a10` can both rewrite it; this also makes it live), and never
at 4:3; the title and movies, which have no WIDE-aware element, are shown 4:3 pillarboxed
in the 16:9 canvas with the flag cleared instead of stretched (`graphics.movie_aspect =
stretch` restores retail's movie stretch); "match window" internal resolution also
reaches the canvas width. Menus stay stretched until stage 2.

**Stage 1: any aspect (overrides).**

- Add a port function `rg_aspect_d()` (0.75 × (4/3)/DAR) and `rg_hud_xscale()` (`s`).
- Override `SceneCameraApplyAspect_1c6a10` to apply `rg_aspect_d()`.
- Override the 12 other flag sites to use `rg_hud_xscale()` instead of 0.75, but only for
  WORLD-class elements; screen-anchored HUD is handled in Stage 2.
- Apply the aspect to `CompassHudRender_370fb0`, `DrawModelWithCamera_28bf80` and the two
  session-init setups, or tag them (Stage 2).
- Keep `IsWidescreen` false when the renderer transform is active, so nothing is squeezed
  twice.
- Under "Original" (4:3), every override reduces to the original constants. Gate on frame
  hashes.

*Implemented 2026-10-17 (docs/WIDESCREEN.md "Stage 1"):* as planned, with the
`rg_hud_xscale()` factor applied at all 12 sites (they are the game's own WIDE squeezes,
WORLD-class or self-anchored, e.g. the attack chain's right-anchored positions); the
compass and menu previews take `rg_aspect_d()` under the flag; the title session init is
left alone (the title is pillarboxed 4:3). `IsWidescreen` stays the game flag until stage 2.

**Stage 2: renderer-side layout transform.**

- Emit a port-private marker packet into the draw list (a GIF A+D write to an unused GS
  register address that `src/ps2/gs` recognises) whenever the layout class changes. The
  marker carries class, `s`, and an optional element centre.
- Insert markers from a runtime hook in `TaskTableRun_1f5340`, using a per-task class
  table for indices 93–174. Add per-element overrides where one task mixes classes
  (`TaskDrawStatus`, the battle menu in the normal overlay, the stealth icon).
- Separate entry points need their own markers: the title loop (`title_TitleFrameStep_4f0b20`
  is drawn outside the table), pause drawing in `GameFrameUpdate_27c4c0`, and
  `MoviePlayModal_267c60`.
- The renderer applies the x-transform to vertex XY and SCISSOR in frame-pixel space, after
  XYOFFSET. It never applies it to readback or write-back addressing.
- Because markers ride the same VIF1 chain as VU1 packets, ordering with 3D is preserved.
- Add a cutscene option, "widened" or "4:3": when an event player or the letterbox is
  active, force aspect 0.75 and class CENTER for the whole frame.

**Stage 3: internal resolution.**

- Make `gpu_config.scale` per-axis (`sx`, `sy`). The anamorphic frame needs horizontal
  density: at 1920x1080 16:9 that is 512 → 1920, about 3.75 → 4×, while vertical
  448 → 1080 is about 2.4 → 3×.
- Keep write-back at the centre sub-sample per axis.
- Implement direct sampling of upscaled targets for matching-layout copies, first for
  `GfxFlipBuffersMaybe_143650`'s copy, then bloom, DOF and glare. Each effect then gets
  "original" (native sample, the reference) or "enhanced" (upscaled sample).
- Render 2D sharp. Font and sprite textures come from the mirror at native texel size
  anyway; only the rasterisation scales.

## Risks

- Overlay 2D (battle menu, the factory and insect menus) is not WIDE-aware, and the
  overlays are where the per-element class splits will be needed.
- Retail-WIDE squeezes and renderer squeezes must never both apply.
- Upscaled lines and points stay one native pixel wide (GPU.md).
- Per-sprite WORLD squeeze widens the gaps between digits in multi-sprite numbers. Add
  per-element centre markers in `DamagePopupDrawAll_2d2ea0` and
  `ScreenMarkerDrawAll_31af50`.
- Full-screen 2D backgrounds in CENTER menus leave side bars. An optional fill (blurred
  edge or solid colour) is a presentation setting.
- Wider Hor+ exposes unbuilt set edges in some event scenes. The cutscene 4:3 option is the
  fallback.

## Test plan

**Aspects:** 4:3, 16:9, 16:10, 21:9 (2.33 and 2.37), plus 32:9 as a stress case. Run each
at scale 1 and at the 4×3 per-axis scale.

**Scenes** (from snapshots or the P4 scripted run):

1. First town, field: minimap, compass, NPC and event icons, door cursors.
2. Dungeon with an outdoor sun: lens-flare occlusion near both frame edges (depth probes).
3. First battle: target slots, attack chain, HP gauges, damage numbers, battle menu.
4. Dialogue: message window, name plate, choice arrow, scissored scrolling text.
5. An event cutscene with letterbox and a camera track (`CameraTrackUpdate_305960`).
6. Main, shop, factory and insect menus, including model previews.
7. Title screen.
8. One 448-line movie and one 336-line movie.

**Checks:**

- **4:3 "Original".** Frame hash identical to the reference at scale 1, and identical
  write-back memory at every scale.
- **16:9 reference.** The Stage 0 port matches PCSX2 with `D_00481638 = 1` (same culled
  object sets, same frames).
- **Gameplay unchanged.** The state-trace corpus is identical across all aspects after
  excluding presentation state (screen markers, door-cursor fades, aim-offscreen).
- **Culling.** No object pops in inside the visible edges: log `ModelPrepareDraw`
  visibility at the frustum edge.
- **HUD placement.** All HUD inside the frame, anchored corners at the expected margins,
  no stretched glyphs, scissors aligned with their text.
- **Movies.** Pillarboxed at 4:3 in every aspect.
- **Readbacks.** Depth-probe values identical between scales 1 and 4 for the same aspect.
