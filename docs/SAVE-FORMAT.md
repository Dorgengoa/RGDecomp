# Rogue Galaxy save file format (and the save editor)

The game's memory-card data file `BASCUS-97490LV5RG_NN` (0x1BC00 bytes), decoded from the
decompiled save / load code for test fixtures: `tools/fixtures/saveedit.py` dumps and patches
it and recomputes both digests, so the game's own checks accept the result. The card side
(directories, icon.sys, libmc, the save manager) is [SAVES.md](SAVES.md) section 1; this file
is the content. Status 2026-10-18 (late): header, summary, chunk tree, story state (flags /
vars / chapter / progress slots / map markers), **how CONTINUE places the party** (summary ->
mode message), the party object (planet / area / sky, members, money), the character
records (level, HP, stats, equipment), the inventory objects and the Insectron team table
are decoded; the editor can apply the game's own per-chapter start states
(`initial_status5`, "Game data the save editor uses") and spawn the party anywhere the
debug jump table names. That is what the card library is made of (docs/TEST-FIXTURES.md
"Card library").

## Layout

| Offset | Size | What | Code |
| --- | --- | --- | --- |
| 0x000 | 0x50 | header | `SaveHeaderBuild_3e5520`, `SaveDataSerialize_3e6100` |
| 0x050 | 0x300 | summary (what the slot list, the title and **CONTINUE** read; the boot scan reads only 0x800) | `SaveHeaderBuild_3e5520` |
| 0x350 | | zero to 0x800 | |
| 0x800 | | chunk tree, then zero padding to 0x1BC00 | `SerialWriteChunkHeader_370e50` |

### Header

| Offset | Type | Value |
| --- | --- | --- |
| +0x00, +0x02 | s16 | -1, -1 on the card (slot record id / slot index in the in-memory copy, `SlotRecordStore_3e52f0`) |
| +0x04 | s16 | version 0x25 (`D_004658D8`; anything else: error 9, "bad data") |
| +0x06 | s16 | 0 (`D_004658E0`; mismatch: error 10, still loads) |
| +0x08 | s32 | save counter |
| +0x10 | s64 | payload length = end of the root chunk - 0x50 |
| +0x20 | 16 | MD5 of [0x50, 0x50 + length) (error 0xC on load) |
| +0x30 | s64 | 0x300 |
| +0x40 | 16 | MD5 of [0x50, 0x350) (error 0xB, checked by the slot scan too) |

MD5 is standard (`hashlib.md5(...).digest()` stored as is).

### Summary (0x50..0x350)

