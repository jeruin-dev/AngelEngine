#include <fmt/base.h>
#include <assert.h>

#include <angelscript.h>
#include <scriptstdstring/scriptstdstring.h>
#include <scriptbuilder/scriptbuilder.h>
#include <string>

#include "headers/AngelEngine.hpp"

void MessageCallback(const asSMessageInfo *msg, void *param){
  const char *type = "ERR ";
  if( msg->type == asMSGTYPE_WARNING )
    type = "WARN";
  else if( msg->type == asMSGTYPE_INFORMATION )
    type = "INFO";
  printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
}

void print(std::string &msg ){
    fmt::println("\n\t {}\n",msg);
}

int main(){

    auto angel = new AngelEngine;

    asIScriptEngine *engine = asCreateScriptEngine();

    int r = engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL); assert( r >= 0 );

    RegisterStdString(engine);

    r = engine->RegisterGlobalFunction("void print(const string &in)", asFUNCTION(print), asCALL_CDECL); assert( r >= 0 );

   CScriptBuilder builder;
    r = builder.StartNewModule(engine, "MyModule");
    if( r < 0 ) {
     printf("Unrecoverable error while starting a new module.\n");
    }
    r = builder.AddSectionFromFile("AngelScript/main.as");
    if( r < 0 ){
     printf("Please correct the errors in the script and try again.\n");
    }
    r = builder.BuildModule();
    if( r < 0 ){
     printf("Please correct the errors in the script and try again.\n");
    }


    // Find the function that is to be called.
    asIScriptModule *mod = engine->GetModule("MyModule");
    asIScriptFunction *func = mod->GetFunctionByDecl("void main()");
    if( func == 0 ){
      // The function couldn't be found. Instruct the script writer
      // to include the expected function in the script.
      printf("The script must have the function 'void main()'. Please add it and try again.\n");
    }

    // Create our context, prepare it, and then execute
    asIScriptContext *ctx = engine->CreateContext();
    ctx->Prepare(func);
     r = ctx->Execute();
    if( r != asEXECUTION_FINISHED ){
      // The execution didn't complete as expected. Determine what happened.
      if( r == asEXECUTION_EXCEPTION ){
        // An exception occurred, let the script writer know what happened so it can be corrected.
        printf("An exception '%s' occurred. Please correct the code and try again.\n", ctx->GetExceptionString());
      }
    }
    // Clean up
    ctx->Release();
    engine->ShutDownAndRelease();
    return 0;
}
