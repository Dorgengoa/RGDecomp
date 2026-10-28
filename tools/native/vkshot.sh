#!/bin/sh
# SPDX-License-Identifier: CC0-1.0
# The window's own back buffer at given fields from power-on (no screen capture: RG_WINDOW_SHOT +
# RG_WINDOW_SHOT_HOST=1 = SDL_RenderReadPixels after the FPS counter, in-process), one windowed run
# per field, then the black share and the counter line's width per shot (history "2026-10-26
# (interp3)": the Vulkan zero-copy "black grabs / short counter" question).
#   vkshot.sh TAG EXE API FIELD...      (API d3d11|vulkan; extra env passes through, e.g. RG_VK_PRESENT=0)
P=../port
tag=$1; exe=$2; api=$3; shift 3
R=$P/out/interp3/vkshot/${tag}_$api
mkdir -p $R
W=$(cd $R && pwd -W)
EW=$(cd $(dirname $exe) && pwd -W)/$(basename $exe)
for f in "$@"; do
  (cd $(dirname $exe) && RG_DATA=${RG_DATA:-data} RG_GPU=hw RG_GPU_API=$api RG_WINDOW_SHOT="$f:$W/f$f.png" RG_WINDOW_SHOT_HOST=1 \
     "$EW" --fields $((f + 30)) --set display.fps_counter=${FPS:-detailed} ${EXTRA} > $R/f$f.log 2>&1)
done
python - "$R" <<'PY'
import sys, glob, os
from PIL import Image
for p in sorted(glob.glob(os.path.join(sys.argv[1], "f*.png"))):
    im = Image.open(p).convert("RGB")
    w, h = im.size
    px = im.load()
    dark = sum(1 for y in range(0, h, 4) for x in range(0, w, 4) if max(px[x, y]) < 8) / ((h // 4) * (w // 4))
    # the counter: yellow text (255, 255, 96) in the top rows; its right-most pixel = the line's width
    xs = [x for y in range(0, 40) for x in range(w) if px[x, y][0] > 200 and px[x, y][1] > 200 and px[x, y][2] < 140]
    print("%s %dx%d black %.1f %% counter text to x=%s" % (os.path.basename(p), w, h, 100 * dark, max(xs) if xs else "none"))
PY
