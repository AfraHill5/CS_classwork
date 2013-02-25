//TEST FUNCTIONS DO NOT TURN IN

#include "Bag.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main()
{
    Bag<int> bi;
    Bag<string> bs;
    assert(bi.empty());
    assert(bs.size() == 0);
    assert(bi.insert(10));
    assert(bs.insert("hello"));
    assert(bs.insert("hello"));
    assert(bs.uniqueSize() == 1);
    assert(bi.contains(10));
    assert(bs.count("hello") == 2);
    bs.start();
    assert(bs.currentValue() == "hello");
    assert(bs.currentCount() == 2);
    bs.next();
    assert(bs.ended());
    assert(bi.erase(10) == 1);
    assert(bs.eraseAll("hello") == 2);
    Bag<string> bs2(bs);
    bs.swap(bs2);
    bs = bs2;
    combine(bi,bi,bi);
    combine(bs,bs2,bs);
    subtract(bi,bi,bi);
    subtract(bs,bs2,bs);
    cout << "Passed all tests" << endl;
}