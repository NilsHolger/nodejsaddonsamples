//hello.cpp

#include <node.h>

using namespace v8;

void Method(const FunctionCallbackInfo<Value>& args){
    args.GetReturnValue().Set(args.Holder());
}

void init(Local<Object> exports){
    NODE_SET_METHOD(exports, "greet", Method);
}

NODE_MODULE(addon, init)