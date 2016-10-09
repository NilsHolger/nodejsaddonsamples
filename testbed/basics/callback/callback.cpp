#include <node.h>
using namespace v8;

void CallThis(const FunctionCallbackInfo<Value>& args){
    Isolate * isolate = args.GetIsolate();
    Local<Function> cb = Local<Function>::Cast(args[0]);
    cb->Call(Null(isolate), 0, nullptr);
}

void CallThisWithThis(const FunctionCallbackInfo<Value>& args){
    Isolate * isolate = args.GetIsolate();
    Local<Function> cb = Local<Function>::Cast(args[0]);
    Local<Value> argv[1] = {args[1]};
    cb->Call(Null(isolate), 1, argv);
}

void init(Local<Object> exports){
    NODE_SET_METHOD(exports, "callthis", CallThis);
    NODE_SET_METHOD(exports, "callthiswiththis", CallThisWithThis);
}

NODE_MODULE(addon, init)