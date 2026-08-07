#include "player.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/global_constants.hpp>

void Jugador::_bind_methods()
{
    godot::ClassDB::bind_method(godot::D_METHOD("get_velocidad"), &Jugador::get_velocidad);
    godot::ClassDB::bind_method(godot::D_METHOD("set_velocidad", "p_velocidad"), &Jugador::set_velocidad);

    godot::ClassDB::bind_method(godot::D_METHOD("get_nombre"), &Jugador::get_nombre);
    godot::ClassDB::bind_method(godot::D_METHOD("set_nombre", "p_nombre"), &Jugador::set_nombre);

    godot::ClassDB::bind_method(godot::D_METHOD("get_vida"), &Jugador::get_vida);
    godot::ClassDB::bind_method(godot::D_METHOD("set_vida", "p_vida"), &Jugador::set_vida);

    // Expone la propiedad 'velocidad' al inspector de Godot
    ADD_PROPERTY(godot::PropertyInfo(godot::Variant::FLOAT, "velocidad"), "set_velocidad", "get_velocidad");
    ADD_PROPERTY(godot::PropertyInfo(godot::Variant::STRING, "nombre"), "set_nombre", "get_nombre");
    ADD_PROPERTY(godot::PropertyInfo(godot::Variant::INT, "vida"), "set_vida", "get_vida");
}

Jugador::Jugador() : velocidad(50.0), nombre("Pachoncito 3842"), vida(100)
{
    // velocidad = 400.0;
}

Jugador::~Jugador()
{
}

void Jugador::_process(double delta)
{

    auto *input = godot::Input::get_singleton();
    if (!input)
    {
        return;
    }

    auto direccion = godot::Vector2(0, 0);

    // Detección de teclas (WASD / Flechas usando acciones predeterminadas de Godot)
    if (input->is_action_pressed("ui_right") || input->is_key_pressed(godot::Key::KEY_D))
    {
        direccion.x += 1.0;
    }
    if (input->is_action_pressed("ui_left") || input->is_key_pressed(godot::Key::KEY_A))
    {
        direccion.x -= 1.0;
    }
    if (input->is_action_pressed("ui_down") || input->is_key_pressed(godot::Key::KEY_S))
    {
        direccion.y += 1.0;
    }
    if (input->is_action_pressed("ui_up") || input->is_key_pressed(godot::Key::KEY_W))
    {
        direccion.y -= 1.0;
    }

    // Normalizar vector para evitar que camine más rápido al ir en diagonal
    if (direccion.length() > 0)
    {
        direccion = direccion.normalized();
    }

    // Aplicar el movimiento
    auto pos = this->get_position();
    pos += direccion * velocidad * delta;
    this->set_position(pos);
}

void Jugador::set_velocidad(const double p_velocidad)
{
    velocidad = p_velocidad;
}

double Jugador::get_velocidad() const
{
    return velocidad;
}

void Jugador::set_nombre(const godot::String p_nombre)
{
    nombre = p_nombre;
}

godot::String Jugador::get_nombre() const
{
    return nombre;
}
