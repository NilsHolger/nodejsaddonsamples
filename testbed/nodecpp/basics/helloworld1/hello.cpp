#include <node.h>

using namespace v8; //you sexy V8 code

void Method(const FunctionCallbackInfo<Value>& args){
    Isolate * isolate = args.GetIsolate();
    Local<String> retVal = String::NewFromUtf8(isolate, "Nils");
    args.GetReturnValue().Set(retVal);
}

void init(Local<Object> exports){
    NODE_SET_METHOD(exports, "hello", Method);
}

NODE_MODULE(addon, init)