//addon6.cpp wrap C++ objects/classes to allow new instances to be created using JavaScript new operator

#include <node.h>
#include <node_object_wrap.h>
#include "myobject.h"

namespace wrappingcppobjects {

    using v8::Local;
    using v8::Object;
    using v8::FunctionCallbackInfo;
    using v8::Isolate;
    using v8::Number;
    using v8::String;
    using v8::Value;

    void CreateObject(const FunctionCallbackInfo<Value>& args){
        MyObject::NewInstance(args);
    }

    void Multiply(const FunctionCallbackInfo<Value>& args){
        Isolate * isolate = args.GetIsolate();

        MyObject* obj1 = node::ObjectWrap::Unwrap<MyObject>(
            args[0]->ToObject());
        MyObject* obj2 = node::ObjectWrap::Unwrap<MyObject>(
            args[1]->ToObject());

        double product = obj1->value() * obj2->value();
        args.GetReturnValue().Set(Number::New(isolate, product));
    }

    void InitAll(Local<Object> exports){
            MyObject::Init(exports);

            NODE_SET_METHOD(exports, "createObject", CreateObject);
            NODE_SET_METHOD(exports, "multiply", Multiply);

    }

    NODE_MODULE(addon, InitAll)

}