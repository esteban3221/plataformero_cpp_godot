#pragma once
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/variant/node_path.hpp>

class ControladorJugador : public godot::Node
{
    GDCLASS(ControladorJugador, godot::Node)

private:
    godot::NodePath ruta_jugador;
    godot::NodePath ruta_sprite;

    godot::CharacterBody2D *cuerpo = nullptr;
    godot::AnimatedSprite2D *sprite = nullptr;

    // Parámetros de movimiento clásico
    double velocidad = 160.0;
    double gravedad = 700.0;
    double fuerza_salto = 320.0;

protected:
    static void _bind_methods();

public:
    ControladorJugador();
    ~ControladorJugador();

    void _ready() override;
    void _physics_process(double delta) override;

    void set_ruta_jugador(const godot::NodePath &p_ruta) { ruta_jugador = p_ruta; }
    void set_ruta_sprite(const godot::NodePath &p_ruta) { ruta_sprite = p_ruta; }
    godot::NodePath get_ruta_jugador() const { return ruta_jugador; }
    godot::NodePath get_ruta_sprite() const { return ruta_sprite; }
};