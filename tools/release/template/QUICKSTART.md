# Rogue Galaxy PC port: quick start

## You need

- Windows 10 or 11 (64-bit) and a graphics card with Direct3D 11 or Vulkan.
- About 10 GB of free disk space.
- Your own disc image of **Rogue Galaxy (USA)**, SCUS-97490, as an `.iso` file. Other
  regions and versions don't work yet.

## Set up (once)

1. Unzip `RogueGalaxyPC-@TAG@-win32.zip` to a folder you can write to, for example
   `Documents\RogueGalaxyPC`. Don't use `Program Files`.
2. Copy your `.iso` into that folder, next to `Setup.exe`.
3. Double-click `Setup.exe`. It checks the disc, unpacks it into a `data` folder and
   builds `rg-game.exe`. This takes a few minutes. When it says "All done", press Enter.
4. You can delete the `.iso` now if you like. Don't delete `data`.

If Windows shows "Windows protected your PC", choose **More info**, then **Run anyway**
(the files aren't signed).

## Play

Double-click `rg-game.exe`.

- **Settings:** press **F1**, or hold **Back + Start** on a gamepad for one second.
- **Fullscreen:** F11 or Alt+Enter.
- **Quit:** Esc (with the settings menu closed), or close the window.
- Saves go in the `saves` folder and settings in `settings.ini`, both next to the game.

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

- **"No .iso file found"**: put the `.iso` next to `Setup.exe`, or drag it onto
  `Setup.exe`.
- **"wrong image"**: the disc is a different region or version, or the image is damaged.
  Setup says which disc it found.
- **Setup stopped halfway**: run it again; it starts over cleanly.
- **The game crashed**: `rg-game-crash.txt` and `rg-game-crash.dmp` appear next to
  `rg-game.exe`. Please include them when you report the problem.

More about the port, its features and known issues: `README.md`.
