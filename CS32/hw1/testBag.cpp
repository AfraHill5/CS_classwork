    #include "Bag.h"
    #include <iostream>
    #include <cassert>
    using namespace std;

    int main()
    {
        Bag b;
        assert(b.empty());
        assert( ! b.contains(42));
        b.insert(42);
        b.insert(42);
        assert(b.size() == 2  && b.uniqueSize() == 1);
        b.start();
        assert( ! b.ended()  &&  b.currentValue() == 42
                        &&  b.currentCount() == 2);
        b.next();
        assert(b.ended());
        cout << "Passed all tests" << endl;
    }