# SPDX-License-Identifier: CC0-1.0
"""Exact-text source edits that keep a file's line endings (CRLF or LF).

    from srcedit import edit
    edit("src/gpu/gpu_core.cpp", [(old, new), ...])   # each old must occur exactly once

Write edit scripts as files (not shell heredocs: some shells fold backslashes) and run them
with python from the port root.  Used by the renderer lane (docs/NATIVE-RENDER.md "Tools").
"""
import sys


def edit(path, pairs, count=1):
    s = open(path, encoding="utf-8", newline="").read()
    crlf = "\r\n" in s
    for old, new in pairs:
        if crlf:
            old = old.replace("\r\n", "\n").replace("\n", "\r\n")
            new = new.replace("\r\n", "\n").replace("\n", "\r\n")
        n = s.count(old)
        if n != count:
            sys.exit("srcedit: %s: %d matches (want %d) for:\n%s" % (path, n, count, old[:200]))
        s = s.replace(old, new)
    open(path, "w", encoding="utf-8", newline="").write(s)