| Offset | Type | What |
| --- | --- | --- |
| 0x050 | f64 | play time (the slot list's clock) |
| 0x058 | s64 | money (party +0x160) |
| 0x060 | s16 | party size (members + reserve) |
| 0x064 | 10 x 0x28 | party entries in party-slot order (active, then reserve; `PartyGetSlotChara_3c2fb0`): name[16], s16 data id (11001 Jaster ..), s16 icon (= chara id), s16 level, pad, **f32 x, y, z, yaw: where CONTINUE puts member k (k < 3)** |
| 0x1F4 | 6 x f32 | **camera eye x, y, z and look-at x, y, z on CONTINUE** |
| 0x20C | s16 | chapter (story +0x8); copied to mode message +0x6 |
| 0x20E | s16 | 0 |
| 0x210 | s16 | progress value of the chapter (`ProgressValueGet_3cd2c0`) |
| 0x212 | u16 | key-item bits (Cancer / Leo / Libra King's key piece 0x4178 / 0x4179 / 0x417A) |
| 0x214 | char[0x40] | chapter title ("Ch. 1: Departure", phase_param #104) |
| 0x254 | char[0x40] | Insectron line ("Insectron: Not Yet Signed Up", from var 5 / 6 / 7, `SaveHeaderFormatLocationMaybe_3ee800`) |
| 0x294 | s16 | story var 0xD (`McSaveHeaderMergeFlagsMaybe_373060`: > 0 merges the unlock mask below into the title's flags) |
| 0x298 | s16 + char[0x80] | location record id (party +0xF8) and its name ("Rosa: Salgin: Near the Church"); display only |
| 0x31A..0x320 | 4 x s16 | record +0x16, party +0x4 (planet), +0x6 (area), +0xA |
| 0x324 | 4 x f32 | location record position, yaw (display copy) |
| 0x338 | u16 | story flags 0x1EA..0x1F1 as bits 0..7 |
| 0x33A, 0x33C, 0x33E | s16 | story vars 5, 6, 7 (Insectron rank / progress). **Title: var 5 >= 3 in any save on the card shows the INSECTRON row** (`McSaveHeaderCheckClearedMaybe_372fd0` -> `D_00483168` -> `title_TitleMenuUpdateExtraRow_4eca70`) |
| 0x340 | u64 | unlock mask from inventory (`UnlockMaskBuildFromInv_3e4020`: one bit per item of the ranges at `D_00480200`, category 10) |
| 0x348 | 3 x 2 bytes | insect cages: bit0 present, byte 1 = insects in it |
| 0x34E | u8 | number of registered Insectron teams (chunk 15 +0; the INSMENU slot list shows it) |

### How CONTINUE places the party (the spawn position)

The positions on load do **not** come from the party object. `title_TitleLoadConfirmCb_4ee2c0`
(load succeeded) -> `SaveSysMsgGet_373840` copies the system message that
`SaveSysResultCbMaybe_373e10` -> `SysMsgFillFromSaveRecMaybe_3e4d10` built **from the summary**:
kind 1, +0x4 slot record, +0x6 chapter (0x20C), +0x8/+0xA/+0xC 0x20E/0x210/0x212, member k
(k < 3) at +0x10 + 16k = summary entry k x, y, z, yaw, camera +0x40..+0x54 = 0x1F4..0x208,
+0x58.. = 0x31C/0x31E/0x320/0x298, location position. `title_TitleSessionShutdown_4f0820`
posts it (`SysMsgPostMaybe_1c3560` -> `D_004A3EF0`); `GameSessionInit_1f5d80` loads the map
(`MapLoadFromGameDataAndWait_2f4920`: party +0x4 planet ->
`PlanetAreaMatrixLookupByProgress_3ed840`, slot-0 area = party +0x6, sky = party +0x8) and
`PartyLoadAndPlaceMembersMaybe_2f4b00` case 1 sets member k's position and yaw from the
message and the camera (live object +0x60 eye = +0x40.., +0x50 look-at = +0x4C..). So a
"later area" save = planet / area / sky in the party object + positions and camera in the
summary (`saveedit.py patch --spawn` / `--spawn-jump`). Verified: Juraika (planet 3) loads
with the party in the jungle; the Dorgenark (planet 1, area 1000) on its bridge. The save
itself writes the leader at the location record's position (`SaveHeaderBuild_3e5520`, the
transporter the game was saved at) and the others at `PartyFormationPosCalcMaybe_1fff00`.

### Chunk tree

Chunk = `u32 kind, u32 version/id, u32 length` + payload (`SerialWriteChunkHeader_370e50`,
read by `UnpackWordTriple_370d70`). The root (kind 0) holds the six parts written by the
save object's sub-objects (`SaveDataSerialize_3e6100` order) and read back by
`SaveDataDeserialize_3e5c30`:

| Kind | Writer | Payload | In save2 |
| --- | --- | --- | --- |
| 1 | `OptionsSerialize_3d5de0` | options object | 0x2C |
| 2 | `StateBlockSerialize_3cb9d0` | **story state** = the StateBlock object (GameData +0x10) from +4, raw (`memcpy`) | 0x2324 |
| 3 | `CharaMgrPoolSerialize_3a8390` | characters: kind-4 chunks (version 1001..1005 = record version), each with sub-chunks 5 (the Chara object from +4) / 6 (10 kind-7 parts, `EquipSlotSerialize_39f4e0`; all empty in save2) (`CharaSerialize_3a9e70`) | 10 x 0x6B4 |
| 8 | `PartySerialize_3bf820` | 9 = the party object from +4 (raw), 12 = 0x33C0 table at party +0x174, 10 = item objects (`InvObjSerialize_3d3a80`, kind 11 each), 13 = `D_00465B70` x 4 bytes at party +0x17C | 0x89B0 |
| 14 | `CharaSysSerialize_3a0b30` | chara system object | 0xB94 |
| 15 | `InsectTeamTableSerialize_42fdd0` | Insectron team table from +4 (raw) | 0x1188 |

Raw object copies carry whatever pointers the object holds (StateBlock +4 = its tables
pointer, team table +0x1188, item-def pointers); on the port these are host addresses. The
loaders keep or rebuild the live value (`InsectTeamTableLoadBlob_42fc60` restores +0x1188,
`InvObjLoadState_3d3940` looks the item def up by id), and the port's own saves load back
(save2), so they are harmless; a retail card has PS2 addresses there.

### Story state (chunk 2; StateBlock offsets, file offset = chunk data + offset - 4)

From `StateBlockReset_3cd670` and its accessors:

| Offset | What | Accessor |
| --- | --- | --- |
| +0x08 | s16 chapter (1 in save2) | `StateGetChapter_3cd5b0`, `ProgressSetChapter_3cd480` |
| +0x0A..+0x26 | **15 x s16 progress slots** (reset 10): one per (chapter, sub-chapter) row of phase_param, in its order: ch 1..7 = slots 0..6, 8-A/B/C = 7..9, 9..13 = 10..14; value = phase (10, 20, ..) | `ProgressValueGet_3cd2c0` / `ProgressValueSet_3cd020` (`GroupTableFindEntry_422950` row +8 = slot); setting the chapter re-applies all slots (`ProgressReapplyChapter_3cd330`: earlier chapters = their last phase, later = first) |
| +0x28 | 2048 story flags (byte n>>3 bit n&7). **Names: rc/param/bit_flag_param_EN** (0..353 'EV01-0010'.. event done, 350..391 'Help Sheet: ..' tutorial shown, 1460.. 'Info-Edge: ..'; `saveedit.py dump --flags` prints them) | `StateFlagTest_3ccd70`, `StateFlagSet_3ccb70` |
| +0x128 | s16 vars[0x80] (names: short_flag_param_EN: 5 'Insectron Rank', 9 'EV09 No. of Placed Key Pieces', 12 'Chapter 14 Phase', 13 'No. of Times Game Cleared', ..) | `StateVarGet_3ccac0`, `StateVarSet_3cc9c0` |
| +0x228 | 2048-bit set ("flags 2") | `StateFlag2Set_3cc6d0` |
| +0x328 | 256-bit set ("flags 256"; initial_status #114 sets small ids 0..5 and up) | `StateFlag256Set_3cc4c0` |
| +0x348 | s16 count, +0x34C s32 ids[4]: active map-marker sets (the minimap's objective star) | `StateBlockMapMarkerSetAddMaybe_3cc170`, `StateBlockCollectMapMarkers_3cc390` |
| +0x360 | 1280-bit set | |
| +0x400, +0x440, +0x840 | s8 tables (reset -1), +0x880 f64[0x40] timers (reset -1.0) | |
| +0xA80.. +0x2322 | zeroed blocks | |

Known meanings (decomp call sites):

| Item | Meaning | Where |
| --- | --- | --- |
| flag 0x3E8 (1000) | main-menu row 6 **Factory** unlocked (set by the late initial_status sections too) | `TopMenuRow6UnlockedMaybe_29ac20`, `TopMenuLayoutEntries_294ad0` |
| key item 0x40E5 (category 10, inventory) | row 5 **Insects** unlocked (the insect-cage menu, game mode 14, MAIN code) | `TopMenuRow5UnlockedMaybe_29ac50` |
| `TopMenuIsHunterUnlocked_29ac90` | row 4 (Hunter) | |
| var 5 | Insectron rank; summary copy >= 3 shows the title's INSECTRON row | above |
| flag 0x7F8 | battle / field / menu behaviour switch (several readers) | `BattleModeUpdate_280220`, `FieldExploreModeUpdate_2833a0` |
| flag 0xB6 | equip-menu party rule | `MenuEquipSlotChoice*` |

### Party (chunk 9; party offsets, file offset = chunk data + offset - 4)

| Offset | What |
| --- | --- |
| +0x04 | s16 **planet id**: 1 Dorgenark, 2 Rosa, 3 Juraika, 4 Zerard, 5 Vedan, 6 Mariglenn, 7 ghost ship, 8 Rose Nebula, 9 space, 10 ghost ship EX, 21 Alistia (dbg/map_jump_en.txt header, planetarea_matrix5 keys). `MapLoadFromGameDataAndWait_2f4920` |
| +0x06 | s16 **area id** = map slot 0 (area_param: 100 Rosa_A, 200 Juraika, 400 Zerard, 500 Vedan, 600 Mariglenn, 700 ghost ship, 800 Rose Nebula, 900 space, 1000 Dorgenark, 1700 ghost ship EX, 300 Alistia ..) |
| +0x08 | s16 **sky id** (sky_param: 100 Rosa .. 900 Pacifia); +0x6 / +0x8 for a planet at a story point = planetarea_param5 row of planetarea_matrix5[planet x 10^7 + chapter x 1000 + sub x 100 + phase] |
| +0x0A | s16 map area slot (`MapFindAreaSlotById_1e4cb0`), +0x0C s16 location / zone record (`GroupTableFindEntry_415e00(id / 100, id)`), +0x10 s32 nav graph: re-derived in the field by `PartySetLocationMaybe_3c9cd0` (stale values load fine) |
| +0x2C.. +0x36 | reset on load (`PartyDeserialize_3bf4f0`): +0x30 map id, +0x32 map box |
| +0x3A / +0x3C | counts of the keyed / radius zone pairs at +0x3E / +0x5E (8 x {s16 group, s16 id}) |
| +0x90 | f32[4] leader position (field) ; +0xA0 3 x f32[4] member positions; +0xD0 f32[3] yaws; +0xDC f32[3] distances to the leader. Used by the next save when the location record is missing (`PartyGetSavedMemberPos_3cafa0`) and by battle setup; **not** by CONTINUE |
| +0xF8 | s16 location record id (201 = "Rosa: Salgin: Near the Church"; `GroupGetRecordById_425590`): the save's display name and the leader position the next save writes. Changing it alone does not move the party |
| +0x160 | s64 money (`PartySetMoney_3c9720`, capped at `D_004659E0`; summary 0x58) |
| +0x168, +0x174, +0x17C | item pool, the chunk-12 table, the chunk-13 table (pointers) |
| +0x18C | s16 active member count (1..3, `PartySetActiveCount_3c1ec0`) |
| +0x18E | s16 leader chara id (`CameraSnapToLeader_1f6a00`) |
| +0x190 | s16 active[3] chara ids (-1 empty), +0x196 s16 reserve[7] (`PartyAddMember_3c1430`, `PartyMoveToReserve_3c19b0`, `PartyMembersReset_3c31b0`) |
| +0x42D0 / +0x4310 / +0x4350 | per-chapter money earned / spent / balance (s32 x 16 each, `PartyAddMoney_3c8e90`) |

### Characters (chunk 3 > 4 > 5; payload = the Chara object from +4)

| Payload | What |
| --- | --- |
| +0x000 | s32 data id: 11001 Jaster, 11002 Deego, 11003 Simon, 11004 Kisala, 11005 Steve, 11006 Lilika, 11007 Jupis, 11008 Zegram, 11009 Hooded Man, 11010 ??? (chara_param_EN) |
| +0x004 | s32 record version (= the kind-4 chunk version) |
| +0x008 | s32 chara id 0..9 (what the party arrays and the summary icon hold) |
| +0x00C | s32 level |
| +0x010 | s32 HP, +0x014 AP, +0x018 / +0x01C max HP |
| +0x020 | s16 pairs: +0x20 AP, +0x28 stat 3 + a bonus, +0x2C stat 2, +0x30 stat 3, +0x34 stat 4 (= chara_levelup_param2: level-1 row + increments up to the level; checked against all ten save2 records) |
| +0x230 | flag byte (object +0x234): bit 1 in party (`PartyAddMember_3c1430`), bit 2 set by initial-status party modes 4 / 5 (`CharaSetFlag234Bit2Related_3ae370`) |
| +0x23A / +0x23C / +0x23E / +0x240 | s16 equipped item unique ids: weapon slot 0, weapon slot 1, clothes, accessory (-1 none; `WorldDataCmdCharaSetEquip_3b97e0` vcalls 0x378 / 0x3C0 / 0x3D4). **A party member without a slot-1 weapon crashes the battle**: `CharaCmdShot_229bc0` calls through the NULL `CharaGetEquippedWeapon` result (seen with a hand-edited party; retail never has such a party) |

### Inventory (chunk 10: one kind-11 chunk per item, version = object kind)

Payload = the item object from +4 (`InvObjSerialize_3d3a80`; created by
`InvObjCreateForItem_3c7110`, set up by `ItemSetup_3d4ff0` and the kind's setup):

| Payload | What |
| --- | --- |
| +0x00 | s16 unique id (`InvAllocUniqueId_3c4f10`; the characters' equip slots hold it) |
| +0x02 | s16 list slot (the initial-status `#102` slot; equipment 0) |
| +0x04 | bits |
| +0x08 | s16 item id (item_param_EN), +0x0C item-def pointer (looked up again on load, `InvObjLoadState_3d3940`) |
| kind 1 (stack: consumables, boosters, materials, feed) | +0x10 s32 count |
| kind 2 (weapon) | +0x10 u16 0, u8 1, the def's 5 weapon bytes (item_param #106, `ItemWeaponSetup_3d3730`), s8 -1, pad |
| kind 3 (special weapon) | kind 2 + f32 gauge = item_param #114[0], s16 0x21 (full), s16 0 (`ItemSpecialWeaponGaugeFill_3d2f90`) |
| kind 0 | key items, clothes, shields (no extra) |
| kind 4 (insect) | +0x10 s16 GameRec insect record index (0..14), +0x14 record pointer (rebound on load); list slot in inventory list 7 (0x284..0x295) |
| kind 5 (Insector Trap, def code 0x4B0) | +0x10 s16 GameRec trap record index (0..2), +0x14 pointer |
| kind 6 (Rearing Cage, def code 0x4B1) | +0x10 s16 GameRec rearing record index (0..2), +0x14 pointer; the cage number is the def's +0x3 (Rearing Cage I / II / III = 0 / 1 / 2) |

`saveedit.py` reproduces all eight save2 objects byte for byte (except the pointer).

### Insects and cages (kinds 4 / 5 / 6 + chunk 12, 2026-10-25 cov3)

An insect / cage object is 0x1C bytes (`InvObjCreateForItem_3c7110`, factory
`InvObjCreateByKind_3c75c0`; vtables `D_00475B10` insect, `D_004759F0` trap, `D_004758D0` rearing
cage; save size 0x1C - 4): the common header, +0x14 s16 index of its record in the **GameRec
table**, +0x18 the record pointer (rebound from the index on load, vtable slot 0x28
`ItemGameRecBind_*`). The GameRec table is the 0x33C0 object at party +0x174, saved raw as
**chunk 12** (`PartyDeserialize_3bf4f0` memcpy; all zero in save2):

| Offset | Records | Accessor |
| --- | --- | --- |
| +0x0000 | 15 insect records x 0x34 | `GameRecGetInsectSlot_3ce350`, cleared by `GameRecInsectSlotClear_3d2780` |
| +0x030C | 3 Insector Trap records x 0x7F0 (placement, bait, catches) | `GameRecGetCageSlot_3ce1f0` |
| +0x1ADC | 3 Rearing Cage records x 0x84C | `GameRecGetInsectRecSlot_3ce090` |

Every record +0 bit0 = in use, bit1 = reclaimable (`GameRecFindFree*`).

- **Insect record** (`InsectItemSetup_3d1fb0` from the def's item_param #115 data, accessors in
  the vtable): +0x1 name[16] (+0x10 NUL), +0x12 s16 exp (`InsectItemGetExp_392240`), +0x14 / +0x16 s16 max HP / HP, +0x18 u8
  satiety, +0x19 / +0x1A u8 growth cap / left, +0x1C / +0x1E s16 attack / defense (the battle
  piece keeps them as u8, `insect_InsectPieceLoadFromItem_516360`), +0x20 u8 six stats (cap 100),
  +0x26 personality (0..4), +0x27 level (1..5), +0x28 bit0 sex, bit1 adult, +0x2C s32 colour (0..9),
  +0x30 f32 satiety timer (`InsectItemTickSatiety_3d1110`: grows while satiety > 0, one satiety point per period).
- **Rearing Cage record** (`ItemGameRecReset_3d0320`): +0x2 s16 insect unique ids[5] (-1 empty),
  +0xC insect object pointers[5] (re-resolved on load from the ids in inventory list 7,
  `InsectRecSlotsResolve_3cfbd0`), +0x20 / +0x22 s16, +0x24 two breed records x 0x14
  (`InsectBreedRecReset_3d2730`: -1, -1, 0, -1, f32 -1, f32 -1), +0x4C 16 x 0x80 message entries.
- **Trap record** (`ItemGameRecReset_3d0e50`): +0x2..+0x8 s16 -1, +0xC..+0x1C 0, +0x7EC f32 -1.

How the game puts an insect in a cage (`WorldDataCmdAddItemMaybe_3b9d40`, initial_status #102 of
an insect item): the first Rearing Cage (`InvGetCageItem_3c8040`: category 12, code 0x4B1, def
index 0..2) with a free place (`InsectRecSlotFindFree_3d0210`, 5 per cage) gets a new insect
object (`InsectItemCreateWithRandomName_3cff30`: list 7, a random name from the species' name
table, then the section's name) whose unique id goes into the cage record
(`InsectRecSlotAddItem_3d0190`). The summary's 0x348 bytes mirror the three cages. The
**story Insectron entry counts these insects** (`EvCmdInvCountInsects_25c280` ->
`InvCollectInsects_3c4d90`: list 0 and list 7 objects that cast to an insect).

`saveedit.py patch --section-insects SID` adds a section's traps, Rearing Cages, named insects,
feed and Insectron License (e.g. 115 'Insectron E-5', the developers' Insectron start states
102..191 carry 3 + 3 cages and 15-16 insects; the 16th does not fit, as in game);
`--add-insect ID[:NAME]` / `--add-item 16744` add one; `--strong-insects` gives the added insects
level 5, stats 100, HP x3, attack / defense x4. The records take the top of each random range
(deterministic). Checked live (`insectstory.py`, "gamerec" phase): after CONTINUE the game's
GameRec table equals the card's byte for byte except the 15 re-resolved insect pointers and the
insects' satiety timers (+0x30, already ticking: 32.0 at the first probe), and the
INSECT overlay's team selection lists the cards' insects (KNIFE A .. at Lv5).

### Insectron teams (chunk 15; offsets in the payload)

`InsectTeamTableAddTeam_431480`, `InsectTeamCodeEncode_4319f0` (the password encoder names
the field widths), `InsectTeamTableLoadBlob_42fc60`:

| Offset | What |
| --- | --- |
| +0x0 | s32 number of teams |
| +0x4 + 0xE0 k | team k (20): name[9] (alnum, 8 chars), owner[6] (alpha, 5), +0xF s8 (3 bits), +0x10 bit0 **used**, bits 1-2 encoded, bit3 cleared on add; +0x18 five insects x 0x28 |
| insect +0x00 | name[13] |
| insect +0x0D | species (5 bits): item def category 0x14, key 2000 + species (`ItemDefFindInsect_40c690`) |
| insect +0x0E | variant (3 bits) |
| insect +0x0F | 4 bits; +0x10..+0x15 six stats (7 bits); +0x18 (3); +0x1A u16 (10); +0x1C, +0x1E u16 (7); +0x20 bits 0-1; +0x21 (3); +0x22 (1) |
| insect +0x24 | item-def pointer, rebuilt on load |

These are the "registered teams" the standalone Insectron mode (title INSECTRON row, INSMENU
overlay) loads from a save (`SaveFileReadInsectTeams_3e49d0`, "Select registered team").
`saveedit.py --insect-team SLOT:NAME:SP,SP,..` writes a team with species SP, variant 0,
stats 40, +0x1A/+0x1C/+0x1E = 100/50/50 (shown as "Lv0" insects; the battle runs with them).

## Game data the save editor uses

Instead of guessing story state, the editor reads the game's own tables (tools in
`tools/fixtures/`, cache `out/fixtures/gamedata/`, game-derived, never committed):

- `gamedata.py list|get|pac|cfg`: files of `data/DATA0_0.HD6/.DAT` (index record = one u64:
  name-stream offset bits 0-17, offset bits 18-37 x 2048, size/4 bits 38-63; recomp's
  hd6_map.py u16/u24/u24 reading is off for many files) and the `.pac` chains inside
  ({name[0x40], u32 header size 0x50, u32 size, u32 next}).
- `cfgdump.py PAC_OR_FILE [MEMBER]`: disassembles `.cfg.bin` (CfgVm byte code:
  `CfgVmLoad_42fac0` header {count, string pool offset, pool size, ?}, commands {u16 id,
  u8 argc, 2-bit types (string / int / float / none), values}, `CfgVmStep_42f6e0`).
- `rgdata.py`: the parsed tables.

| Table | What it gives | Used for |
| --- | --- | --- |
| `rc/param/initial_status5.cfg.bin` | **278 developer start states**: section 0 "game start", 1010 "Ch1 10" .. 13020, chapter 8-A/B/C 8110..8333, battles 20010.., ghost ship 14010.., Alistia 28010.., area masters, Insectron ranks. Commands = the `WorldDataCmd*` table at `data2c_00466030`: 100 section, 101 money, 102 item (slot, id, "*N"), 103 party member (data id, mode 0 out / 1 leader / 2 member / 3 reserve / 4-5 reserve + bit 2), 104 level / exp / HP / MP, 105 equipment, 106 abilities, 109 options, 110 field enables, 111 story flags, 112 vars, 113 flags 2, 114 flags 256, 115 map markers, 117 pending encounter | `saveedit.py patch --section SID` |
| `phase_param_EN` (param_2_en.pac) | chapters 1..13 (8 has A/B/C), their phases (10, 20, ..) and titles | chapter, progress slots, summary title |
| `planetarea_matrix5` / `planetarea_param5` | (planet, chapter, sub, phase) -> area id, sky id (+ the docked Dorgenark model / spot) | party +0x6 / +0x8 |
| `dbg/map_jump_en.txt` | 437 debug jump points: planet id, x, y, z, yaw, label (planet bases, Dorgenark bridges / spaceports, event triggers, next-episode markers, signboards, last-boss maps, ghost ship EX floors) | `--spawn-jump ID` |
| `event_param5` | events: planet, area, camera and party end positions | spawn points (Alistia) |
| `chara_param_EN`, `chara_levelup_param2` | names, default equipment; per level exp and stat increments | levels / stats |
| `item_param_EN` | item names, categories, weapon bytes (#106), special gauge (#114) | inventory objects |
| `bit_flag_param_EN`, `short_flag_param_EN` | names of the 2048 story flags and the vars | `dump --flags`, `--no-help` (350..391) |
| `area_param`, `sky_param`, `trigger_param6`, `zonephaseset*`, ... | area names / map dirs; event triggers (base64-like encoded conditions, not decoded) | reference |

## saveedit.py

```text
python tools/fixtures/saveedit.py dump  SAVE [--flags] [--vars] [--chunks] [--all]
python tools/fixtures/saveedit.py patch SAVE [--section SID ..] [--no-levels] [--no-help]
      [--spawn-jump ID | --spawn PLANET:X,Y,Z,YAW] [--set-flag N] [--clear-flag N] [--var I=V]
      [--chapter C] [--location ID] [--party16 OFF=V] [--insect-team SLOT:NAME:SP,..]
      [--summary-var5 V] [--no-summary-sync] [--abilities] [--learn DATAID:ID,..]
      [--add-item ID[:N]] [--insect-team ..] [--insect-formation]
      [--section-insects SID] [--add-insect ID[:NAME]] [--strong-insects] [--insect-limit N]
python tools/fixtures/saveedit.py copy  SRC_SAVES DST_SAVES
python tools/fixtures/saveedit.py check SAVE
python tools/fixtures/saveedit.py make  [NAME ..]      # RECIPES + cardlib.LIBRARY from cards/save2
```

SAVE is the data file, a slot directory or a saves dir (first save found). `patch` keeps the
summary mirrors (chapter, var 5/6/7/0xD, flags 0x1EA..) in sync and always rewrites both
digests. `--section` applies an initial_status section on top of the save the way the
WorldDataCmd handlers do (flags / vars / flag sets / markers / money set; party members
reset and re-added by mode; levels with stats from the level table; inventory cleared and
rebuilt from the section's items, the party's equipment added and equipped), plus chapter,
progress slots and the summary's party list / title; repeatable (e.g. 13020 then a ghost
ship section). `--spawn*` sets planet, area / sky (planetarea matrix at the save's story
point), the summary positions (leader + the two followers at the case-0 formation offsets)
and camera. `--abilities` (with `--section`) also applies the section's abilities, `--learn`
any list (see "Abilities" below). Not applied: HP/MP overrides, options, field enables; insects and
cages only with `--section-insects SID` (above). Test: `fixtures.saveedit` (synthetic save, `tests/fixtures/saveedit_test.py`: flags,
vars, chapter, location, insect team, spawn, inventory rebuild, digests).

## Open

- Trigger conditions (`trigger_param6`, base64-like strings) are not decoded, so which
  event fires at a spawn point is found by booting (bootcheck reports it).
- Chunk 13 (party +0x17C): {-1, 0} pairs in save2, meaning unknown. Options chunk not decoded.
  (Chunk 12 = the GameRec table, decoded 2026-10-25, "Insects and cages" above.)
- The exp field is not written (a section's levels come with exp 0, as the game's own sections do).
  Abilities: written since 2026-10-25 (soak2), below.

## Abilities (`saveedit.py --abilities`, `--learn`; 2026-10-25 soak2)

`WorldDataCmdCharaLearnAbilities_3b9720` (initial_status #106) calls `CharaLearnAbility_3ad460`
per ability id; the editor reproduces it on the save:

- the character's ability list = `chara_ability_param3` (#200 data id, #202 {index, ability id},
  `rgdata.chara_abilities()`); the learned set is the u64 at Chara object +0x2E0 (payload
  +0x2DC), bit index-1; learning an ability clears the bits of the same family (ability def byte
  m4: its other levels);
- ability defs `ability_param_EN` #4 {id, '', name, m2, m3, m4 family, m5 level}
  (`rgdata.ability_defs()`): m2 == 0 = an active (Flash Sword, Star Charm, the combination attacks
  Fated Passion / Supernova ..) also takes an equip slot: the slot of the same family is re-set,
  else the first empty one (`EquipSlotSetAbilityFromObj_39fb80` -> `EquipSlotSetAbility_3a07b0`:
  slot +8 s16 ability id, +0xA s16 owner chara id, +0xC use count, +0x10 f32 gauge; a fresh slot
  keeps 0), then the 10 slots are bubble-sorted by family with empties last. The slots are the
  kind-7 parts of sub-chunk 6 (part payload = slot +4..+0x28; empty = id / owner -1);
- family 0x86 (Burning Strike Lv1-3, ids 1341..1343, in every character's list) also sets the
  story flags 0x3ED 'Burning Strike Possible' and 0x3EE 'First Burning Strike'
  (`CharaResolveActionHitMaybe_3b28d0` tests 0x3ED).

Checked by booting: a `w_ch07_rosa` battle shows Jaster's Flash Sword / Break Throw / Whirlwind
in the battle menu's Abilities page and uses them (cut-in game mode 10/2).
