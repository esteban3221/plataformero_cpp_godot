#!/usr/bin/env python
import os

# Configuración básica del entorno
env = Environment()

# Variables de compilación (debug por defecto)
opts = Variables()
opts.Add(EnumVariable('target', 'Target build', 'template_debug', allowed_values=['editor', 'template_debug', 'template_release']))
opts.Add(BoolVariable("use_hot_reload", "Enable hot reloading", True))
opts.Update(env)

# Le decimos a SCons dónde está godot-cpp
env.Append(CPPPATH=['godot-cpp/gdextension', 'godot-cpp/include', 'godot-cpp/gen/include', 'src'])
env.Append(LIBPATH=['godot-cpp/bin'])

# Configuramos la librería que vamos a enlazar (la que ya compilaste)
if env['target'] in ['editor', 'template_debug']:
    env.Append(LIBS=['godot-cpp.linux.template_debug.x86_64'])
else:
    env.Append(LIBS=['godot-cpp.linux.template_release.x86_64'])

if env["use_hot_reload"]:
    env.Append(CPPDEFINES=["HOT_RELOAD_ENABLED"])
    # Evita que GCC use símbolos únicos que bloquean la descarga de la .so
    env.Append(CCFLAGS=["-fno-gnu-unique"]) 

# Banderas de compilación para C++17 (Requisito de Godot)
env.Append(CXXFLAGS=['-std=c++20', '-fPIC'])

# Recopilamos todos los archivos .cpp de tu carpeta src/
sources = Glob('src/*.cpp')

# Nombre del archivo final que se guardará en demo/bin/
library_name = 'godot_project/nuevo-proyecto-de-juego/bin/libplataformero.linux.' + env['target'] + '.x86_64.so'

# Compilamos como una librería compartida (.so en Linux)
env.SharedLibrary(target=library_name, source=sources)
