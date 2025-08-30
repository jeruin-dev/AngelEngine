#ifndef ANGELENGINE_H
#define ANGELENGINE_H

#include <scriptbuilder/scriptbuilder.h>
#include <angelscript.h>
#include <fmt/base.h>
#include <assert.h>


class AngelEngine{
    private:

        CScriptBuilder builder;
        asIScriptContext *ctx;
        void FnControl(int result , const char *msg);


    public:
         asIScriptEngine *engine;
        AngelEngine();

        ~AngelEngine();

        static void MessageCallback(const asSMessageInfo *msg, void *param);
        template<typename T>
        void RegisterFunction(const char *decharation, T func);

        void RegisterModule(const char *name , const char *path);

        void BuildModule();

        void run(const char *module, const char *FuncByDecl);

        void registerstd(asIScriptEngine *engine);

};
#endif
