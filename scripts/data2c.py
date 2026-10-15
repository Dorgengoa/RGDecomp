#!/usr/bin/env python3
"""Generate MAIN data C from annotated listings, with bit-exact local checks.

Inputs default to the current assembly listings. --historical reads the base
listings from Git after their linked replacements have been admitted. Names
are resolved by address against the CURRENT symbol table and config overrides.
Never edit generated C. Put manual choices in config/data2c.json.

This command generates candidates only; it never admits them to the link.
"""
from __future__ import annotations
import argparse
import collections
import hashlib
import json
import math
import re
import struct
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
LABEL = re.compile(r'^\s*(?:glabel|dlabel|alabel)\s+(\w+)')
ROW = re.compile(r'^\s*/\*\s*([\dA-Fa-f]+)\s+([\dA-Fa-f]{8})(?:\s+([\dA-Fa-f]{8}))?\s*\*/\s*(.*)')
SYMBOL = re.compile(r'^\s*(\w+)\s*=\s*(0x[\dA-Fa-f]+)\s*;(.*)')
CTYPE = {'word': 'u32', 'float': 'f32', 'short': 's16', 'byte': 'u8'}
SIZE = {'word': 4, 'float': 4, 'short': 2, 'byte': 1}


def write_generated(path, text):
    # Reproduction checks should not rewrite thousands of identical files.
    content = text.encode('utf-8')
    if not path.exists() or path.read_bytes() != content:
        path.write_bytes(content)


def listing(path, cfg, historical):
    if not historical and (ROOT / path).exists():
        return (ROOT / path).read_text(encoding='utf-8')
    return subprocess.check_output(['git', 'show', cfg['base'] + ':' + path],
                                   cwd=ROOT).decode('utf-8')


def parse(text, main=False):
    """Each label-delimited run, including raw instruction-looking data words."""
    blocks, pending, current = [], [], None
    for line in text.splitlines():
        m = LABEL.match(line)
        if m:
            pending.append(m[1])
            current = None
            continue
        m = ROW.match(line)
        if not m:
            continue
        offset, address, raw, tail = m.groups()
        address = int(address, 16)
        if current is None:
            current = {'address': address, 'labels': pending, 'rows': []}
            pending = []
            blocks.append(current)
        directive = re.match(r'\.(word|float|short|byte)\s+([^/#]+)', tail)
        if directive:
            kind, expression = directive.groups()
            expression = expression.strip()
        elif main and raw:
            kind, expression = 'word', '0x%08X' % int.from_bytes(bytes.fromhex(raw), 'little')
        else:
            raise ValueError('unparsed annotated directive at 0x%08X: %s' % (address, line))
        if raw:
            data = bytes.fromhex(raw)
        elif kind in ('byte', 'short'):
            data = (int(expression, 0) % (1 << (8 * SIZE[kind]))).to_bytes(SIZE[kind], 'little')
        else:
            raise ValueError('missing reference bytes at 0x%08X' % address)
        if len(data) != SIZE[kind]:
            raise ValueError('bad directive width at 0x%08X' % address)
        if current['rows']:
            last = current['rows'][-1]
            if last['address'] + len(bytes.fromhex(last['bytes'])) != address:
                raise ValueError('noncontiguous run at 0x%08X' % address)
        current['rows'].append({'address': address, 'kind': kind,
                                'expression': expression, 'bytes': data.hex()})
    return blocks


def escape(data):
    # Fixed three-digit octal avoids greedy C hex escapes and locale conversion.
    result = ''.join(chr(b) if 32 <= b <= 126 and b not in (34, 63, 92)
                     else '\\%03o' % b for b in data)
    decoded = bytearray()
    i = 0
    while i < len(result):
        if result[i] == '\\':
            decoded.append(int(result[i+1:i+4], 8)); i += 4
        else:
            decoded.append(ord(result[i])); i += 1
    assert bytes(decoded) == data
    return result


def text_run(data):
    return (0 in data and sum(32 <= b <= 126 for b in data) >= 3 and
            all(b == 0 or b in (9, 10, 13) or 32 <= b <= 126 for b in data))


