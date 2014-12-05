#include "PersonajeJugador.h"

PersonajeJugador::PersonajeJugador(int x, int y,
                                    SDL_Renderer* renderer,
                                    list<Personaje*>*personajes)
{
    this->rectangulo.x = x;
    this->rectangulo.y = y;
    this->personajes=personajes;

    SDL_Texture *textura = IMG_LoadTexture(renderer, "assets/personaje/down1.png");
    SDL_QueryTexture(textura, NULL, NULL, &this->rectangulo.w, &this->rectangulo.h);
    texturas_down.push_back(textura);

    texturas_down.push_back(IMG_LoadTexture(renderer, "assets/personaje/down2.png"));

    texturas_up.push_back(IMG_LoadTexture(renderer, "assets/personaje/up1.png"));
    texturas_up.push_back(IMG_LoadTexture(renderer, "assets/personaje/up2.png"));

    texturas_left.push_back(IMG_LoadTexture(renderer, "assets/personaje/left1.png"));
    texturas_left.push_back(IMG_LoadTexture(renderer, "assets/personaje/left2.png"));

    texturas_right.push_back(IMG_LoadTexture(renderer, "assets/personaje/right1.png"));
    texturas_right.push_back(IMG_LoadTexture(renderer, "assets/personaje/right2.png"));

    orientacion="down";

    textura_actual=texturas_down.begin();

   SDL_Texture* rayo2_textura = IMG_LoadTexture(renderer,  "assets/Thunder/right/thunder_right1.png");
    rayo2_right.push_back(IMG_LoadTexture(renderer, "assets/Thunder/right/lightning.png"));
    rayo2_right.push_back(IMG_LoadTexture(renderer, "assets/Thunder/right/lightning2.png"));
    rayo2_right.push_back(IMG_LoadTexture(renderer, "assets/Thunder/right/lightning3.png"));
    rayo2_right.push_back(IMG_LoadTexture(renderer, "assets/Thunder/right/lightning4.png"));

    rayo2_left.push_back(IMG_LoadTexture(renderer, "assets/Thunder/left/lightning.png"));
    rayo2_left.push_back(IMG_LoadTexture(renderer, "assets/Thunder/left/lightning2.png"));
    rayo2_left.push_back(IMG_LoadTexture(renderer, "assets/Thunder/left/lightning3.png"));
    rayo2_left.push_back(IMG_LoadTexture(renderer, "assets/Thunder/left/lightning4.png"));

    rayo2_up.push_back(IMG_LoadTexture(renderer, "assets/Thunder/up/lightning.png"));
    rayo2_up.push_back(IMG_LoadTexture(renderer, "assets/Thunder/up/lightning2.png"));
    rayo2_up.push_back(IMG_LoadTexture(renderer, "assets/Thunder/up/lightning3.png"));
    rayo2_up.push_back(IMG_LoadTexture(renderer, "assets/Thunder/up/lightning4.png"));

    rayo2_down.push_back(IMG_LoadTexture(renderer, "assets/Thunder/down/lightning.png"));
    rayo2_down.push_back(IMG_LoadTexture(renderer, "assets/Thunder/down/lightning2.png"));
    rayo2_down.push_back(IMG_LoadTexture(renderer, "assets/Thunder/down/lightning3.png"));
    rayo2_down.push_back(IMG_LoadTexture(renderer, "assets/Thunder/down/lightning4.png"));

    rayo_texture = IMG_LoadTexture(renderer, "assets/rayo.png");
    SDL_QueryTexture(rayo_texture, NULL, NULL, &this->rayo_rect.w, &this->rayo_rect.h);
    SDL_QueryTexture(rayo2_textura, NULL, NULL, &this->rayo2_rect.w, &this->rayo2_rect.h);

    rayo_rect.x = 0;
    rayo_rect.y = 0;
    rayo2_rect.x = 0;
    rayo2_rect.y = 0;
    rayo_activado = false;
    rayo2_activado = false;

    rayo_cooldown = 100;
    rayo_frame_actual = 0;
    rayo_orientacion = orientacion;

}

PersonajeJugador::~PersonajeJugador()
{
    //dtor
}

