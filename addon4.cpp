//addon4.cpp => object factory create and return new objects

#include <node.h>

namespace objectfactory {

        using v8::FunctionCallbackInfo;
        using v8::Isolate;
        using v8::Local;
        using v8::Object;
        using v8::String;
        using v8::Value;

        void CreateObject(const FunctionCallbackInfo<Value>&args){
            Isolate * isolate = args.GetIsolate();

            Local<Object> obj = Object::New(isolate);

            obj->Set(String::NewFromUtf8(isolate, "secretmsg"), args[0]->ToString());

            args.GetReturnValue().Set(obj);
        }

        void Init(Local<Object> exports, Local<Object> module){
            NODE_SET_METHOD(module, "exports", CreateObject);
        }

        NODE_MODULE(addon, Init)
}

