# Third-party notices

The port's own code is CC0 1.0 (see `LICENSE`). The components below are compiled into
`rg-game.exe` and keep their own licenses; their full texts are in
`THIRD_PARTY_LICENSES.txt`. No GPL-licensed code is used.

| Component | Version | License | Used for |
| --- | --- | --- | --- |
| SDL3 (Simple DirectMedia Layer) | 3.4.18 | zlib, Copyright (C) 1997-2026 Sam Lantinga | Window, input, gamepads, audio output |
| Vulkan-Headers (Khronos) | vulkan-sdk-1.4.363.0 | Apache-2.0 OR MIT, Copyright 2015-2026 The Khronos Group Inc. | Vulkan API declarations |
| volk | vulkan-sdk-1.4.363.0 | MIT, Copyright (c) 2018-2026 Arseny Kapoulkine | Loading the Vulkan driver |
| Vulkan Memory Allocator (AMD GPUOpen) | v3.4.0 | MIT, Copyright (c) 2017-2026 Advanced Micro Devices, Inc. | Vulkan memory management |

`Setup.exe` uses only the port's own code. Both programs link the Microsoft C runtime
statically.
