#include "../headers/AngelEngine.hpp"
#include "scriptstdstring/scriptstdstring.h"
#include <angelscript.h>
#include <cassert>
#include <fmt/base.h>
#include <print>

//Mensaje de error
 void AngelEngine::MessageCallback(const asSMessageInfo *msg, void *param){
  const char *type = "ERR ";
  if( msg->type == asMSGTYPE_WARNING )
    type = "WARN";
  else if( msg->type == asMSGTYPE_INFORMATION )
    type = "INFO";
  fmt::print("{} ({}, {}) : {} : {}\n", msg->section, msg->row, msg->col, type, msg->message);
}

//contructor
AngelEngine::AngelEngine(){
    this->engine = asCreateScriptEngine();

    int result = this->engine->SetMessageCallback(asFunctionPtr(&this->MessageCallback),0,asCALL_CDECL); assert(result >= 0);
    FnControl(result,"error Message");
}

//Control de funciones
void AngelEngine::FnControl(int result, const char *msg){
    if (result < 0) {
        std::println("{},{}",result , msg);
    }
}

//Register Funcion
template<typename T>
void AngelEngine::RegisterFunction(const char *decharation,T func){
    int result = this->engine->RegisterGlobalFunction(decharation,asFUNCTION(func), asCALL_CDECL);

   FnControl(result,"fallo en el registro de funcion");
}

//Registro de modulos
void AngelEngine::RegisterModule(const char *name, const char *path){
    int result = this->builder.StartNewModule(this->engine,name); assert( result >= 0);

    FnControl(result,"fallo module");

    result = this->builder.AddSectionFromFile(path);
    FnControl(result,"fallo en el path");
}

void AngelEngine::BuildModule(){
    this->builder.BuildModule();
}

void AngelEngine::run(const char *module, const char *FuncByDecl){
    this->BuildModule();
    asIScriptModule *mod = engine->GetModule(module);
    asIScriptFunction *func = mod->GetFunctionByDecl(FuncByDecl);

    if (func == 0) {
        fmt::println("Error funcion");
    }

     // Create our context, prepare it, and then execute
     this->ctx = engine->CreateContext();
     this->ctx->Prepare(func);
     int r = this->ctx->Execute();
     if( r != asEXECUTION_FINISHED )
     {
       // The execution didn't complete as expected. Determine what happened.
       if( r == asEXECUTION_EXCEPTION )
       {
         // An exception occurred, let the script writer know what happened so it can be corrected.
         fmt::println("An exception '{}' occurred. Please correct the code and try again.\n", ctx->GetExceptionString());
       }
     }

}

void AngelEngine::registerstd(asIScriptEngine *engine){
    RegisterStdString(engine);
}

AngelEngine::~AngelEngine(){
    ctx->Release();
    engine->ShutDownAndRelease();
}
