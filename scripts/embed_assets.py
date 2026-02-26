#!/usr/bin/env python3
import os
import sys

def file_to_c_array_fast(input_file, var_name):
    """Ultra-fast file to C array conversion"""
    try:
        with open(input_file, 'rb') as f:
            data = f.read()
        size = len(data)
        print(f"  ✅ {os.path.basename(input_file)} ({size/1024:.0f} KB)")
    except Exception as e:
        print(f"  ❌ Error: {e}")
        return None, None
    
    # Generate C array (minimal formatting)
    c_array = f"// {os.path.basename(input_file)}\n"
    c_array += f"unsigned char {var_name}[] = {{"
    bytes_str = ','.join(f'0x{b:02x}' for b in data)
    c_array += bytes_str
    c_array += "};\n"
    return c_array, size

def main():
    print("=" * 50)
    print("PACMAN ASSET EMBEDDER (TURBO MODE)")
    print("=" * 50)
    
    current_dir = os.getcwd()
    print(f"📁 Working directory: {current_dir}")
    
    if not os.path.exists("assets"):
        print("❌ ERROR: 'assets' folder not found!")
        sys.exit(1)
    
    # Collect all asset files
    assets = []
    extensions = ('.png', '.ttf', '.mp3', '.txt', '.ico')
    
    print("\n🔍 Scanning for assets...")
    for root, dirs, files in os.walk("assets"):
        for file in files:
            if file.lower().endswith(extensions):
                full_path = os.path.join(root, file)
                # Create valid C variable name
                var_name = file.replace('.', '_').replace('-', '_').lower()
                var_name = ''.join(c for c in var_name if c.isalnum() or c == '_')
                assets.append((full_path, var_name))
    
    total_files = len(assets)
    total_size = sum(os.path.getsize(f[0]) for f in assets) / (1024*1024)
    
    print(f"\n📊 FOUND: {total_files} files | Total size: {total_size:.1f} MB")
    
    music_files = [f for f in assets if f[0].endswith('.mp3')]
    if music_files:
        music_size = sum(os.path.getsize(f[0]) for f in music_files) / (1024*1024)
        print(f"🎵 Music: {len(music_files)} files | {music_size:.1f} MB")
    
    print("\n⚡ GENERATING EMBEDDED ASSETS...")
    
    c_path = "src/embedded_assets.c"
    h_path = "src/embedded_assets.h"
    
    with open(c_path, "w", encoding='utf-8') as c_file:
        c_file.write('#include "embedded_assets.h"\n\n')
        
        with open(h_path, "w", encoding='utf-8') as h_file:
            h_file.write("#ifndef EMBEDDED_ASSETS_H\n")
            h_file.write("#define EMBEDDED_ASSETS_H\n\n")
            
            for i, (file_path, var_name) in enumerate(assets):
                # Progress indicator
                percent = (i + 1) * 100 // total_files
                bar = '█' * (percent // 5) + '░' * (20 - (percent // 5))
                print(f"\r[{bar}] {percent}% - {os.path.basename(file_path):30}", end='')
                
                c_array, size = file_to_c_array_fast(file_path, var_name)
                if c_array:
                    # Write array
                    c_file.write(c_array)
                    # Write size definition
                    c_file.write(f"unsigned int {var_name}_size = {size};\n\n")
                    
                    # Write declarations to header
                    h_file.write(f"extern unsigned char {var_name}[];\n")
                    h_file.write(f"extern unsigned int {var_name}_size;\n\n")
            
            h_file.write("#endif // EMBEDDED_ASSETS_H\n")
    
    print(f"\n\n{'=' * 50}")
    print(f"✅ SUCCESS! Embedded {total_files} files")
    print(f"📄 Generated: {c_path}")
    print(f"📄 Generated: {h_path}")
    print(f"💾 Total embedded size: {total_size:.1f} MB")
    print(f"{'=' * 50}")

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("\n\n❌ Cancelled by user")
        sys.exit(1)