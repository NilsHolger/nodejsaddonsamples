//addon5.cpp => create javascript functions that wrap c++ functions and return them back to javascript

#include<node.h>

namespace functionfactory {

        using v8::Function;
        using v8::FunctionCallbackInfo;
        using v8::FunctionTemplate;
        using v8::Isolate;
        using v8::Local;
        using v8::Object;
        using v8::String;
        using v8::Value;

        void MyFunction(const FunctionCallbackInfo<Value>&args){
            Isolate * isolate = args.GetIsolate();
            args.GetReturnValue().Set(String::NewFromUtf8(isolate, "Linus you were right.Open Source has won.God bless you."));
        }

        void CreateFunction(const FunctionCallbackInfo<Value>&args){
            Isolate * isolate = args.GetIsolate();

            Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, MyFunction);
            Local<Function> fn = tpl->GetFunction();

            //omit this to make it anonymous
            fn->SetName(String::NewFromUtf8(isolate, "The Function"));
            args.GetReturnValue().Set(fn);
        }

        void Init(Local<Object> exports, Local<Object> module){
            NODE_SET_METHOD(module, "exports", CreateFunction);
        }
        NODE_MODULE(addon, Init)
}