void PersonajeJugador::logic(Uint8* teclas_presionadas)
{
    SDL_Rect temp = this->rectangulo;

    if(rayo_activado)
    {
        rayo_frame_actual++;
    }

    if(rayo2_activado)
    {
        rayo_frame_actual++;
    }

    if(rayo_frame_actual >= rayo_cooldown)
    {
        rayo_activado = false;
        rayo2_activado = false;
    }

    if(teclas_presionadas[SDL_SCANCODE_SPACE] && !rayo2_activado && !rayo_activado)
    {
        //cout << "Entro" << endl;
        rayo2_activado = true;
        rayo_frame_actual = 0;
        rayo2_rect.x = rectangulo.x;
        rayo2_rect.y = rectangulo.y;
        if(orientacion == "right")
        {
            rayo2_actual = rayo2_right.begin();
            rayo2_rect.x+= rectangulo.w;
        }

        else if(orientacion == "left")
        {
            rayo2_actual = rayo2_left.begin();
            rayo2_rect.x-= rectangulo.w;
        }

        else if(orientacion == "up")
        {
            rayo2_actual = rayo2_up.begin();
            rayo2_rect.y-= rectangulo.h;
        }

        else if(orientacion == "down")
        {
            rayo2_actual = rayo2_down.begin();
            rayo2_rect.y+= rectangulo.h;
        }
    }

    if(teclas_presionadas[SDL_SCANCODE_X] && !rayo_activado && !rayo2_activado)
    {
      //  cout << "Entro - rayo normal" << endl;
        rayo_activado = true;
        rayo_frame_actual = 0;
        rayo_rect.x = rectangulo.x;
        rayo_rect.y = rectangulo.y;
        if(orientacion == "right")
        {
            rayo_rect.x+= rectangulo.w;
        }

        if(orientacion == "left")
        {
            rayo_rect.x-= rectangulo.w;
        }

        if(orientacion == "up")
        {
            rayo_rect.y-= rectangulo.h;
        }

        if(orientacion == "down")
        {
            rayo_rect.y+= rectangulo.h;
        }
    }

    else
    {
        if(rayo2_activado != true)
        {
            if( teclas_presionadas[ SDL_SCANCODE_UP] )
            {
                rectangulo.y-=1;
                if(orientacion!="up")
                    textura_actual=texturas_up.begin();
                orientacion="up";
            }
            if( teclas_presionadas[ SDL_SCANCODE_DOWN] )
            {
                rectangulo.y+=1;
                if(orientacion!="down")
                    textura_actual=texturas_down.begin();
                orientacion="down";
            }
            if( teclas_presionadas[ SDL_SCANCODE_RIGHT ] )
            {
                rectangulo.x+=1;
                if(orientacion!="right")
                    textura_actual=texturas_right.begin();
                orientacion="right";
            }
            if( teclas_presionadas[ SDL_SCANCODE_LEFT ] )
            {
                rectangulo.x-=1;
                if(orientacion!="left")
                    textura_actual=texturas_left.begin();
                orientacion="left";
            }
            rayo_orientacion = orientacion;
        }
    }

    for(list<Personaje*>::iterator i = personajes->begin(); i!=personajes->end(); i++)
    {
        if(this==(*i))
            continue;
        if(colision(this->rayo_rect, (*i)->rectangulo))
        {
            //rectangulo=temp;
            personajes->erase(i);
            rayo_activado = false;
            //rayo2_activado = false;
            break;
        }

        if(colision(this->rayo2_rect, (*i)->rectangulo))
        {
            (*i)->moviendo = false;
            personajes->erase(i);
            //rayo_activado = false;
            rayo2_activado = false;
            break;
        }
    }

    if(rayo_activado)
    {
        if(rayo_orientacion == "up")
        {
            rayo_rect.y-= 2;
        }

        if(rayo_orientacion == "down")
        {
            rayo_rect.y+= 2;
        }

        if(rayo_orientacion == "left")
        {
            rayo_rect.x-= 2;
        }

        if(rayo_orientacion == "right")
        {
            rayo_rect.x+= 2;
        }
    }

    if(rayo2_activado)
    {
        if(rayo_orientacion == "up")
        {
            rayo2_rect.y-= 2;
        }

        if(rayo_orientacion == "down")
        {
            rayo2_rect.y += 2;
        }

        if(rayo_orientacion == "left")
        {
            rayo2_rect.x-= 2;
        }

        if(rayo_orientacion == "right")
        {
            rayo2_rect.x+= 2;
        }
    }

//    if(rayo2_activado != true)
//    {
//        rayo2_rect.x = rectangulo.x;
//        rayo2_rect.y = rectangulo.y;
//    }
//
//    if(rayo_activado != true)
//    {
//        rayo_rect.x = rectangulo.x;
//        rayo_rect.y = rectangulo.y;
//    }

}

void PersonajeJugador::mover_rayo2(SDL_Renderer* renderer)
{
    //cout << "Entro al mov" << endl;
    SDL_RenderCopy(renderer, *rayo2_actual, NULL, &rayo2_rect);
    rayo2_actual++;

    if(rayo_orientacion == "right")
    {
        if(rayo2_actual == rayo2_right.end())
            rayo2_actual = rayo2_right.begin();
    }

    if(rayo_orientacion == "left")
    {
        if(rayo2_actual == rayo2_left.end())
            rayo2_actual = rayo2_left.begin();
    }

    if(rayo_orientacion == "up")
    {
        if(rayo2_actual == rayo2_up.end())
            rayo2_actual = rayo2_up.begin();
    }

    if(rayo_orientacion == "down")
    {
        if(rayo2_actual == rayo2_down.end())
            rayo2_actual = rayo2_down.begin();
    }
}

void PersonajeJugador::render(SDL_Renderer* renderer)
{
    Personaje::render(renderer);
    if(rayo_activado)
    {
        SDL_RenderCopy(renderer, rayo_texture, NULL, &rayo_rect);
        //mover_rayo2(renderer);
    }

    if(rayo2_activado)
    {
//        while(rayo2_actual != rayo2_right.end())
//        {
//            SDL_RenderCopy(renderer, *rayo2_actual, NULL, &rayo_rect);
//            rayo2_actual++;
//
//        }
      //  cout << "Entro al mov" << endl;
        mover_rayo2(renderer);
    }
}




