#include "App.h"

extern CGameState GameState;

void CApp::OnEvent(SDL_Event *Event)
{
    CEvent::OnEvent(Event);
}

void CApp::OnExit()
{
    Running = false;
}

void CApp::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    switch(sym)
    {
    case SDLK_BACKSPACE:
        if(TestString.size())
        {
            TestString.resize((TestString.size()-1));
        }
        break;
    case SDLK_a:
        if(TestString.size() > 23) break;
        TestString.push_back('a');
        break;
    case SDLK_b:
        if(TestString.size() > 23) break;
        TestString.push_back('b');
        break;
    case SDLK_c:
        if(TestString.size() > 23) break;
        TestString.push_back('c');
        break;
    case SDLK_d:
        if(TestString.size() > 23) break;
        TestString.push_back('d');
        break;
    case SDLK_e:
        if(TestString.size() > 23) break;
        TestString.push_back('e');
        break;
    case SDLK_f:
        if(TestString.size() > 23) break;
        TestString.push_back('f');
        break;
    case SDLK_g:
        if(TestString.size() > 23) break;
        TestString.push_back('g');
        break;
    case SDLK_h:
        if(TestString.size() > 23) break;
        TestString.push_back('h');
        break;
    case SDLK_i:
        if(TestString.size() > 23) break;
        TestString.push_back('i');
        break;
    case SDLK_j:
        if(TestString.size() > 23) break;
        TestString.push_back('j');
        break;
    case SDLK_k:
        if(TestString.size() > 23) break;
        TestString.push_back('k');
        break;
    case SDLK_l:
        if(TestString.size() > 23) break;
        TestString.push_back('l');
        break;
    case SDLK_m:
        if(TestString.size() > 23) break;
        TestString.push_back('m');
        break;
    case SDLK_n:
        if(TestString.size() > 23) break;
        TestString.push_back('n');
        break;
    case SDLK_o:
        if(TestString.size() > 23) break;
        TestString.push_back('o');
        break;
    case SDLK_p:
        if(TestString.size() > 23) break;
        TestString.push_back('p');
        break;
    case SDLK_q:
        if(TestString.size() > 23) break;
        TestString.push_back('q');
        break;
    case SDLK_r:
        if(TestString.size() > 23) break;
        TestString.push_back('r');
        break;
    case SDLK_s:
        if(TestString.size() > 23) break;
        TestString.push_back('s');
        break;
    case SDLK_t:
        if(TestString.size() > 23) break;
        TestString.push_back('t');
        break;
    case SDLK_u:
        if(TestString.size() > 23) break;
        TestString.push_back('u');
        break;
    case SDLK_v:
        if(TestString.size() > 23) break;
        TestString.push_back('v');
        break;
    case SDLK_w:
        if(TestString.size() > 23) break;
        TestString.push_back('w');
        break;
    case SDLK_x:
        if(TestString.size() > 23) break;
        TestString.push_back('x');
        break;
    case SDLK_y:
        if(TestString.size() > 23) break;
        TestString.push_back('y');
        break;
    case SDLK_z:
        if(TestString.size() > 23) break;
        TestString.push_back('z');
        break;
    case SDLK_0:
        if(TestString.size() > 23) break;
        TestString.push_back('0');
        break;
    case SDLK_1:
        if(TestString.size() > 23) break;
        TestString.push_back('1');
        break;
    case SDLK_2:
        if(TestString.size() > 23) break;
        TestString.push_back('2');
        break;
    case SDLK_3:
        if(TestString.size() > 23) break;
        TestString.push_back('3');
        break;
    case SDLK_4:
        if(TestString.size() > 23) break;
        TestString.push_back('4');
        break;
    case SDLK_5:
        if(TestString.size() > 23) break;
        TestString.push_back('5');
        break;
    case SDLK_6:
        if(TestString.size() > 23) break;
        TestString.push_back('6');
        break;
    case SDLK_7:
        if(TestString.size() > 23) break;
        TestString.push_back('7');
        break;
    case SDLK_8:
        if(TestString.size() > 23) break;
        TestString.push_back('8');
        break;
    case SDLK_9:
        if(TestString.size() > 23) break;
        TestString.push_back('9');
        break;
    }

}
/*
void CApp::OnLButtonDown(int x, int y)
{

    switch (GameState.getGameStatus())
    {
    }
}
*/
