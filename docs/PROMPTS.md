# Button prompts per device

PLAN.md P6: show Xbox, Nintendo or keyboard prompts when that device is in use. This page
covers the data (the `gaiji2` texture and its tables), the tool that dumps and rebuilds it
(`tools/assets/gaiji.py`), and how the port switches it (section "Implementation"). The
mechanism comes from CONTROLS-AUDIT.md section 8.

## Summary

- Every button prompt in message text is an ASCII tag (`[l1]`, `(X)`, ...) drawn from one
  256×256 8-bit texture, `gaiji2`. Only 8 glyphs are buttons: L2 L1 R1 R2 and the four face
  buttons. The texture has no Start, Select, d-pad or stick glyphs.
- `gaiji.py build` redraws those 8 rects procedurally for Xbox, Nintendo and keyboard. The
  rects stay the same. It re-encodes the result in the game's exact format (IM3 + TIM2,
  PSMT8, CSM1 CLUT, swizzled, 66,704 bytes, under the 0x10800 cap) and checks the round
  trip.
- Switching is presentation-only. The port rewrites the texture's pixels and CLUT in place,
  and the switch is decided where `GaijiGetTex_270510` is called. Widths change only for
  wide keyboard labels, through one metric lookup (`FontFindGaijiMetric_26f8c0`). That keeps
  drawing, measuring and wrapping consistent.

## The data

### Where it is

`FontSystemLoad_3133c0` → `GaijiLoadImage_2705a0` copies `gaiji2.img` (`D_0045F688`) out of
`meswin/fontset_main_?.pak` (`D_0045F660`; `?` = `en` on the US disc) into the static
buffer `D_004C3180`. The buffer is at most 0x10800 bytes and `GaijiGetImageBuf_270590`
returns it. `GaijiRegister_270520` registers the buffer as an IM3 archive in the draw
context's name table and stores the handle of the texture named `gaiji2` (`D_0045F680`) in
`D_004820E0`. `GaijiGetTex_270510` returns that handle.

On the disc the pack is in `DATA0_0` and again in `DATA1_0` (`meswin\fontset_main_en.pak`,
788,720 bytes). `meswin\fontset_launcher_en.pak` has a third copy. All copies of
`gaiji2.img` are byte-identical (`gaiji.py dump` checks this).

### Container formats

| Layer | Format |
| --- | --- |
| `DATA*.HD6` | Directory record = LE u64: bits 0–17 name-stream offset (varint token string), 18–37 data offset in 2048-byte sectors, 38–63 size / 4 |
| `.pak` | Chained entries: `name[0x40]` (NUL-terminated, then junk), u32 header size 0x50, u32 body size, u32 next (relative, 16-aligned), u32 `@ABC`; body at +0x50. The chain ends with a size 0xFFFFFFFF entry. `fontset_main_en.pak` holds 3 font tables, 9 `FontTex_*.tm2` and `gaiji2.img` |
| `gaiji2.img` (IM3) | `IM3\0`, u32 0x10, u32 count = 1, u32 0; then one 0x40 entry: `name[0x20]` = `gaiji2` (then junk), u32 0x40, u32 TIM2 offset = 0x50, …, +0x34 u32 TIM2 size = 0x10440 |
| TIM2 | Version 4, 16-byte header alignment, 1 picture: header 0x30, image 0x10000, CLUT 0x400. `GsTex0` = 0x0000000221310000 (PSMT8, TBW 4, TW = TH = 8) |

### Texture format

| Property | Value |
| --- | --- |
| PSM | PSMT8, 256×256 |
| CLUT | 256 × 32-bit RGBA, **CSM1** order: within every 32 entries, entries 8–15 and 16–23 are swapped. PS2 alpha 0..0x80 (the file uses 0..0x7F). Of 256 entries, 251 are used outside the button rects. |
| Pixels | **Swizzled.** They are stored the way the GS holds a PSMT8 texture uploaded as PSMCT32. For this file decoding is unambiguous: the linear reading is noise (mean neighbour difference 71 against 16). `gaiji.py` implements the permutation and its inverse, and a test checks that it is a bijection. |
| PNG mapping | alpha8 = min(255, 2·a); back: a = (alpha8 + 1) / 2, which is exact on every value the forward mapping produces |

