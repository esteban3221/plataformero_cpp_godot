#include "register_types.h"
#include "player.h" // 1. Incluir encabezado
#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void initialize_plataformero_module(ModuleInitializationLevel p_level)
{
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
    {
        return;
    }

    GDREGISTER_CLASS(Jugador); // 2. Registrar clase
    godot::UtilityFunctions::print("Módulo 'plataformero' inicializado correctamente.");
}

void uninitialize_plataformero_module(ModuleInitializationLevel p_level)
{
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
    {
        return;
    }
    godot::UtilityFunctions::print("Módulo 'plataformero' terminado correctamente.");
}

extern "C"
{
    GDExtensionBool GDE_EXPORT plataformero_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
    {
        godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

        init_obj.register_initializer(initialize_plataformero_module);
        init_obj.register_terminator(uninitialize_plataformero_module);
        init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

        return init_obj.init();
    }
}