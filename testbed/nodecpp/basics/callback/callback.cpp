#include <node.h>
using namespace v8;

void CallThis(const FunctionCallbackInfo<Value> & args){
    Isolate * isolate = args.GetIsolate();
    Local<Function> cb = Local<Function>::Cast(args[0]);
    cb->Call(Null(isolate), 0, nullptr);
    return; //returns undefined to javascript
}

void CallThisWithThis(const FunctionCallbackInfo<Value> & args){
    Isolate * isolate = args.GetIsolate();
    Local<Function> cb = Local<Function>::Cast(args[0]);

    //create an array with only the argument passed in the message
    Local<Value> argv[1] = {args[1]};
    cb->Call(Null(isolate), 1, argv);
    return;
}

void Mutate(const FunctionCallbackInfo<Value> & args){
    Isolate * isolate = args.GetIsolate();
    Local<Object> target = args[0]->ToObject();
    target->Set(String::NewFromUtf8(isolate, "x"), Number::New(isolate, 100));
    args.GetReturnValue().Set(target);
}

void init(Local<Object> exports){
    NODE_SET_METHOD(exports, "callthis", CallThis);
    NODE_SET_METHOD(exports, "callthis_withthis", CallThisWithThis);
    NODE_SET_METHOD(exports, "mutate", Mutate);
}

NODE_MODULE(addon, init)