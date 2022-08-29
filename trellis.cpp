#include "trellis.h"

Trellis::Trellis()
{
    //possibleTransitions
    possibleTransitions.push_back(Tuple {0,0});
    possibleTransitions.push_back(Tuple {0,2});
    possibleTransitions.push_back(Tuple {1,0});
    possibleTransitions.push_back(Tuple {1,2});
    possibleTransitions.push_back(Tuple {2,1});
    possibleTransitions.push_back(Tuple {2,3});
    possibleTransitions.push_back(Tuple {3,1});
    possibleTransitions.push_back(Tuple {3,3});
    
    //transitionMatrix
    transitionMatrix.push_back(Tuple {-1,-1});
    transitionMatrix.push_back(Tuple {0,0});
    transitionMatrix.push_back(Tuple {1,1});
    transitionMatrix.push_back(Tuple {0,0});
    
    transitionMatrix.push_back(Tuple {1,-1});
    transitionMatrix.push_back(Tuple {0,0});
    transitionMatrix.push_back(Tuple {-1,1});
    transitionMatrix.push_back(Tuple {0,0});

    transitionMatrix.push_back(Tuple {0,0});
    transitionMatrix.push_back(Tuple {-1,-1});
    transitionMatrix.push_back(Tuple {0,0});
    transitionMatrix.push_back(Tuple {1,1});

    transitionMatrix.push_back(Tuple {0,0});
    transitionMatrix.push_back(Tuple {1,-1});
    transitionMatrix.push_back(Tuple {0,0});
    transitionMatrix.push_back(Tuple {-1,1});

    //pastStates
    pastStates.push_back(Tuple {0,1});
    pastStates.push_back(Tuple {2,3});
    pastStates.push_back(Tuple {0,1});
    pastStates.push_back(Tuple {2,3});

    //futureStates
    futureStates.push_back(Tuple {0,2});
    futureStates.push_back(Tuple {0,2});
    futureStates.push_back(Tuple {1,3});
    futureStates.push_back(Tuple {1,3});

}

Tuple Trellis::GetSymbolTransitionMatrix(int x, int y)
{
    return transitionMatrix[(x*4) + y];
}

double Trellis::Butterfly(double a1,double a2,double b1,double b2)
{
    return std::max(a1+b1,a2+b2);
}