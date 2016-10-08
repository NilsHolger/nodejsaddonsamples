//addon6.cpp wrap C++ objects/classes to allow new instances to be created using JavaScript new operator

#include <node.h>
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

    void InitAll(Local<Object> exports){
            MyObject::Init(exports);

            NODE_SET_METHOD(exports, "createObject", CreateObject);

    }

    NODE_MODULE(addon, InitAll)

}