### Glyph tables (in `SCUS_974.90`)

| Table | Record | Read by |
| --- | --- | --- |
| `D_0044E680` | 12 bytes `{u16 code, s16 u, s16 v, s16 w, s8 h, s8 dx, s8 dy, pad}`, 37 records, ends at code 0 | Only `FontFindGaijiMetric_26f8c0`. `w` is the pen advance (`FontGetGaijiWidth_26f890`) and the quad width. `FontDrawGaiji_26dd50` centres the glyph vertically in the line (`(advance − h) / 2 + dy`) and adds `dx` to x. |
| `D_0044EA00` | 8 bytes `{char *name, s16 len, u16 code}`, 35 records | `TextGaijiTagFind_26f060` (linear `strncmp`) |
| `D_0047FC90` | 2 × `{s16 u, v, w, h}` = L1, R1 | `InsectCageButtonHintDraw_388ee0` only |

The button glyphs (`gaiji.py dump` writes all of them to `out/gaiji/gaiji2_glyphs.json`):

| Tag | Code | PS2 | Position | Action (INPUT.md) | Rect u, v, w×h | dx, dy |
| --- | --- | --- | --- | --- | --- | --- |
| `[l2]` | FD04 | L2 | left trigger | `decline` | 0, 0, 32×20 | 0, −3 |
| `[l1]` | FD02 | L1 | left shoulder | `camera_turn_left` | 32, 0, 32×20 | 0, −3 |
| `[r1]` | FD03 | R1 | right shoulder | `camera_turn_right` | 64, 0, 32×20 | 0, −3 |
| `[r2]` | FD05 | R2 | right trigger | `camera_recentre` | 96, 0, 32×20 | 0, −3 |
| `(O)` | FD06 | Circle | east | `cancel` | 0, 20, 22×22 | −1, −3 |
| `(A)` | FD07 | Triangle | north | `menu` | 22, 20, 22×22 | −1, −3 |
| `(#)` | FD09 | Square | west | `attack` | 44, 20, 22×22 | −1, −3 |
| `(X)` | FD08 | Cross | south | `confirm` | 66, 20, 22×22 | −1, −3 |

The other glyphs are left untouched. They include: `[+]` FD40, a white plus (not a d-pad);
FD3A/FD3B, two untagged arrows; FD3C/FD3D, untagged down and right triangles. Those two are
probably the art for the message-window page icon and the choice arrow, which are drawn
from fixed rects (`D_0045F6E0`/`D_0045F6F0`) via `FontDrawGaijiSprite_26fa50`; that link
is inferred, not traced. Also untouched: the status,
element and menu icons; and `(R)` FD3E/FD3F. **`(R)` is the registered-trademark sign ®,
not a right-stick or R3 icon.** The atlas shows a circled R (FD3F is the smaller variant
used for font type 2), so CONTROLS-AUDIT.md section 8's "right stick or R3 (inferred)" is
wrong.

Free atlas space: rows 163–233 at full width, and x 141–255 for rows 42–147.

## The tool: `tools/assets/gaiji.py`

Standard library only (Python 3.10+). It reads `data/` and writes only to `out/gaiji/`,
which is gitignored. Every output except `prompts_*.png` contains game art.

```
python tools/assets/gaiji.py dump                       # original atlas + glyph map
python tools/assets/gaiji.py build                      # xbox, nintendo, keyboard
python tools/assets/gaiji.py build --styles keyboard --bindings rg.ini [--wide]
python tools/assets/gaiji.py encode atlas.png out.img   # any 256x256 PNG -> game format
python tools/assets/gaiji.py decode in.img atlas.png
python tools/assets/test_gaiji.py -v                    # 13 tests; data tests skip without data/
```

