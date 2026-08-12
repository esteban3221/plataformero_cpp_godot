#include "controlador_jugador.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

ControladorJugador::ControladorJugador() {}
ControladorJugador::~ControladorJugador() {}

void ControladorJugador::_bind_methods()
{
    godot::ClassDB::bind_method(godot::D_METHOD("get_ruta_jugador"), &ControladorJugador::get_ruta_jugador);
    godot::ClassDB::bind_method(godot::D_METHOD("set_ruta_jugador", "p_ruta"), &ControladorJugador::set_ruta_jugador);

    godot::ClassDB::bind_method(godot::D_METHOD("get_ruta_sprite"), &ControladorJugador::get_ruta_sprite);
    godot::ClassDB::bind_method(godot::D_METHOD("set_ruta_sprite", "p_ruta"), &ControladorJugador::set_ruta_sprite);

    // Expone la propiedad en el Inspector limitándola estrictamente a CharacterBody2D
    ADD_PROPERTY(
        godot::PropertyInfo(
            godot::Variant::NODE_PATH,
            "Ruta Jugador",
            godot::PROPERTY_HINT_NODE_PATH_VALID_TYPES,
            "CharacterBody2D"),
        "set_ruta_jugador",
        "get_ruta_jugador");

    ADD_PROPERTY(
        godot::PropertyInfo(
            godot::Variant::NODE_PATH,
            "Ruta Sprite",
            godot::PROPERTY_HINT_NODE_PATH_VALID_TYPES,
            "AnimatedSprite2D"),
        "set_ruta_sprite",
        "get_ruta_sprite");
}

void ControladorJugador::_ready()
{
    if (has_node(ruta_jugador))
    {
        cuerpo = get_node<godot::CharacterBody2D>(ruta_jugador);
    }
    if (has_node(ruta_sprite))
    {
        sprite = get_node<godot::AnimatedSprite2D>(ruta_sprite);
    }
}

void ControladorJugador::_physics_process(double delta)
{
    if (!cuerpo)
        return;

    if (!sprite)
        return;

    auto velocity = cuerpo->get_velocity();

    if (!cuerpo->is_on_floor())
        velocity.y += gravedad * delta;

    godot::Input *input = godot::Input::get_singleton();
    if (input->is_action_just_pressed("ui_accept") && cuerpo->is_on_floor())
        velocity.y = -fuerza_salto;

    double direccion = 0.0;
    if (input->is_action_pressed("ui_right"))
        direccion += 1.0;
    if (input->is_action_pressed("ui_left"))
        direccion -= 1.0;
    if (direccion != 0.0)
        velocity.x = direccion * velocidad;
    else
        velocity.x = godot::Math::move_toward(velocity.x, 0.0f, static_cast<float>(velocidad * delta * 13.0f));

    if (!cuerpo->is_on_floor())
        sprite->play("saltar");
    else if (velocity.x != 0)
        sprite->play("correr");
    else
        sprite->play("idle");

    // NUEVA LÓGICA DE GIRO
    if (direccion < 0.0)
        sprite->set_flip_h(false); // Voltea a la izquierda
    else if (direccion > 0.0)
        sprite->set_flip_h(true);

    cuerpo->set_velocity(velocity);
    cuerpo->move_and_slide();
}