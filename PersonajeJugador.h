#ifndef PERSONAJEJUGADOR_H
#define PERSONAJEJUGADOR_H
#include <vector>
#include "Personaje.h"

class PersonajeJugador : public Personaje
{
    public:
        SDL_Texture *rayo_texture;
        SDL_Texture *rayo_texture2;
         SDL_Texture *rayo_texture3;
        vector<SDL_Texture*> rayos;
        SDL_Rect rayo_rect;
         SDL_Rect rayo2_rect;
        list<SDL_Texture*> rayo2_right;
        list<SDL_Texture*> rayo2_left;
        list<SDL_Texture*> rayo2_up;
        list<SDL_Texture*> rayo2_down;
        list<SDL_Texture*>::iterator rayo2_actual;
        bool rayo_activado;
        bool rayo2_activado;

        int rayo_cooldown;
        int rayo_frame_actual;
        string rayo_orientacion;
        PersonajeJugador(int x, int y,
                          SDL_Renderer* renderer,
                          list<Personaje*>*personajes);
        void logic(Uint8* teclas_presionadas);
         void mover_rayo2(SDL_Renderer* renderer);
        virtual void render(SDL_Renderer* renderer);

        virtual ~PersonajeJugador();
    protected:
    private:
};

#endif // PERSONAJEJUGADOR_H
