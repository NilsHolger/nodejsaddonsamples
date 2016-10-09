//hello.cpp

#include <node.h>

using namespace v8;

void Method(const FunctionCallbackInfo<Value>& args){
    Isolate * isolate = args.GetIsolate();
    Local<String> retVal = String::NewFromUtf8(isolate, "good morning => improve, improve, improve");
    args.GetReturnValue().Set(retVal);
}

void init(Local<Object> exports){
    NODE_SET_METHOD(exports, "greet", Method);
}

NODE_MODULE(addon, init)