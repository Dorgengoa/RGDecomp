# SPDX-License-Identifier: CC0-1.0
"""Write tools/trace/input.py's table blob for a script: the exact bytes the
harness PINE-writes at TABLE (u32 count, then count u16 words, little endian).
Usage: input_py_blob.py <tools/trace dir> <script> <out.bin>"""
import struct
import sys

sys.path.insert(0, sys.argv[1])
import input as I  # noqa: E402  (tools/trace/input.py)

words = I.build_table(I.parse_script(sys.argv[2]))
with open(sys.argv[3], "wb") as f:
    f.write(struct.pack("<I%dH" % len(words), len(words), *words))
