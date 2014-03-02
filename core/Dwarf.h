#ifndef CORE_DWARF_H
#define CORE_DWARF_H

#include "core/World.h"

class Dwarf : public IEntity {

private:
    World *m_World;
    std::string m_Name;

public:
    inline Dwarf(World *world, Coordinates coords, const std::string &name)
      : IEntity(coords), m_World(world), m_Name(name)
    {
    }

    unsigned int type() const;

    inline std::string name() const
    {
        return m_Name;
    }

};

#endif
