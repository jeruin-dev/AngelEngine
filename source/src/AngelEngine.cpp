#include "../headers/AngelEngine.hpp"
#include <cassert>
#include <fmt/base.h>

AngelEngine::AngelEngine(){
    this->engine = asCreateScriptEngine();

    int r = engine->SetMessageCallback(asFUNCTION(this->MessageCallback), 0, asCALL_CDECL); assert( r >= 0 );
}

void AngelEngine::MessageCallback(const asSMessageInfo *msg, void *param){
  const char *type = "ERR ";
  if( msg->type == asMSGTYPE_WARNING )
    type = "WARN";
  else if( msg->type == asMSGTYPE_INFORMATION )
    type = "INFO";
  fmt::print("{} ({}, {}) : {} : {}\n", msg->section, msg->row, msg->col, type, msg->message);
}

void AngelEngine::RegisterModule(const char *name, const char *path){
    int result = this->builder.StartNewModule(this->engine,name); assert( result >= 0);

    result = this->builder.AddSectionFromFile(path);
}
