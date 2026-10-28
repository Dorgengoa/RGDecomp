#!/usr/bin/env python3
"""Settings census (docs/P6-STATUS.md): dump every registered setting with
key / type / default / original / flags / menu visibility, plus the source
lines that READ it outside the registration tables (a setting nobody reads
takes no effect, whatever its flags say).

Static: parses the designated-initialiser tables in
  src/settings/rg_settings_core.c   (k_core)
  src/host/host_input.c             (tune[] + one input.bind.<action> per k_act row)
No build needed.  Usage:
  python tools/settings_census.py                 # TSV to stdout
  python tools/settings_census.py -o census/settings.tsv
  python tools/settings_census.py --summary       # counts only
"""
import argparse, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(ROOT, "src")
TABLES = ["src/settings/rg_settings_core.c", "src/host/host_input.c"]
FLAG_MACROS = {"ORIG": "ORIG", "PH": "PLACEHOLDER", "DISP": "DISPLAY", "RS": "RESTART",
               "GP": "GAMEPLAY"}


def rel(p):
    return os.path.relpath(p, ROOT).replace("\\", "/")


def enum_arrays(text):
    out = {}
    for m in re.finditer(r'static const char \*const (\w+)\[\]\s*=\s*\{([^}]*)\}', text):
        out[m.group(1)] = re.findall(r'"([^"]*)"', m.group(2))
    return out


def parse_table(path):
    text = open(os.path.join(ROOT, path), encoding="utf-8").read()
    enums = enum_arrays(text)
    rows = []
    starts = [m for m in re.finditer(r'\{\s*\.id\s*=\s*"([^"]+)"', text)]
    for i, m in enumerate(starts):
        end = starts[i + 1].start() if i + 1 < len(starts) else len(text)
        body = text[m.start():end]
        # cut at the closing brace of this initialiser
        depth, j = 0, 0
        for j, ch in enumerate(body):
            if ch == "{": depth += 1
            elif ch == "}":
                depth -= 1
                if depth == 0: break
        body = body[:j + 1]
        line = text.count("\n", 0, m.start()) + 1

        def field(name):
            f = re.search(r'\.' + name + r'\s*=\s*("(?:[^"\\]|\\.)*"(?:\s*"(?:[^"\\]|\\.)*")*|[^,}]+)', body)
            return f.group(1).strip() if f else ""

        sid = m.group(1)
        typ = field("type").replace("RG_SET_", "")
        flags_raw = field("flags")
        flags = set()
        for tok in re.findall(r'\w+', flags_raw):
            if tok in FLAG_MACROS: flags.add(FLAG_MACROS[tok])
            elif tok.startswith("RG_SETF_"):
                t = tok[len("RG_SETF_"):]
                flags.add("ORIG" if t == "HAS_ORIGINAL" else t)
        en = field("enum_names")
        names = enums.get(en, [])
        if typ in ("ENUM",):
            def ename(v):
                try: return names[int(v)]
                except Exception: return v
            d = ename(field("def_i") or "0")
            o = ename(field("orig_i")) if "ORIG" in flags else ""
        elif typ == "FLOAT":
            d = field("def_f") or "0"; o = field("orig_f") if "ORIG" in flags else ""
        elif typ in ("STRING", "BINDING"):
            d = field("def_s").strip('"')
            o = field("orig_s").strip('"') if "ORIG" in flags else ""
        elif typ == "BOOL":
            d = {"0": "false", "": "false"}.get(field("def_i"), "true")
            o = ({"0": "false"}.get(field("orig_i") or "0", "true")) if "ORIG" in flags else ""
        else:
            d = field("def_i") or "0"; o = field("orig_i") if "ORIG" in flags else ""
        cat = field("category").strip('"') or sid.split(".")[0]
        label = re.sub(r'"\s*"', "", field("label")).strip('"')
        rows.append(dict(id=sid, type=typ, category=cat, default=d, original=o,
                         flags=",".join(sorted(flags)), values="|".join(names),
                         label=label, src="%s:%d" % (path, line)))
    if path.endswith("host_input.c"):
        km = re.search(r'k_act\[RG_ACT_COUNT\]\s*=\s*\{(.*?)\n\};', text, re.S)
        for am in re.finditer(r'\{\s*"(\w+)",\s*"([^"]*)",\s*([^}]+)\}', km.group(1)):
            line = text.count("\n", 0, km.start(1) + am.start()) + 1
            ui = am.group(3).strip() == "-1" and am.group(1) != "walk"
            rows.append(dict(id="input.bind." + am.group(1), type="BINDING",
                             category="controls_ui" if ui else "controls",
                             default="(rg_actions_default)", original="", flags="",
                             values="", label=am.group(2), src="%s:%d" % (path, line)))
    return rows


def consumers(ids):
    """Source lines (outside the def tables' own initialisers) quoting each id."""
    hits = {i: [] for i in ids}
    pat = re.compile(r'"((?:display|graphics|audio|gameplay|system|input|prompts)\.[a-z0-9_.]+)"')
    for dp, _, fs in os.walk(SRC):
        for f in fs:
            if not f.endswith((".c", ".h", ".cpp")): continue
            p = os.path.join(dp, f)
            try: lines = open(p, encoding="utf-8", errors="replace").read().split("\n")
            except OSError: continue
            for n, ln in enumerate(lines, 1):
                if ".id = " in ln: continue
                for m in pat.finditer(ln):
                    if m.group(1) in hits:
                        hits[m.group(1)].append("%s:%d" % (rel(p), n))
    # bindings are read generically (rg_actions_from_settings builds the id)
    for i in ids:
        if i.startswith("input.bind.") and not hits[i]:
            hits[i].append("src/host/host_input.c:rg_actions_from_settings (generic)")
    return hits


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("-o", "--out")
    ap.add_argument("--summary", action="store_true")
    a = ap.parse_args()
    rows = []
    for t in TABLES: rows += parse_table(t)
    hits = consumers([r["id"] for r in rows])
    cols = ["id", "type", "category", "default", "original", "flags", "menu", "readers", "reader_sites",
            "values", "label", "src"]
    out = ["\t".join(cols)]
    for r in rows:
        fl = r["flags"].split(",")
        r["menu"] = "no" if "HIDDEN" in fl else "yes"
        r["readers"] = str(len(hits[r["id"]]))
        r["reader_sites"] = " ".join(hits[r["id"]][:6]) + (" ..." if len(hits[r["id"]]) > 6 else "")
        out.append("\t".join(r[c].replace("\t", " ") for c in cols))
    if a.summary or not a.out:
        ph = [r["id"] for r in rows if "PLACEHOLDER" in r["flags"]]
        dead = [r["id"] for r in rows if r["readers"] == "0" and "PLACEHOLDER" not in r["flags"]]
        print("settings: %d (bindings %d); placeholder %d; hidden %d; gameplay %d" % (
            len(rows), sum(r["type"] == "BINDING" for r in rows), len(ph),
            sum(r["menu"] == "no" for r in rows), sum("GAMEPLAY" in r["flags"] for r in rows)),
            file=sys.stderr)
        print("placeholder: " + " ".join(ph), file=sys.stderr)
        print("non-placeholder with no reader: " + (" ".join(dead) or "(none)"), file=sys.stderr)
    if a.out:
        os.makedirs(os.path.dirname(os.path.abspath(a.out)), exist_ok=True)
        open(a.out, "w", encoding="utf-8", newline="\n").write("\n".join(out) + "\n")
        print("wrote %s (%d rows)" % (a.out, len(rows)), file=sys.stderr)
    elif not a.summary:
        sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
