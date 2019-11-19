#pragma once
#include <iostream>

class Population
{
public:
    virtual void update()
    {
        std::cout << "Update not implemented!" << std::endl;
    }

private:
};
