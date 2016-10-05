//addon.cpp
//read function arguments passed in from javascript, return a result

#include <node.h>
namespace nodetalks {

            using v8::Exception;
            using v8::FunctionCallbackInfo;
            using v8::Isolate;
            using v8::Local;
            using v8::Number;
            using v8::Object;
            using v8::String;
            using v8::Value;

//this is implementation of multiply method
//input arguments are passed using the
//const FunctionCallbackInfo<Value>& args struct

void Multiply(const FunctionCallbackInfo<Value>& args){
            Isolate * isolate = args.GetIsolate();

            //check number of arguments passed
            if (args.Length() < 2){
                //throw an error that is passed back to javascript
                isolate->ThrowException(Exception::TypeError(
                    String::NewFromUtf8(isolate, "You must provide 2 arguments")));
                return;
            }

            //check argument types
            if (!args[0]->IsNumber() || !args[1]-> IsNumber()){
                isolate->ThrowException(Exception::TypeError(
                    String::NewFromUtf8(isolate, "You must enter numbers")));
            }

            //perform the operation
            double value = args[0]->NumberValue() * args[1]->NumberValue();
            Local<Number> num = Number::New(isolate, value);

            //set return value using passed in
            //FunctionCallbackInfo<Value>& args
            args.GetReturnValue().Set(num);

    }

    void Init(Local<Object> exports){
        NODE_SET_METHOD(exports, "multiply", Multiply);
    }

    NODE_MODULE(addon, Init)

}