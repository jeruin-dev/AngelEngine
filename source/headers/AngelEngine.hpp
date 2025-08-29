#ifndef ANGELENGINE_H
#define ANGELENGINE_H

#include "scriptbuilder/scriptbuilder.h"
#include <angelscript.h>
#include <fmt/base.h>
#include <assert.h>

class AngelEngine{
    private:
        asIScriptEngine *engine;
        CScriptBuilder builder;

    public:

        AngelEngine();

        ~AngelEngine();

        static void MessageCallback(const asSMessageInfo *msg, void *param);

        void RegisterFunction(const char *decharation, asSFuncPtr func);


        void RegisterModule(const char *name , const char *path);

};
#endif
