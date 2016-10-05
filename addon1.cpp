//pass javascript function to c++ and execute it there

//addon1.cpp
#include <node.h>

namespace noderocks {

    using v8::Function;
    using v8::FunctionCallbackInfo;
    using v8::Isolate;
    using v8::Local;
    using v8::Null;
    using v8::Object;
    using v8::String; //she has a sexy v8 string
    using v8::Value;

    void ExecuteCallback(const FunctionCallbackInfo<Value>& args){
        Isolate* isolate = args.GetIsolate();
        Local<Function> cb = Local<Function>::Cast(args[0]);
        const unsigned argc = 1;
        Local<Value> argv[argc] = { String::NewFromUtf8(isolate, "Node and V8 Rock Da House")};
        cb->Call(Null(isolate), argc, argv);
    }

    void Init(Local<Object> exports, Local<Object> module){
        NODE_SET_METHOD(module, "exports", ExecuteCallback );
    }

    NODE_MODULE(addon, Init)





}