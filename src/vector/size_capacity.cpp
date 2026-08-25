// size_capacity.cpp
// Vector size versus capacity

#include <vector>
#include <iostream>

using namespace std;

int main()
{
    vector<int> vec;
    cout << "vec: size: " << vec.size() 
         << " capacity: " << vec.capacity() << endl;

    for(int i = 0; i < 24; i++) {
        vec.push_back(i);
        cout << "vec: size: " << vec.size() 
             << " capacity: " << vec.capacity() << endl;
    }
    // Exercise 2.1:
    // 1. vector size is the number of elements stored by the vector currently
    // while vector capacity is the full umber of elements a vector can possibly hold before it needs to grow again
    // so capacity can be bigger or equal to size of a vector
    // 2. when a vector needs more capacity, it must allocate a new block of memory and copy all existing elements into it which is very inefficient
    // so it grows exponentially instead for less frequent reallocations for more efficiency. 


    return 0;
}

