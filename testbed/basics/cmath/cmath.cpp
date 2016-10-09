#include <node.h>
using namespace v8;

void Add(const FunctionCallbackInfo<Value>& args){
    Isolate * isolate = args.GetIsolate();
    if (args.Length() < 2){
        return;
    }
    double value = args[0]->NumberValue() + args[1]->NumberValue();
    Local<Number> num = Number::New(isolate, value);
    args.GetReturnValue().Set(num);
}
void Multiply(const FunctionCallbackInfo<Value>& args){
    Isolate * isolate = args.GetIsolate();
    if (args.Length() < 2){
        return;
    }
    double value = args[0]->NumberValue() * args[1]->NumberValue();
    Local<Number> num = Number::New(isolate, value);
    args.GetReturnValue().Set(num);
}
void Divide(const FunctionCallbackInfo<Value>& args){
    Isolate * isolate = args.GetIsolate();
    if (args.Length() < 2){
        return;
    }
    double value = args[0]->NumberValue() / args[1]->NumberValue();
    Local<Number> num = Number::New(isolate, value);
    args.GetReturnValue().Set(num);
}
void Subtract(const FunctionCallbackInfo<Value>& args){
    Isolate * isolate = args.GetIsolate();
    if (args.Length() < 2){
        return;
    }
    double value = args[0]->NumberValue() - args[1]->NumberValue();
    Local<Number> num = Number::New(isolate, value);
    args.GetReturnValue().Set(num);
}



void Init(Local<Object> exports){
    NODE_SET_METHOD(exports, "add", Add);
    NODE_SET_METHOD(exports, "multiply", Multiply);
    NODE_SET_METHOD(exports, "divide", Divide);
    NODE_SET_METHOD(exports, "subtract", Subtract);
}

NODE_MODULE(addon, Init)