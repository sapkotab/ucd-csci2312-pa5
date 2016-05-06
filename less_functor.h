//
// Created by bhuwan sapkota on 5/4/16.
//


#ifndef UCD_CSCI2312_PA5_LESS_FUNCTOR_H
#define UCD_CSCI2312_PA5_LESS_FUNCTOR_H
namespace CS2312{

    // less class template for generic type T
    template <class T>
    class less{
    public:
        bool operator ()(T const &first, T const &second){
            return first < second;
        };
    };

    // Specialized for string.
    template <>
    class less<std::string>{
    public:
        bool operator ()(std::string const &first, std::string const &second){
            return first < second;
        };
    };

    // specialized for c-strings
    template <>
    class less <const char* >{
    public:
        bool operator ()( char* const first,char* const second){
            // changing c-strings to string
            // to make it easy to compare. we could also compare using for loops like a array of char.
            string string1 = first;
            string string2 = second;
            return string1 <string2;
        };
    };

}
#endif //UCD_CSCI2312_PA5_LESS_FUNCTOR_H
