#include <iostream>
#include "StaticSynapse.h"

using namespace std;

StaticSynapse::StaticSynapse(Population* n_from, Population* n_to) : 
    param(new StaticSynapse_param), 
    from_population(n_from), 
    to_population(n_to) 
{

}

StaticSynapse::StaticSynapse(Population* n_from, Population* n_to, StaticSynapse_param* param) : 
    param(param), 
    from_population(n_from), 
    to_population(n_to)
{

}