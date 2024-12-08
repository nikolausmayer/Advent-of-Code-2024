I spent a little while searching for how to put `std::plus` and `std::multiplies` into a common container, but could not find a way.

Then I made a recursive lambda with C++23's `deducing this` feature, and promptly made GCC-14 run into a forever loop. I do not understand what happened, but I blame my lack of understanding of C++ "views".

Finally, I made my lambda a bit less fancy, and that worked directly. 

I then only had to add a single line (and fix a 32bit-overflow issue, naturally..) for the new operator in part 2!
