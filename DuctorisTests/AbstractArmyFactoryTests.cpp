#include "AbstractArmyFactoryTests.h"
#include "abstractarmyfactory.h"
#include "romanarmyfactory.h"
#include <memory>

void AbstractArmyFactoryTests::TestCase_RomanArmyFactoryCreation()
{
    std::unique_ptr<AbstractArmyFactory> romanFactory(new RomanArmyFactory);
}

void AbstractArmyFactoryTests::TestCase_MacedonArmyFactoryCreation()
{

}

void AbstractArmyFactoryTests::TestCase_GallicArmyFactoryCreation()
{

}

