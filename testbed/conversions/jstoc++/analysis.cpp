#include <node.h>
#include <string> //you sexy string yum yum
#include <algorithm>
#include <iostream>


using namespace v8;

//FunctionCallbackInfo passed in from node.js runtime
void Mutate(const FunctionCallbackInfo<Value>& args){
    //get reference to current isolate => access anything from running javascript code
    Isolate * isolate = args.GetIsolate();
    //local is handle, args[0] is of type v8::Value top of inheritance chain
    //wrap v8 value in handle
    //handlescope container for a bunch of handles
    //handlescope automatically deleted by garbage collector when function terminates
    Local<Object> target = args[0]->ToObject();
    target->Set(
        String::NewFromUtf8(isolate, "x"),
        Number::New(isolate, 42));

        //V8 context deleted, provide return value to javascript
        args.GetReturnValue().Set(target);
}

void PassNumber(const FunctionCallbackInfo<Value>& args){
    Isolate * isolate = args.GetIsolate();
    //convert first argument passed to c++ into a number using ToNumber method on v8::Value
    Local<Number> target = args[0]->ToNumber();
    //value is now outside of V8 - we can use it in all the c++ standard ways
    double value = target->NumberValue();
    //modify c++ value by adding a fixed value to it
    value += 100;
    //create storage cell, pass isolate in new method, assign and allocate the value
    Local<Number> retVal = Number::New(isolate, value);
    args.GetReturnValue().Set(retVal);    
}

//take home v8 has mapped values to javascript counterparts
//return values for NAN, null and undefined are javascript standard
void PassNumberWithExceptionHandling(const FunctionCallbackInfo<Value>&args){
    Isolate * isolate = args.GetIsolate();
    //catch no input provided and return 0
    if (args.Length() < 1){
        args.GetReturnValue().Set(Number::New(isolate, 0));
        return;
    }
    //catch anything that isn't a number and return -1 or a string
    if (!args[0]->IsNumber()){
        args.GetReturnValue().Set(Number::New(isolate, -1));
        //return a string
        //args.GetReturnValue().Set(String::NewFromUtf8(isolate, "numbers only"));
        return;
    }
}

//api for converting V8 to C++ is similar to numbers
void PassBoolean(const FunctionCallbackInfo<Value>&args){
    Isolate * isolate = args.GetIsolate();
    bool value = args[0]->BooleanValue();
    if (args.Length() < 1){
        args.GetReturnValue().Set(String::NewFromUtf8(isolate, "enter a value"));
        return;
    }
    if (!args[0]->IsBoolean()){
        args.GetReturnValue().Set(String::NewFromUtf8(isolate, "booleans only"));
        return;
    }
    Local<Boolean> retVal = Boolean::New(isolate, !value);
    args.GetReturnValue().Set(retVal);
}

void PassString(const FunctionCallbackInfo<Value>& args){
    Isolate * isolate = args.GetIsolate();
    if (args.Length() < 1){
        args.GetReturnValue().Set(String::NewFromUtf8(isolate, "enter a value"));
        return;
    }
    if (!args[0]->IsString()){
        args.GetReturnValue().Set(String::NewFromUtf8(isolate, "strings only"));
        return;
    }

    //instantiate from input handle
    v8::String::Utf8Value s(args[0]);

    //dereference the instance and wrap in c++ string
    std::string str(*s);
    //reverse
    std::reverse(str.begin(), str.end());
    //create a new V8 string from char* and return the value
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, str.c_str()));
}

//this is an antipattern persisting state with a global object
Persistent<Object> persist;
int increment;
void Increment(const FunctionCallbackInfo<Value>& args){
    Isolate * isolate = args.GetIsolate();
    Local<Object> target = Local<Object>::New(isolate, persist);
    Local<String> prop = String::NewFromUtf8(isolate, "x");
    double x = target->Get(prop)->NumberValue();
    target->Set(prop, Number::New(isolate, x + increment));
}
void Initialize(const FunctionCallbackInfo<Value>& args){
    Isolate * isolate = args.GetIsolate();
    //set global variables, they survive returning from this call
    persist.Reset(isolate, args[0]->ToObject());
    increment = args[1]->NumberValue();
}




void init(Local<Object> exports){
    NODE_SET_METHOD(exports, "mutate", Mutate);
    NODE_SET_METHOD(exports, "passnumber", PassNumber);
    NODE_SET_METHOD(exports, "passnumberwithexceptionhandling", PassNumberWithExceptionHandling);
    NODE_SET_METHOD(exports, "passboolean", PassBoolean);
    NODE_SET_METHOD(exports, "passstring", PassString);
    NODE_SET_METHOD(exports, "increment", Increment);
    NODE_SET_METHOD(exports, "initialize", Initialize);
}

NODE_MODULE(addon, init)

