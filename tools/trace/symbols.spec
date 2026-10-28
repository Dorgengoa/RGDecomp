# SPDX-License-Identifier: CC0-1.0
# Hand-picked game-state symbols for per-variable trace hashing.
# gen_regions.py turns this into regions_symbols.cfg.
#
#   name  address  size  evidence
# address: D_ symbol address (MAIN image), or *PTR[+OFF] = follow the u32
#          pointer stored at PTR (read from the same snapshot) and hash
#          [*PTR+OFF, +size). A null or out-of-RAM pointer hashes as "ptr:<value>".
# size:    hex/dec bytes, or 'auto' = distance to the next D_ symbol referenced
#          anywhere in game/src (the decomp's own symbol boundaries), capped at
#          0x1000.
# Evidence: the naming database (../RGDecomp config/names.txt @ 2efa6b43,
# ingested as game/) and the matching decomp source. Names are ours (the
# corpus is address-named); the D_ address is the ground truth.
#
# --- frame / system ----------------------------------------------------------
VblankCount        0x004810C4  4      GfxVblankStartHandler_15df20 increments it; GetVsyncCount_15df00 reads it; WaitVsyncCount_15de90 spins on it
VblankWaitFlag     0x004810C0  4      set by WaitVsyncCount_15de90 so the vblank handler iSignalSema(D_0047DF18)
GameMgrPtr         0x004810A4  4      global manager / gfx draw context pointer (GameMgrVif1HandlerStop_15dc40, +0x3BA0 name table)
LoadedOverlayId    0x0047E254  4      OverlayLoad_1c3210 stores the index 0..6 it loaded; GetLoadedOverlayId_1c3200 returns it
SysMode            0x0047E224  4      main-loop mode MainLoop_1c2c10 switches on (0 -> overlay 3/6, 1 -> 2 TITLE, 2 -> 1, else 0)
SysModeNext        0x0047E228  4      requested next main-loop mode (copied into SysMode at the top of MainLoop_1c2c10)
GameModeStack      0x004B51A0  0x40   16-deep game mode stack, [0] = current (GameModeStackPush_1f58f0; GameModeDispatch_27c670 runs handler 1..21; 6 = FieldExploreModeUpdate_2833a0)
GameModePhaseStack 0x004B51E0  0x40   parallel 16-deep phase stack
DataSetLang        0x0048155C  4      selects the row of overlay table D_0044AF90[lang][7] (OverlayLoad_1c3210, OverlayLocateFiles_1c3300)
# --- RNG -----------------------------------------------------------------------
RandState          *0x00449858+0xA8  8   Rand_133710: newlib rand, state u64 at _impure_ptr(D_00449858)+0xA8, x*0x5851F42D4C957F2D+1
# --- pad -------------------------------------------------------------------------
Pad0               0x004B2570  0x270  static pad objects ("static pads D_004B2570"); port0 decoded word at +4 (PadReadData_184df0 dst); port1 object at +0x270
Pad1               0x004B27E0  0x270  port-1 pad object (FUN_001843a0(0x4b27e0))
# --- tasks ---------------------------------------------------------------------
TaskTable          0x004D7FA0  auto   named task table: TaskStatePushAll_27c220 / TaskTableSetEnabledByName ('Chara Think', ...)
TaskStateDepth     0x00482278  4      push/pop depth of TaskTable (TaskStatePushAll_27c220 ++, TaskStatePopAll_27c250 --)
# --- game data / party -----------------------------------------------------------
GameData           0x004B8B30  auto   static settled GameData (GetGameData_1fede0, 755 callers; +0x14 CharaMgr, +0x18 party)
GameDataPtr        0x00483748  4      GameData pointer (->+0x20 CharaSys +0x24C bit0 = battle active)
PartyPtr           0x00483820  4      party object pointer (leader s16 +0x18E, active list +0x190, reserve +0x196)
Party              *0x00483820 0x200  party object fields up to the 7-entry reserve list (+0x196..+0x1A4)
CharaListHost      0x004838E8  4      chara list host pointer (CharaMgrPoolFindByDataId; 10-unit pool)
ActionMgr          0x004B8680  0x40   static CActionManager 0x40 (GetActionMgr_1fdb50); +0x20 CActionChara list
SkillTimers        0x004E9800  0x600  64 x 0x18 skill timers (SkillTimerReset; GameDataUpdate clock)
SkillSlots         0x004E9770  0x90   skill slot table 0x48-stride, s16 +0x3C (precedes SkillTimers)
# --- scene / camera / events ---------------------------------------------------------
GameScene          0x004A7000  0xB570 retail CGameScene 0xB570 static (vtable D_00471210): camera stack +0x5DDC, fade block +0x5980
Camera0            0x004B5660  0x2F0  6 x 0x2F0 camera objects registered in scene slots 0-5 (SceneCamerasInit_1f6c10)
Camera1            0x004B5950  0x2F0  "
Camera2            0x004B5C40  0x2F0  "
Camera3            0x004B5F30  0x2F0  "
Camera4            0x004B6220  0x2F0  "
Camera5            0x004B6510  0x2F0  "
EventScenePtr      0x00481F78  4      event world/scene pointer (ObjRecGetLiveObject_1c4a90(D_00481F78, id))
EventContext       0x00481F28  auto   gEventContext {arg, player} the event handlers read (main.symbols.txt)
SystemVm           0x004BD270  0x40   gSystemVm: system script VM, +0x3C gate read by SystemVmUpdate_2509f0 (main.symbols.txt)
TimerAccumA        0x004824C8  4      TimerAccumulate f32
TimerAccumB        0x00482544  4      TimerAccumulate f32
MenuStateMachine   0x00482350  auto   menu state machine (main menu init 297ac0)
# --- heaps -------------------------------------------------------------------------
HeapA              0x004BB890  0x60   mgCMemory heap object (MemStackCtor_14e030; MemStackGetStats_14d0e0 walks its +0x18 block list)
HeapB              0x004BB8F0  0x60   second mgCMemory heap object
HeapNpcData        0x004B6920  auto   'NPC Data' heap (NpcDataStackInit_1fd7d0)
# --- title overlay state (main .bss shared with TITLE via gp) ------------------------------
TitleMenuSel       0x004803AC  2      title menu selection b23c: 1 NEW GAME, 2 CONTINUE, 4 OPTIONS (title disasm, memory notes)
TitleMenuOpened    0x0048416C  2      title menu opened/blocked flag (0x4eb23c / 0x4ebb34 / 0x4ebb18)
TitleCounter       0x00484164  4      title page frame counter (idle-timer open at 196..1730)
SaveExists         0x0047E5B4  1      save-exists flag from the boot memory-card scan (func_206b00)
