#ifndef JUGADOR_H
#define JUGADOR_H
#include <iostream>

#include <godot_cpp/classes/sprite2d.hpp>

class Jugador : public godot::Sprite2D
{
    GDCLASS(Jugador, godot::Sprite2D)

private:
    double velocidad;
    godot::String nombre;
    int vida;

protected:
    static void _bind_methods();

public:
    Jugador();
    ~Jugador();

    void _process(double delta) override;

    void set_velocidad(const double p_velocidad);
    double get_velocidad() const;

    void set_nombre(const godot::String p_nombre);
    godot::String get_nombre() const;

    void set_vida(const int p_vida) { vida = p_vida; }
    int get_vida() const { return vida; }
};

#endif // JUGADOR_H