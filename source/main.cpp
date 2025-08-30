#include <fmt/base.h>
#include <assert.h>

#include <angelscript.h>
#include <scriptstdstring/scriptstdstring.h>
#include <scriptbuilder/scriptbuilder.h>
#include <string>

#include "headers/AngelEngine.hpp"

void print(std::string &msg ){
    fmt::println("\n\t {}\n",msg);
}

int main(){

    auto angel = new AngelEngine;

    angel->registerstd(angel->engine);

    angel->engine->RegisterGlobalFunction("void print(const string &in)", asFUNCTION(print), asCALL_CDECL);

    angel->RegisterModule("MyModule","AngelScript/main.as");

    angel->run("MyModule","void main()");

   return 0;
}
