#include <node.h>
using namespace v8;


void Add(const FunctionCallbackInfo<Value>& args){

    Isolate * isolate = args.GetIsolate();

    if (args.Length() < 2){
        //returns undefined
        //return;
        //throws an exception to javascript
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }
    if (!args[0]->IsNumber() || !args[1]->IsNumber()){
        //return undefined
        //return;
        //throw an exception
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Numbers only")));
    }

    double value = args[0]->NumberValue() + args[1]->NumberValue();

    Local<Number> num = Number::New(isolate, value);
    args.GetReturnValue().Set(num);
}




void Init(Local<Object> exports){
    NODE_SET_METHOD(exports, "add", Add);
}

NODE_MODULE(addon, Init)