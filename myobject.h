//myobject.h => the wrapper class inherits from node:ObjectWrap
#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <node.h>
#include <node_object_wrap.h>

namespace wrappingcppobjects {

    class MyObject: public node::ObjectWrap {
        public:
         static void Init(v8::Local<v8::Object> exports);
         static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);
         inline double value() const { return value_; }

         private:
         explicit MyObject(double value = 0);
         ~MyObject();

         static void New(const v8::FunctionCallbackInfo<v8::Value>&args);
         static void TimesTwo(const v8::FunctionCallbackInfo<v8::Value>&args);
         static v8::Persistent<v8::Function> constructor;
         double value_;
    };
}

#endif