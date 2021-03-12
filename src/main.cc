#include "terwinal.h"

#include <iostream>
#include <cassert>
#include <string>
#include <regex>

// todo add default handler (in case nothing executes)
// todo add prefix option to allow for dynamic input

int main(int argc, char const *argv[]) {
    terwinal::TextBody text;

    text.content << "Hello, world!" << '\n';

    text.addKeyController("print", [](terwinal::Event event) {
        std::cout << "get printed lol" << '\n';
        return false;
    });
    text.addKeyController("exit", [](terwinal::Event event) { return true; });

    text.render(true);
    text.listen();
}