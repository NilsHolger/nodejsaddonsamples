#include <node.h>
#include <string>
#include <algorithm>
#include <iostream>

using namespace v8;

void PassNumber(const FunctionCallbackInfo<Value>& args){
    Isolate * isolate = args.GetIsolate();
    if (args.Length() < 1){
        args.GetReturnValue().Set(Number::New(isolate, 0));
        return;
    }
    //catches anything that isn't a number
    if (!args[0]->IsNumber()){
        args.GetReturnValue().Set(Number::New(isolate, -1));
        return;
    }
    Local<Number> target = args[0]->ToNumber();
    //value is out of V8 can be used in all standard C++ ways
    double value = target->NumberValue();
    value += 100;
    Local<Number> retVal = Number::New(isolate, value);
    args.GetReturnValue().Set(retVal);
}

void PassInteger(const FunctionCallbackInfo<Value>& args) {
    Isolate * isolate = args.GetIsolate();
    int value = args[0]->Int32Value();
    Local<Number> retVal = Int32::New(isolate, value);
    args.GetReturnValue().Set(retVal);
}

void PassBoolean(const FunctionCallbackInfo<Value>& args){
    Isolate * isolate = args.GetIsolate();
    bool value = args[0]->BooleanValue();
    Local<Boolean> retVal = Boolean::New(isolate, !value);
    args.GetReturnValue().Set(retVal);
}

void PassString(const FunctionCallbackInfo<Value>& args){
    Isolate * isolate = args.GetIsolate();
    v8::String::Utf8Value s(args[0]);

    //wrap it in a c++ string
    std::string str(*s);
    std::reverse(str.begin(), str.end());

    Local<String> retVal = String::NewFromUtf8(isolate, str.c_str());
    args.GetReturnValue().Set(retVal);
}

void PassObject(const FunctionCallbackInfo<Value>& args){
    Isolate * isolate = args.GetIsolate();
    Local<Object> target = args[0]->ToObject();
    Local<String> prop = String::NewFromUtf8(isolate, "x");
    double x = target->Get(prop)->NumberValue();
    target->Set(prop, Number::New(isolate, x + 100));
    args.GetReturnValue().Set(target);
}

void PassObjectFactory(const FunctionCallbackInfo<Value>& args){
    Isolate * isolate = args.GetIsolate();
    Local<Object> target = args[0]->ToObject();
    Local<String> x_prop = String::NewFromUtf8(isolate, "x");
    Local<String> y_prop = String::NewFromUtf8(isolate, "y");
    Local<String> sum_prop = String::NewFromUtf8(isolate, "sum");
    Local<String> product_prop = String::NewFromUtf8(isolate, "product");
    Local<String> divide_prop = String::NewFromUtf8(isolate, "divide");
    Local<String> subtract_prop = String::NewFromUtf8(isolate, "subtract");
    if (!target->Get(x_prop)->IsNumber()){
        target->Set(x_prop, Number::New(isolate, 1));
    } 
    if (!target->Get(y_prop)->IsNumber()){
        target->Set(y_prop, Number::New(isolate, 1));
    }
    double x = target->Get(x_prop)->NumberValue();
    double y = target->Get(y_prop)->NumberValue();
    //create new object to return to V8
    Local<Object> obj = Object::New(isolate);
    obj->Set(sum_prop, Number::New(isolate, x + y));
    obj->Set(product_prop, Number::New(isolate, x * y));
    obj->Set(divide_prop, Number::New(isolate, x / y));
    obj->Set(subtract_prop, Number::New(isolate, x - y));
    args.GetReturnValue().Set(obj);
}


void init(Local<Object> exports){
    NODE_SET_METHOD(exports, "passnumber", PassNumber);
    NODE_SET_METHOD(exports, "passinteger", PassInteger);
    NODE_SET_METHOD(exports, "passboolean", PassBoolean);
    NODE_SET_METHOD(exports, "passstring", PassString);
    NODE_SET_METHOD(exports, "passobject", PassObject);
    NODE_SET_METHOD(exports, "passobjectfactory", PassObjectFactory);

}


NODE_MODULE(addon, init)