def generate(historical=False, only=None):
    cfg = json.loads((ROOT / 'config/data2c.json').read_text())
    historical = historical or cfg.get('historical_inputs', False)
    listings = {p: listing(p, cfg, historical) for p in
                ('asm/main.s', 'asm/data/main_data.data.s', 'asm/bss/main_bss.s', 'asm/bss/main_overlays.s')}
    main_blocks = parse(listings['asm/main.s'], main=True)
    data_blocks = parse(listings['asm/data/main_data.data.s'])
    # Data labels may have been renamed to descriptive names. Classification
    # is by their historical addresses, never by the new name's spelling.
    historical_main = subprocess.check_output(['git', 'show', cfg['base'] + ':asm/main.s'], cwd=ROOT).decode('utf-8')
    data_addresses = set()
    waiting = False
    for line in historical_main.splitlines():
        label = LABEL.match(line)
        if label:
            waiting = label[1].startswith(('D_', 'jtbl_'))
        elif waiting and (row := ROW.match(line)):
            data_addresses.add(int(row[2], 16))
            waiting = False
    current = {}
    functions = set()
    function_addresses = set()
    for line in (ROOT / 'config/main.symbols.txt').read_text().splitlines():
        m = SYMBOL.match(line)
        if m:
            current[int(m[2], 16)] = m[1]
            if 'type:func' in m[3]:
                functions.add(m[1])
                function_addresses.add(int(m[2], 16))
    symbols = {}
    for block in main_blocks + data_blocks:
        for name in block['labels']:
            symbols.setdefault(block['address'], name)
    symbols.update(current)
    # LCF supplies non-function symbols absent from the assembler listings.
    for line in (ROOT / 'SCUS_974.90.lcf').read_text().splitlines():
        m = SYMBOL.match(line)
        if m and 0x100000 <= int(m[2], 16) < 0x528200:
            symbols.setdefault(int(m[2], 16), m[1])
    for address, name in cfg['renames'].items():
        symbols[int(address, 0)] = name
        if int(address, 0) in function_addresses:
            functions.add(name)
    import data2c_symbols
    extra_entries = data2c_symbols.entries(cfg, current)
    symbols.update(extra_entries)
    functions.update(extra_entries.values())
    external = cfg.get('external_symbols', {})
    functions.update(n for n, item in external.items() if item['kind'] == 'function')
    original_addresses = {}
    for block in main_blocks + data_blocks:
        for name in block['labels']:
            original_addresses[name] = block['address']
    original_addresses.update({n: a for a, n in symbols.items()})
    owned = []
    for line in (ROOT / 'config/crodata.txt').read_text().splitlines():
        fields = line.split('#')[0].split()
        if fields:
            owned.append((int(fields[1], 16), int(fields[1], 16) + int(fields[2], 16)))
    selected = []
    exclusions = []
    for block in main_blocks:
        if (block['address'] not in data_addresses and
                '0x%08X' % block['address'] not in cfg.get('extra_data_blocks', {}) and
                not any(n.startswith(('D_', 'jtbl_')) for n in block['labels'])):
            continue
        # A label-delimited table can overlap several C-owned switch slots.
        rows = [r for r in block['rows'] if not any(a <= r['address'] < b for a, b in owned)]
        excluded = len(block['rows']) - len(rows)
        if excluded:
            exclusions.append({'address': block['address'], 'bytes': excluded * 4,
                               'reason': 'config/crodata.txt owns these bytes'})
        run = []
        for row in rows:
            if run and run[-1]['address'] + 4 != row['address']:
                selected.append({'address': run[0]['address'], 'labels': block['labels'] if run[0]['address'] == block['address'] else [], 'rows': run, 'section': '.rodata'})
                run = []
            run.append(row)
        if run:
            selected.append({'address': run[0]['address'], 'labels': block['labels'] if run[0]['address'] == block['address'] else [], 'rows': run, 'section': '.rodata'})
    for block in data_blocks:
        block['section'] = '.data'
        selected.append(block)
    selected.sort(key=lambda b: b['address'])
    # Separate directive-width runs rather than guessing a packed struct ABI.
    # This also preserves two-byte/one-byte labels at ownership boundaries.
    expanded = []
    for block in selected:
        groups = [list(g) for kind, g in __import__('itertools').groupby(block['rows'], key=lambda r: r['kind'])]
        data = b''.join(bytes.fromhex(r['bytes']) for r in block['rows'])
        # A recognized byte string remains one char array with its padding.
        as_text = text_run(data) and all(r['kind'] in ('byte', 'word') for r in block['rows']) and not any(
            re.match(r'^[A-Za-z_]\w*$', r['expression']) for r in block['rows'])
        if len(groups) == 1 or as_text:
            expanded.append(block)
        else:
            for i, rows in enumerate(groups):
                expanded.append({'address': rows[0]['address'], 'rows': rows,
                    'labels': block['labels'] if i == 0 else [], 'section': block['section'],
                    'fragment_of': block['address']})
    selected = expanded
    unresolved, declarations, definitions, manifest = [], [], [], []
    generated = ROOT / 'src/main_data'
    generated.mkdir(parents=True, exist_ok=True)

    def value(row):
        data = bytes.fromhex(row['bytes'])
        kind, expression, address = row['kind'], row['expression'], row['address']
        override = cfg['overrides'].get('0x%08X' % address)
        if override:
            return override
        if kind == 'float':
            val = struct.unpack('<f', data)[0]
            if not math.isfinite(val):
                raise ValueError('nonfinite f32 requires configured bit representation at 0x%08X' % address)
            literal = format(val, '.9g')
            if '.' not in literal and 'e' not in literal:
                literal += '.0'
            assert struct.pack('<f', float(literal)) == data
            unresolved.append('0x%08X f32 %sf (bits 0x%08X)' % (address, literal, int.from_bytes(data, 'little')))
            return literal + 'f'
        integer = int.from_bytes(data, 'little')
        if kind == 'word':
            external_name = cfg.get('external_pointer_slots', {}).get('0x%08X' % address)
            if external_name:
                if integer != int(external[external_name]['address'], 0):
                    raise ValueError('external pointer value mismatch at 0x%08X' % address)
                return '(u32)&' + external_name
            pointer = cfg.get('pointer_slots', {}).get('0x%08X' % address)
            if pointer:
                base, offset = int(pointer['base'], 0), pointer['offset']
                owners = [b for b in all_selected if b['address'] == base]
                if len(owners) != 1 or base + offset != integer or not 0 <= offset < sum(len(bytes.fromhex(r['bytes'])) for r in owners[0]['rows']):
                    raise ValueError('invalid configured data pointer at 0x%08X' % address)
                return '(u32)((u8*)&%s + 0x%Xu)' % (owners[0]['name'], offset)
            target = symbols.get(integer)
            symbolic = re.match(r'^\w+$', expression) and not expression.startswith('0x')
            if symbolic:
                target_addr = original_addresses.get(expression)
                if target_addr is not None:
                    if target_addr != integer:
                        raise ValueError('symbol/reference byte mismatch: ' + expression)
                    target = symbols.get(target_addr, expression)
                else:
                    target = expression
            if target and (symbolic or 0x100000 <= integer < 0x528200):
                return '(u32)&' + target
            unresolved.append('0x%08X word 0x%08X%s' % (address, integer,
                ' (image address without exact symbol)' if 0x100000 <= integer < 0x528200 else ''))
            return '0x%08Xu' % integer
        if kind == 'short':
            integer = integer if integer < 0x8000 else integer - 0x10000
        unresolved.append('0x%08X %s %s' % (address, kind, integer))
        return str(integer)

    for block in selected:
        address, rows = block['address'], block['rows']
        name = symbols.get(address, block['labels'][0] if block['labels'] else 'data2c_gap_%08X' % address)
        if 'fragment_of' in block and not block['labels']:
            name = cfg['renames'].get('0x%08X' % address, 'data2c_fragment_%08X' % address)
        # Definition labels are preferred over names of interleaved functions.
        if block['labels']:
            name = cfg['renames'].get('0x%08X' % address, block['labels'][0])
            if address in current and current[address] not in functions:
                name = current[address]
        symbols[address] = name
        block['name'] = name
    all_selected = list(selected)
    all_defined = {b['name'] for b in all_selected}
    if only:
        selected = [b for b in selected if only[0] <= b['address'] < only[1]]
    # Resolve pointers AFTER all generated definition names have been settled.
    for block in selected:
        address, rows, name = block['address'], block['rows'], block['name']
        data = b''.join(bytes.fromhex(r['bytes']) for r in rows)
        section = cfg['sections'].get('0x%08X' % address, block['section'])
        const = 'const ' if section == '.rodata' else ''
        typename = 'data2c_type_%08X' % address
        if text_run(data) and all(r['kind'] in ('byte', 'word') for r in rows) and not any(
                re.match(r'^[A-Za-z_]\w*$', r['expression']) for r in rows):
            declaration = '%schar %s[%d]' % (const, name, len(data))
            definition = declaration + ' = "' + escape(data) + '";'
            text_kind = 'text'
        else:
            kinds = {r['kind'] for r in rows}
            if len(kinds) != 1:
                raise ValueError('mixed-width non-text run was not split')
            kind = rows[0]['kind']
            declaration = '%s%s %s[%d]' % (const, CTYPE[kind], name, len(rows))
            definition = declaration + ' = {\n    ' + ', '.join(value(r) for r in rows) + '\n};'
            text_kind = 'typed directives'
            if re.search(rb'[ -~]{4,}', data):
                unresolved.append('0x%08X text-looking run retained as typed bytes/words: mixed non-text bytes' % address)
        declarations.append('extern ' + declaration + ';')
        definition += '\ntypedef char data2c_sizecheck_%08X[(sizeof(%s) == %d) ? 1 : -1];' % (address, name, len(data))
        filename = 'data2c_%08X.c' % address
        # Per-object files are initially deliberate: compiler ordering must be
        # measured before grouping 4-16 KB windows (cfg.window is the target).
        definitions.append((filename, definition))
        manifest.append({'name': name, 'address': address, 'size': len(data),
                         'last_address': rows[-1]['address'],
                         'section': section, 'source': 'src/main_data/' + filename,
                         'object': filename[:-2] + '.o', 'kind': text_kind,
                         'sha256': hashlib.sha256(data).hexdigest(),
                         'labels': block['labels']})
    references = set(re.findall(r'&([A-Za-z_]\w*)', '\n'.join(d for _, d in definitions)))
    defined = {b['name'] for b in selected}
    for name in sorted(references - defined):
        if name in functions or (name not in all_defined and name.startswith(('FUN_', 'func_'))):
            declarations.append('extern void %s(void);' % name)
        else:
            declarations.append('extern u8 %s[];' % name)
    header = ('/* Generated by scripts/data2c.py; edit config/data2c.json. */\n'
              '#ifndef DATA2C_GENERATED_H\n#define DATA2C_GENERATED_H\n'
              '#include "types.h"\n' + '\n'.join(declarations) + '\n#endif\n')
    write_generated(generated / 'generated.h', header)
    names_by_file = {Path(o['source']).name: o['name'] for o in manifest}
    for filename, definition in definitions:
        local_declarations = []
        own = names_by_file[filename]
        for name in sorted(set(re.findall(r'&([A-Za-z_]\w*)', definition)) - {own}):
            local_declarations.append('extern void %s(void);' % name if name in functions or (name not in all_defined and name.startswith(('FUN_', 'func_'))) else 'extern u8 %s[];' % name)
        write_generated(generated / filename, '/* Generated: do not edit. */\n#include "types.h"\n' + '\n'.join(local_declarations) + '\n' + definition + '\n')
    if not only:
        bss = listings['asm/bss/main_bss.s']
        match = re.search(r'\.space\s+(0x[0-9a-fA-F]+)', bss)
        if not match or int(match[1], 16) != 0x68e00:
            raise ValueError('unexpected MAIN bss reservation')
        write_generated(generated / 'data2c_bss.c', '/* Generated fallback: real NOBITS definition. */\n#include "types.h"\nu8 data2c_main_bss[0x68E00];\n')
        manifest.append({'name': 'data2c_main_bss', 'address': 0x481080, 'size': 0x68e00,
                         'section': '.bss', 'source': 'src/main_data/data2c_bss.c', 'object': 'data2c_bss.o'})
        # These are MAIN's empty LOAD reservations, not overlay data contents.
        reservations = re.findall(r'\.section\s+(\.ov(\d)bss)[^\n]*\n\.space\s+(0x[0-9A-Fa-f]+)', listings['asm/bss/main_overlays.s'])
        if len(reservations) != 7:
            raise ValueError('expected all seven MAIN overlay reservations')
        for section, number, size in reservations:
            size = int(size, 16)
            filename = 'data2c_ov%s_bss.c' % number
            name = 'data2c_overlay_reserve_' + number
            write_generated(generated / filename, '/* Generated MAIN reservation; overlay contents unchanged. */\n#include "types.h"\nu8 %s[0x%X];\n' % (name, size))
            manifest.append({'name': name, 'address': 0x4e9e80, 'size': size,
                'section': section, 'reservation': True, 'source': 'src/main_data/' + filename,
                'object': filename[:-2] + '.o'})
    if not only:
        expected_files = {Path(o['source']).name for o in manifest}
        for file in generated.glob('data2c_*.c'):
            if file.name not in expected_files and file.read_text().startswith('/* Generated'):
                file.unlink()
    out = ROOT / 'handoff'
    out.mkdir(exist_ok=True)
    (out / 'data2c-manifest.json').write_text(json.dumps({'schema': 1, 'objects': manifest, 'excluded': exclusions,
        'inputs': {p: hashlib.sha256(t.encode()).hexdigest() for p, t in listings.items()}}, indent=2) + '\n', newline='\n')
    (out / 'unresolved.txt').write_text('Ordering: one TU per homogeneous directive-width run; mixed labels split into adjacent address-ordered fragments. MAIN overlay reservations intentionally share an address in alternative LOAD segments. Compiler probes are recorded separately; linked admission requires full byte proof.\n' + '\n'.join(unresolved) + '\n', newline='\n')
    print('Generated %d candidate objects; %d C-owned table exclusions; %d unresolved/numeric entries.' % (len(manifest), len(exclusions), len(unresolved)))
    print('Local float and string round-trip checks passed. Compiler and full-link proof still required.')


if __name__ == '__main__':
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--historical', action='store_true')
    ap.add_argument('--range', nargs=2, type=lambda x: int(x, 0), metavar=('START', 'END'))
    args = ap.parse_args()
    generate(args.historical, args.range)
