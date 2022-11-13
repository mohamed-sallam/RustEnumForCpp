#include <iostream>
#include <variant>

#define ENUM
#define CASE(caseName) struct caseName
#define END_ENUM(enumName, ...) using enumName = std::variant<__VA_ARGS__>;

#define MATCH std::visit(overload{
#define WHEN(caseName) [=](const caseName & _this_)
#define OTHERWISE [=](const auto & )
#define END_MATCH(matchParam) }, matchParam);

template<class... Ts>
struct overload : Ts... {
    using Ts::operator()...;
};
template<class... Ts>
overload(Ts...) -> overload<Ts...>;

// Source: stackoverflow.com/a/64018031
int main() {
    ENUM
        CASE(Quit) {};
        CASE(Move) { int32_t x; int32_t y; };
        CASE(Write) { std::string s; };
        CASE(ChangeColor) { int32_t r; int32_t g; int32_t b; };
    END_ENUM(Message, Quit, Move, Write, ChangeColor)

    Message m1{Quit{}};
    Message m2{Move{1, 2}};
    Message m3{Write{"a"}};
    Message m4{ChangeColor{1, 2, 3}};
    Message m5{};

    MATCH
        WHEN(Quit) { std::cout << "Quit\n"; },
        WHEN(Move) { std::cout << "Move " << _this_.x << " " << _this_.y << "\n"; },
        WHEN(ChangeColor) { std::cout << "ChangeColor " << _this_.r << " " << _this_.g << " " << _this_.b << "\n"; },
        OTHERWISE { std::cout << "Otherwise\n"; }
    END_MATCH(m2)

    return 0;

}
