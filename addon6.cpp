//addon6.cpp wrap C++ objects/classes to allow new instances to be created using JavaScript new operator

#include <node.h>
#include "myobject.h"

namespace wrappingcppobjects {

    using v8::Local;
    using v8::Object;

    void InitAll(Local<Object> exports){
            MyObject::Init(exports);
    }

    NODE_MODULE(addon, InitAll)

}