#include "Ductoris.h"

//singleton init
Ductoris *Ductoris::m_ductoriusGame = nullptr;

Ductoris::Ductoris()
{

}

void Ductoris::initilize()
{

}

Ductoris::~Ductoris()
{

}

Ductoris *Ductoris::getInstance()
{
    if(!Ductoris::m_ductoriusGame->m_initialized)
    {
        //initialize game
        Ductoris::m_ductoriusGame->initilize();
    }
    return  Ductoris::m_ductoriusGame;
}

void Ductoris::onUnitMove(int x, int y)
{

}

void Ductoris::onSelectUnit()
{

}

void Ductoris::onUnitAttack()
{

}

void Ductoris::onNewUnitCreate()
{

}

void Ductoris::onUnitAttacked()
{

}



