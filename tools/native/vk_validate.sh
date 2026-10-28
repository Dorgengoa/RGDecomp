#!/bin/sh
# SPDX-License-Identifier: CC0-1.0
# The Vulkan backend under the Khronos validation layer (docs/NATIVE-VULKAN.md "Validation"): the
# golden route from power-on (headless, RG_GPU_API=vulkan, RG_VK_VALIDATE=1) with the 32-bit layer
# tools/native/build_vvl_x86.ps1 builds, then the distinct messages (VUID / message id, count,
# first text).  WINDOWED=1: not headless (the
# window's renderer on the backend's device, zero-copy presents), for the presentation path.
# The loader ignores VK_ADD_LAYER_PATH in an elevated process (registry only), so the backend loads
# the layer library itself as well ($RG_VK_LAYER_DLL, nr_vulkan.cpp "vkl").
#   vk_validate.sh EXE TAG [FIELDS] [EXTRA rg-game ARGS...]
#   VVL_DIR (default ../tools/vvl-x86/bin): the directory holding VkLayer_khronos_validation.json
# Output: out/nrender/runs/vkval_TAG/run.log, vkval_TAG.txt (summary).
P=../port
exe=$1; tag=$2; fields=${3:-9000}; shift 3 2>/dev/null || shift $#
R=$P/out/nrender/runs/vkval_$tag
rm -rf "$R"; mkdir -p "$R/saves"
W=$(cd "$R" && pwd -W)
vvl=${VVL_DIR:-../tools/vvl-x86/bin}
hl=--headless; [ -n "$WINDOWED" ] && hl=""
$P/tools/native/game_slot.sh
RG_VK_LAYER_DLL="$vvl/VkLayer_khronos_validation.dll" VK_ADD_LAYER_PATH="$vvl" RG_VK_VALIDATE=1 RG_GPU_API=vulkan RG_DATA='data' RG_GPU=hw RG_RENDER=native \
  "$exe" $hl --fields "$fields" --saves "$W/saves" \
  --input tools/trace/goldens/newgame_save2.input.txt "$@" > "$R/run.log" 2>&1
echo "rc=$?" >> "$R/run.log"
python - "$R/run.log" "$P/out/nrender/runs/vkval_$tag.txt" <<'EOF'
import re, sys
log = open(sys.argv[1], errors='replace').read().splitlines()
out = []
dev = [l for l in log if l.startswith('rg gpu:') or 'validation' in l.lower() and 'rg vulkan' in l]
out += dev[:3]
msgs = [l[len('vk validation: '):] for l in log if l.startswith('vk validation: ')]
groups = {}
for m in msgs:
    k = re.match(r'(\w+) \[ (\S+) \]', m)
    key = (k.group(1) + ' ' + k.group(2)) if k else m[:80]
    groups.setdefault(key, []).append(m)
out.append('%d validation messages (callback cap 400), %d distinct' % (len(msgs), len(groups)))
for k, v in sorted(groups.items(), key=lambda kv: -len(kv[1])):
    out.append('  %5d  %s' % (len(v), k))
    out.append('         %s' % v[0][:600])
out += [l for l in log if 'run_hash' in l][-1:]
out += [l for l in log if l.startswith('rc=')][-1:]
open(sys.argv[2], 'w').write('\n'.join(out) + '\n')
print('\n'.join(out))
EOF
