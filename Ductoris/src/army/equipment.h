#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include <cstdint>

class Equipment
{
public:
    Equipment();
    virtual ~Equipment();

protected:
    uint16_t m_value;
};

#endif // EQUIPMENT_H
