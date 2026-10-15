# Naming

## Format

Every function is named `<Name>_<address>`, where the address is the function's address in
lowercase hex without leading zeros beyond six digits:

```
EffHdlRelease_1a3040                main executable, address 0x001A3040
normal_FieldHudPanelsFadeIn_4f6f00  NORMAL.BIN overlay, address 0x004F6F00
```

The address suffix is not decoration: the linkers derive a cross-part reference's address
from it, so it must stay. Overlay functions keep their image prefix (`title_`,
`insmenu_`, `normal_`, `factory_`, `insect_`).

Functions that are part of the Sony SDK or the C library keep their retail names where
those are known (`memcpy`, `sceSdTransToIOP`, ...).

## Confidence

Names follow a ladder:

| Form | Meaning |
| --- | --- |
| `CharaGetHeightAboveGround_238380` | the role is established from the code, its callers and data |
| `CharaGetIconRecMaybe_3ae3e0` | the role was read from the body, but not fully proven |
| `CharaEvObjContactFlag4Related_214860` | only the subsystem is known |

`Maybe` and `Related` names are the final names for this release; they mark where the
evidence ran out, not unfinished work.

## Twins

Functions that are byte-for-byte copies of each other, or the same command in two script
interpreters, share a base name at their two addresses (for example the event-script and
system-script versions of an event command).

## Thunks

A jump thunk is named after its target, with the target's address:
`CharaClearThunk_3af980` jumps to `CharaClear_3af980`. A second thunk to the same target
is `<Target>Thunk2_<address>` (`CharaClearThunk2_3af980`).