| Output | What |
| --- | --- |
| `gaiji2_ps.png` / `.img` | Original atlas (RGBA) and the original file. `dump` checks that the decode re-encodes byte-identical. |
| `gaiji2_glyphs.json` | Every metric record with its tags, button, position and action; untagged codes; the insect-cage rects; format facts |
| `gaiji2_rects.png` | Atlas ×3 on a checkerboard, button rects outlined (review aid) |
| `prompts_<style>.png` | The 8 procedural glyphs on a transparent 256×256 sheet, no game art |
| `gaiji2_<style>.png` / `.img` / `.json` | Original atlas with the 8 rects redrawn, its game-format encoding, and the metric records it needs |

All art is drawn in code: rounded rects, ellipses and a stroke font defined in the file
(A–Z, 0–9, punctuation, arrows), with 4×4 supersampling. No third-party icons or fonts are
used, so THIRD_PARTY_NOTICES.md is unchanged. Styles:

| Style | Face (S / E / W / N) | Shoulders (L1 R1 L2 R2) |
| --- | --- | --- |
| `xbox` | A green, B red, X blue, Y yellow on dark discs | LB RB LT RT |
| `nintendo` | B, A, Y, X (positional: Cross's slot shows **B**) in white on dark discs | L R ZL ZR |
| `keyboard` | Key caps labelled with the first `key:` or `mouse:` binding of the action; a mouse icon (button highlighted) for `mouse:left/right/middle/x1/x2` | same |

**Palette.** The atlas must stay 256 colours, and 251 are in use outside the button rects.
Indices used anywhere outside the redrawn rects keep their colour. The other 5 go to the new
colours that would otherwise cost the most (premultiplied RGBA error × pixel count), and
every remaining new colour maps to its nearest entry. So the rest of the atlas is
bit-exact, and the new glyphs are slightly quantised (visually clean on the dark
backgrounds). A host-rendered RGBA32 replacement would avoid this, but the port has no
texture-replacement path yet (see Risks).

**Round trip.** For each style, `build` checks three things: `decode(encode(x)) == x` on
pixels; re-encoding the decoded file gives the same bytes; and re-indexing the PNG against
the final palette is lossless. The tests also check: the swizzle is a bijection and inverts;
CSM1 is an involution; a synthetic IM3 round-trips; PNG write/read round-trips; the original
re-encodes byte-identical; and pixels outside the redrawn rects are unchanged.

## Switching at runtime (design)

### Choosing the style

Implemented on the host side (INPUT.md "Device type and button prompts"):
`rg_host_active_pad_family(h)` wraps `SDL_GetGamepadType`, and `rg_host_prompt_style(h)`
resolves the setting to a style:

| SDL type | Style |
| --- | --- |
| `PS3`, `PS4`, `PS5` | `playstation` (original texture) |
| `XBOX360`, `XBOXONE`, `STEAM`, `STANDARD`, `UNKNOWN` | `xbox` |
| `NINTENDO_SWITCH_PRO`, `NINTENDO_SWITCH_JOYCON_*`, `GAMECUBE` | `nintendo` |
| keyboard/mouse | `keyboard` |

The setting is `prompts.style = auto | playstation | xbox | nintendo | keyboard` (default
`auto`, Original `playstation`). No device used yet keeps the current style. Scripted and
headless runs always get `playstation`, whatever the setting, so traces and frame hashes
don't depend on the device. The style names here (`playstation`) and `gaiji.py`'s (`ps`
for the original) differ only in spelling.

### Swapping the texture

Every gaiji draw gets its texture from `GaijiGetTex_270510`. Its callers are
`FontDrawGaiji_26dd50` (all tagged text), `FontDrawGaijiSprite_26fa50` (page icon, choice
arrow) and `InsectCageButtonHintDraw_388ee0`. `D_004820E0` has no other reader. The plan:

1. **At load.** After `GaijiLoadImage_2705a0` fills `D_004C3180`, a port service (host side,
   no game state) keeps the original bytes and builds one image per style. It runs the same
   steps as `gaiji.py build`: decode, redraw the 8 rects procedurally, quantise into the free
   palette slots, encode. The C++ port of the drawing code is small: shapes plus the stroke
   font, which `gaiji.py` is the reference for. The service never ships game art, because it
   always starts from the user's `data/`.
2. **On a style change.** An override of `GaijiGetTex_270510` (or a per-frame hook before
   the draw lists are built) compares the wanted style with the current one. When they
   differ, it copies the new image's pixels and CLUT (`0x10400` bytes at TIM2 + 0x40) into
   `D_004C3180`. It then returns the **same handle** as before. Keeping the handle,
   texture id and name-table entry fixed matters because several UI draws load textures by
   fixed id (`DrawListAddTexLoad_1418c0(h, 0x338, …)` and similar). It is not traced which
   id is `gaiji2`, so swapping handles could leave TEX0 and the uploaded texture out of
   step.
3. **Upload.** `DrawListAddTexLoad_1418c0` allocates VRAM through `TexGroupAllocVram_157e70`
   for each draw list. If that re-sends the image from EE memory every frame, the swap
   appears on the next frame. If it caches residency by id, the swap must also clear that
   entry. **To verify** with a GS trace of a style switch. The GPU renderer has no texture
   cache (GPU.md), so nothing on the host side needs invalidating.

The alternative is to register extra IM3s under new names (`encode(..., name='gaiji2x')`)
and have `GaijiGetTex_270510` return their handles. That costs 3 × 0x10490 bytes of EE
memory, plus name-table registration in `GaijiRegister_270520`, and it carries the
fixed-id risk above. It's a fallback if the in-place copy can't be made to re-upload.

The swap changes only presentation: no game logic reads the texture. It is safe under the
state-trace gate, provided that scripted runs stay on `ps`.

### Keyboard prompts from the bindings

For each of the 8 PS2 buttons, the label comes from the first `key:` or `mouse:` button
binding of the action that drives it. INPUT.md's actions drive exactly one `rg_pad` input
each, so the map is fixed: Cross → `confirm`, and so on (table above). Mouse motion
bindings are skipped. An unbound action shows "-". Keys get short labels so that they fit
the original rects (`Space` → SPC, `Return` → ENT, `Left Shift` → SHF, arrows → ↑↓←→,
`Keypad 8` → K8). The keyboard image is rebuilt whenever the action map changes: the
settings overlay, `--set`, a loaded file. `gaiji.py --bindings FILE` does the same from a
settings .ini (`[input] bind.<action> = ...`, old ids accepted).

### Width changes (`--wide`)

Full names (SPACE, ENTER, SHIFT) don't fit 22 or 32 pixels. `--wide` keeps the short
labels in the original rects, because fixed-rect code reads them. It then draws a second,
wider copy of each keyboard glyph into the free band (rows 163–233), with
`w = max(original, label + 8)`. The metric records in `gaiji2_keyboard_wide.json` point
there.

At runtime, an override of `FontFindGaijiMetric_26f8c0` returns a pointer into a port-owned
copy of the 12-byte record table for the active style. The original `D_0044E680` stays
untouched. That one lookup feeds every text path:
- drawing: `FontDrawGaiji_26dd50`, `FontDrawText_26cdc0`, `FontDrawTextGradient_26c6e0`,
  `MesWinDrawGlyphs_271b70`;
- measuring: `FontMeasureString_26daf0`, `FontMeasureWordWidth_26d8d0`,
  `MesWinMeasureText_272b80`, `MesWinMeasureMsg_273470`, `MesItemNameMeasureWidth_274710`,
  `TextCalcGapWidthMaybe_2741c0`;
- wrapping and layout: `FontWrapText_26d5a0`, `MesWinLayoutText_274e70`,
  `MesWinLayoutMsg_273cf0`, `MesWinLayoutItemName_2748f0`.

So text measures, wraps and draws with the same advance, and a style change between two
layouts can't mismatch. A message that was laid out with one width and drawn with another
could still go wrong when the style changes in the middle of a message, if a layout is
cached. So a style change **takes effect on the next message**: the override holds the
active table until the message window closes, or `MesWinLayoutText_274e70` runs again. The
FD3E → FD3F font-type-2 rule must stay in the override. Gamepad styles keep the original
widths, so only `keyboard --wide` ever reflows text.

### The insect-cage exception

`InsectCageButtonHintDraw_388ee0` doesn't use the metric table. It draws L1 and R1 from
`D_0047FC90..9C` ({32,0,32,20}, {64,0,32,20}) and lays out the hint from
`D_0047FC94 + D_0047FC9C` (the two widths). Because every style redraws the original rects,
this hint follows the texture swap without changes, and in `--wide` mode it shows the short
labels. A width-aware version would need an override that reads FD02/FD03 from the active
metric table. That is optional.

### Missing glyphs

The texture has no Start, Select, d-pad, L3/R3 or stick glyphs, and the tag table has no
tags for them. The game names those buttons with symbol tags (`[ar-u]`…, drawn from the
normal font pages through `TextSymbolTagFind_26efe0`) or with words in the message files.
So:

- **Nothing to swap** for them in the gaiji path. If the message files name "START" or
  "SELECT" in words, a text-override pass of the message data maps them per style (Menu /
  View, + / −, Return / Backspace). That needs the message-text dump, which is not done
  yet (CONTROLS-AUDIT.md section 8).
- **Port-authored text** (settings overlay, new hints) can use extension glyphs. Codes
  FD48+ are drawn into the free band. Port-only tags such as `[start]`, `[select]`,
  `[dpad]` and `[ls]` are added by an override of `TextGaijiTagFind_26f060` that checks a
  port table after `D_0044EA00`, with records in the port metric table. Game text never
  contains these tags, so retail behaviour is unchanged.
- **Literal tags.** `(O)`, `(X)`, `(A)` and `(#)` always become icons, because the gaiji
  match runs first, and `(R)` becomes ®. Port text must not use them as words.

## Implementation

Done 2026-10-17 (build tree `build/prompts-i686`; scratch, scripts, runs and screenshots in
`out/prompts/`, game imagery, never committed).

### What changes per style

Only the 8 button rects of `gaiji2` (table above) change; every other pixel keeps its exact
index byte and every palette entry used outside the rects keeps its colour. Widths, text,
layout and game state are unchanged.

| `prompts.style` resolves to | L2 / L1 / R1 / R2 | Circle / Triangle / Square / Cross |
| --- | --- | --- |
| `playstation` (Original, every scripted or headless run) | the original art; **the texture is never written** | the original art |
| `xbox` (also `auto` with an Xbox, Steam or generic pad) | LT LB RB RT on dark key caps | B red, Y yellow, X blue, A green on dark discs |
| `nintendo` (`auto` with a Switch / Joy-Con / GameCube pad) | ZL L R ZR | A X Y B in white (positional: Cross's slot shows B) |
| `keyboard` (`auto` after keyboard/mouse use) | light key caps labelled with the first `key:` binding of `decline`, `camera_turn_left`, `camera_turn_right`, `camera_recentre` | the same for `cancel`, `menu`, `attack`, `confirm`; a mouse icon with the button highlighted for a `mouse:` binding; "-" when unbound |

Default keyboard labels: L2 `1`, L1 `Q`, R1 `E`, R2 `3`, Circle `C`, Triangle `TAB`,
Square `Z`, Cross `SPC`. Rebinding (menu, file, `--set input.bind.*`) redraws the keyboard
glyphs on the next field.

### Setting

| Id | Values (default; Original) | Flags |
| --- | --- | --- |
| `prompts.style` | `auto` "Auto (device in use)", `playstation`, `xbox`, `nintendo`, `keyboard` (auto; playstation) | live; Controls page; not a gameplay option (no longer "planned") |

Resolution is unchanged (INPUT.md "Device type and button prompts"): scripted / headless →
PlayStation; a fixed value wins; `auto` follows the device used last, the previous style
until one is used. For verification only, `rg-game --prompt-style STYLE[@FIELD]`
(repeatable, fields ascending) forces a style from a field on, also in scripted runs.
`RG_PROMPTS_LOG=1` prints a `PROMPTS field=… style=… writes=… captures=…` line per
texture write.

### Code

| File | What |
| --- | --- |
| `src/settings/rg_prompts.[ch]` (new) | Pure C, no SDL, no game state. `rg_gaiji_layout_of` (IM3/TIM2 shape check), `rg_gaiji_build` (the C port of `gaiji.py build`: decode, procedural glyphs with the same stroke font, shapes, colours and 4×4 supersampling, palette quantisation into the slots unused outside the rects, PSMT8 swizzle, CSM1 CLUT), `rg_gaiji_key_label`, and the switch `rg_prompts_step` |
| `src/game/rg_game_main.c` | `prompts_apply()` before every field (next to `aspect_apply`): wanted style, keyboard bindings (re-read when `rg_settings_generation` changes), `rg_prompts_step` on `D_004C3180`; checks once that the ELF's metric records (`D_0044E680`) have the 8 rects the builder redraws, else stays PlayStation; `--prompt-style` |
| `src/host/host_input.c` | `prompts.style` loses `RG_SETF_PLACEHOLDER`, new help text |
| `tests/settings/prompts_tests.c` (new), `tests/settings/CMakeLists.txt` | `rg-prompts-tests` and the `prompts` ctest label; `settings_tests.c`: `prompts.style` is no longer planned (`input.prompt_style`, `settings.menu_flags` now uses `graphics.bloom` as its planned row) |
| `tools/prompts/compare.py` (new) | the C builder against `gaiji.py build` on the real `gaiji2.img`, every style (ctest `prompts.vs_gaiji_py`) |
| `tools/prompts/vram_gaiji.py` (new) | finds `gaiji2` in a GS local-memory dump (`fNNNNN.vram`), decodes it and names the style its rects hold |

No `game/`, override, `tools/ingest.py`, `tools/stages`, `src/gpu` or `src/ps2` file
changed, and no override was needed (`tools/ingest.py --check`: 0 problems).

`rg_prompts_step` per field: an invalid buffer (not loaded yet) is left alone; a buffer
holding neither the captured original nor the image last written means the game loaded the
file again, so it is captured as the new original (current style PlayStation); when the
wanted style (and, for keyboard, the bindings) equals the current one nothing happens;
otherwise the style's pixels + CLUT (`0x10400` bytes at TIM2 + 0x40) are copied in. Images
are built lazily from the captured original (under 50 ms each) and cached per style.

### Revisions to the design above

1. **No override.** The design put the switch in an override of `GaijiGetTex_270510` or a
   per-frame hook. `D_004C3180` is a plain MAIN `.bss` buffer the game only reads through
   texture uploads, so the host rewrites it between fields (no guest code runs then), like
   the widescreen flag. The handle, the name-table entry, TEX0 and every fixed-id texture
   load are untouched.
2. **Upload: verified, no invalidation needed.** The texture's GS area (TBP block 0x2D80,
   CLUT block 0x3F76 at field 2400) is shared with other textures and re-uploaded from EE
   memory whenever the font texture group is loaded again, so the in-place copy reaches
   the GS without touching `TexGroupAllocVram_157e70`'s cache. `vram_gaiji.py` on a dump of
   an Xbox run finds the Xbox atlas in GS memory (0 rect pixels different from
   `gaiji.py`'s), on the PlayStation run the original.
3. **Images are built at run time in C**, not shipped: `rg_gaiji_build` starts from the
   user's own `gaiji2.img` and is pixel-identical to `gaiji.py build` for all three styles
   (`prompts.vs_gaiji_py`: 0 of 65,536 pixels differ, 0 index bytes moved outside the rects,
   headers identical).
4. **Reloads are detected by content.** `FontSystemLoad_3133c0` runs again when the game
   leaves the title (field ~2000 in the golden run): the second load is seen (`captures=2`)
   and the style re-applied before the next field.
5. **Scripted runs keep PlayStation.** The rule stays; `--prompt-style` is the explicit,
   device-independent override used for the screenshots below.
6. **Not done:** the `--wide` keyboard labels (they need an override of
   `FontFindGaijiMetric_26f8c0` and a message screen to test the reflow on; short labels
   fit the original rects), and port-only extension tags (`[start]`, ...; no port text uses
   them yet). Both designs above still stand.

### Verification

Runs: headless, unthrottled, `RG_GPU=hw`, `--preset original`, the golden input
(`tools/trace/goldens/newgame_battle.input.txt`) or `out/prompts/scripts/ext.input.txt`
(the golden plus, after its last pause: unpause, Triangle, move, attack, R1, Triangle; the
golden itself never puts a `gaiji2` button glyph on screen). Scripts and runs in
`out/prompts/scripts`, `out/prompts/runs`.

**Original is unchanged.** "Before" = `out/prompts/base/rg-game.exe`, built in
`build/prompts-i686` before any change; "after" = the final build. Both `--preset original`,
`RG_GS_DUMP_FIELDS` 1500, 7100, 8000, 8290, 12000, 20000, 23000, 23600, 24500:

| Compared | Result |
| --- | --- |
| displayed frame (`fNNNNN_display.png`), all 9 fields | byte-identical |
| local-memory read-out (`fNNNNN_local.png`), all 9 fields | byte-identical |
| GS registers + CLUT (`fNNNNN.regs`), all 9 fields | byte-identical |
| the full 4 MB of GS local memory (`fNNNNN.vram`), all 9 fields | byte-identical |
| the 50 `RG_STATUS_EVERY=500` lines | identical |
| `PROMPTS` writes in the after-run (`RG_PROMPTS_LOG=1`) | none |

(`src/gpu` was being changed by the perf lane between the two builds; the output is
identical regardless.)

**Where prompts appear.** Frame diffs between a PlayStation and an Xbox run (63 fields over
the whole golden run, 64 fields over the first battle, 62 over the title OPTIONS screen):
no difference anywhere in the golden run or on the title / OPTIONS screens. The game data
has the button tags only in a few UI strings (`menu/cmd_static3_en.txt`: "Pick up with
[r1][+](X)!", "(A) Main Menu", "(#) Team Command", "Guard against enemy attacks with
[r1]...", "Throw with (#)!", "(X) Use transporter", the DUALSHOCK-not-connected message,
...); the event dialogue reached by the golden run has none. The battle PAUSE screen's
"Square :Go back to title" is **not** `gaiji2` (different art, unchanged in every style): a
prompt baked into another texture (Risks). With `ext.input.txt`, 25 fields differ: the
battle command hint window (Triangle) and the pick-up message.

**Upload and live switching.** `vram_gaiji.py` on field-2400 dumps finds the texture at TBP
block 0x2D80 / CLUT 0x3F76 and names the style its rects hold: the PlayStation, Xbox,
Nintendo and keyboard runs each hold exactly their atlas (0 rect pixels different from
`gaiji.py`, 0 index bytes changed outside the rects). A scripted run with `--prompt-style
playstation --prompt-style xbox@25600 --prompt-style playstation@25800` shows the
PlayStation glyphs at 24960, Xbox at 25610-25785 (the texture was resident and in use when
the switch happened) and PlayStation again from 25810: the swap reaches the screen on the
next upload, both ways. (The glyphs' brightness in those hint windows differs between
separate runs, also between two PlayStation runs where the texture is never written: a
pulse animation whose phase is not reproducible run to run. The comparison checks the glyph
shapes.)

**Screenshots** (`out/prompts/shots/`, native 512x448):

| File | What |
| --- | --- |
| `01-title-f01500-{playstation,nintendo,keyboard}.png`, `01-title-f01600-{playstation,xbox}.png` | title menu: no `gaiji2` prompts, identical in every style |
| `02-battle-menu-f24960-<style>.png` | battle command hint "(A) Main Menu / (#) Team Command" |
| `03-pickup-message-f25660-<style>.png` | "Pick up with [r1][+](X)!" |
| `04-crop-battle-menu-...`, `05-crop-pickup-...` | the same, cropped x3: PlayStation / Xbox / Nintendo / keyboard side by side |
| `06-live-switch-...`, `07-live-switch-...` | the live-switch run against the fixed-style runs |
| `atlas-vram-f02400-<style>.png`, `atlas-buttons-4styles.png` | the atlas decoded from GS memory, and its button rows x4 for the four styles |
| `atlas-vram-f02400-keyboard-rebound.png` | keyboard with `--set input.bind.confirm=key:Return --set input.bind.attack=mouse:left` (ENT key cap, mouse icon) |

**Tests** (`ctest -L "settings|host|input|prompts"`, 82 tests: all pass except
`gpu.gfx.anisotropic`, which started failing with the perf lane's concurrent `src/gpu`
edits (it passed in this tree before them; nothing here touches it); `gpu.gfx.game_replay`
skipped):

| Test | Checks |
| --- | --- |
| `prompts.layout` | the IM3/TIM2 shape is accepted (offsets); 22 kinds of damage and an empty buffer are rejected |
| `prompts.build` | every style on a synthetic atlas: index bytes outside the rects and every palette entry used there unchanged (checked through an independent swizzle in the test), rects redrawn, 1-6 free slots reassigned, deterministic; PlayStation = the original |
| `prompts.art` | Xbox green A / red B / white LB, Nintendo white letters, keyboard light key caps, mouse bindings draw a red-highlighted mouse |
| `prompts.key_labels` | 25 binding texts to labels (SPC, SHF, arrows, K8, KEN, PRIN, mouse 1-5, unbound "-") |
| `prompts.step` | nothing before the load; PlayStation never writes (100 steps); one write per change; every style pair returns to the original byte for byte; a reload while Xbox is shown and a different file are re-captured; a rebind rebuilds and changes only that glyph; a bad style means PlayStation |
| `prompts.step_control` (`WILL_FAIL`) | a byte changed behind the switch's back must be caught |
| `prompts.vs_gaiji_py` | the C builder against `gaiji.py build` on the real `gaiji2.img`: 0 pixels differ for xbox / nintendo / keyboard (also run by hand with a rebinding .ini: mouse, Return, Left Shift, Keypad 8) |
| `input.prompt_style`, `settings.menu_flags` | updated: `prompts.style` is real (not planned) and has an Original value |

### Known issues

- Prompts baked into other textures (the PAUSE screen's Square, possibly menu `rc/*.pac`
  art and attack-chain marks) stay PlayStation. Each needs its texture found and swapped; a
  texture dump per screen is the next step.
- Words in message text ("START button", "DUALSHOCK(R)2") are not rewritten (needs the
  message-text dump).
- Keyboard key caps are light with dark letters; where the game draws the glyphs dimmed and
  tinted (the battle hint window) they have low contrast. A darker key-cap variant would
  read better there; it must then change in `gaiji.py` too (`prompts.vs_gaiji_py` keeps the
  two identical).
- No `--wide` (full key names) and no port-only extension tags (revision 6).
- Nintendo uses the PS2 positional layout only (Cross's slot shows B).

## Checkpoint (newest first)

- 2026-10-17: done. Code, tests, docs; Original byte-identical at 9 fields (including GS
  memory); screenshots per style in `out/prompts/shots/`.
- 2026-10-17: started (`build/prompts-i686`, configured like `build/render-i686`; baseline
  exe saved before any edit).

## Risks and open items

- **Upload caching** (step 3 above): resolved, the in-place rewrite re-uploads
  ("Implementation", revision 2).
- **Palette quantisation.** Only 5 palette slots are free. Glyph art with many new colours
  (gradients) maps to nearest colours. Keep glyph art to a few flat colours plus
  antialiasing, as the procedural styles do.
- **High-resolution prompts** need a host texture-replacement path, keyed by the texture's
  TBP/CLUT at draw time. The GPU renderer has none (no texture cache to key). That's later
  work (P7 texture packs). The 8-bit 256×256 atlas is the compatible baseline.
- **Baked prompts outside gaiji2** (menu `rc/*.pac`, HUD `*_def_?.res`, attack-chain marks
  from `AttackChainMarkersShow_382c40`) are not covered. At least one exists: the battle
  PAUSE screen's Square ("Implementation", Verification).
- **Nintendo label layout.** With positional bindings Cross's slot shows B, which is
  correct for a Switch pad where B is south. A "labels" mode (A confirms) swaps bindings and
  atlas together and is out of scope here.
