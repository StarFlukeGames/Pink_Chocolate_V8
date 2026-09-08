#!/usr/bin/env python3
# Copyright (c) StarFluke Fallen World. All Rights Reserved.
# SIBHDS Spreadsheet-to-INI Pre-Build Compiler & Code Generator

import os
import sys
import csv
import configparser

def compile_catalog(csv_path, ini_path):
    if not os.path.exists(csv_path):
        print(f"[ERROR] Source CSV '{csv_path}' is missing.", file=sys.stderr)
        sys.exit(1)
        
    config = configparser.ConfigParser()
    print(f"[SIBHDS] Beginning compilation: '{csv_path}' -> '{ini_path}'...")
    
    with open(csv_path, mode='r', encoding='utf-8') as f:
        reader = csv.reader(f)
        rows = list(reader)
        
    if len(rows) < 3:
        print("[ERROR] CSV must contain at least 3 rows of metadata headers.", file=sys.stderr)
        sys.exit(1)
        
    # Extract headers
    raw_field_names = rows[0]
    raw_data_types = rows[1]
    raw_directives = rows[2]
    data_rows = rows[3:]
    
    # Map valid (non-hidden) columns
    active_columns = []
    key_column_idx = -1
    
    for idx, name in enumerate(raw_field_names):
        if name.startswith('#') or name.startswith('_') or "Hide" in raw_directives[idx]:
            continue
        active_columns.append(idx)
        if "Key" in raw_directives[idx]:
            key_column_idx = idx
            
    if key_column_idx == -1:
        print("[ERROR] CSV must define a column with the 'Key' directive in Row 3.", file=sys.stderr)
        sys.exit(1)
        
    for row_idx, row in enumerate(data_rows, start=4):
        # Skip empty or commented rows
        if not row or not row[0] or row[0].startswith('#') or row[0].startswith('//'):
            continue
            
        key_val = row[key_column_idx]
        section_name = key_val
        
        if not config.has_section(section_name):
            config.add_section(section_name)
            
        for col_idx in active_columns:
            if col_idx == key_column_idx:
                continue
            field_name = raw_field_names[col_idx]
            cell_value = row[col_idx]
            
            # Apply defaults if empty
            if not cell_value:
                directive = raw_directives[col_idx]
                if "Default=" in directive:
                    cell_value = directive.split("Default=")[1]
                    
            config.set(section_name, field_name, cell_value)
            
    os.makedirs(os.path.dirname(ini_path), exist_ok=True)
    with open(ini_path, mode='w', encoding='utf-8') as f:
        config.write(f)
    print(f"[SIBHDS] Compilation completed successfully. Target written to: '{ini_path}'")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: compile_catalog.py <src.csv> <target.ini>")
        sys.exit(1)
    compile_catalog(sys.argv[1], sys.argv[2])