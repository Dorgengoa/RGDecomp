# Rogue Galaxy PC port: quick start (Linux)

## You need

- A 64-bit x86 Linux desktop (glibc 2.38 or newer, for example Ubuntu 24.04, Fedora 39,
  Debian 13 or later) with a Vulkan driver, under X11 or Wayland.
- About 10 GB of free disk space.
- Your own disc image of **Rogue Galaxy (USA)**, SCUS-97490, as an `.iso` file. Other
  regions and versions don't work yet.

## Set up (once)

1. Unzip `RogueGalaxyPC-1112a-linux-x86_64.zip` to a folder you can write to, for example
   `~/Games/RogueGalaxyPC`.
2. Copy your `.iso` into that folder, next to `rg-setup`.
3. In a terminal in that folder run `./rg-setup` (or `./rg-setup /path/to/image.iso`). It
   checks the disc, unpacks it into a `data` folder and builds `rg-game`. This takes a few
   minutes. When it says "All done", you are ready.
4. You can delete the `.iso` now if you like. Don't delete `data`.

If `./rg-setup` says "Permission denied", run `chmod +x rg-setup` first (some unzip tools
drop the execute bit).

## Play

Run `./rg-game`.

- **Settings:** press **F1**, or hold **Back + Start** on a gamepad for one second.
- **Fullscreen:** F11 or Alt+Enter.
- **Quit:** Esc (with the settings menu closed), or close the window.
- Saves go in the `saves` folder and settings in `settings.ini`, both next to the game.
- The renderer is Vulkan. Sound goes through PipeWire, PulseAudio or ALSA.

## Default controls

| PS2 button | Keyboard | Gamepad |
| --- | --- | --- |
| Left stick (move) | W A S D (hold Left Shift to walk) | Left stick |
| Right stick (camera) | I J K L | Right stick |
| D-pad | Arrow keys | D-pad |
| Cross (confirm, talk, sword) | Space or X | A / Cross |
| Circle (cancel, jump) | C | B / Circle |
| Square (gun) | Z | X / Square |
| Triangle (menu, battle commands) | Tab | Y / Triangle |
| L1 / R1 | Q / E | Shoulder buttons |
| L2 / R2 | 1 / 3 | Triggers |
| L3 / R3 | V / B | Stick clicks |
| Start (pause, skip) | Enter | Start / Menu |
| Select (map) | Backspace | Back / View |

Every control can be changed in the settings menu (Controls page).

## If something goes wrong

- **"No .iso file found"**: put the `.iso` next to `rg-setup`, or give its path:
  `./rg-setup /path/to/image.iso`.
- **"wrong image"**: the disc is a different region or version, or the image is damaged.
  Setup says which disc it found.
- **Setup stopped halfway**: run it again; it starts over cleanly.
- **No window / Vulkan error**: install your distribution's Vulkan driver (Mesa or the GPU
  vendor's) and check that `vulkaninfo` lists a device.
- **The game crashed**: start it from a terminal (`./rg-game`) and include the terminal
  output when you report the problem.

More about the port, its features and known issues: `README.md`.
