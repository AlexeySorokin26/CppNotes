#include <iostream>

#include <vector>

// before C++ 11 this code below would habe to make 3 extra copies
// First if we have s + s 
// Second just s
// And finally after we use assigning operator. RVO only helps in return statement. So we dont copy but we copy for return statment but copy after in = operator. 

std::vector<std::string> CreateAndInsertV(){
    std::vector<std::string> v;
    v.reserve(10);

    std::string s = "data";

    v.push_back(s);

    v.push_back(s + s);

    v.push_back(std::move(s));

    return v;
}


int main(){
   auto v = CreateAndInsertV();
}