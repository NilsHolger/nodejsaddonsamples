//myobject.cpp here we implement the various methods to be exposed, the method timestwo() is exposed
//by adding it to the constructors prototype

#include "myobject.h"

namespace wrappingcppobjects {

        using v8::Context;
        using v8::Function;
        using v8::FunctionCallbackInfo;
        using v8::FunctionTemplate;
        using v8::Isolate;
        using v8::Local;
        using v8::Number;
        using v8::Object;
        using v8::Persistent;
        using v8::String;
        using v8::Value;

        Persistent<Function> MyObject::constructor;

        MyObject::MyObject(double value) : value_(value){}

        MyObject::~MyObject(){}

        void MyObject::Init(Local<Object> exports){
            Isolate * isolate = exports->GetIsolate();

            //prepare constructor template
            Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
            tpl->SetClassName(String::NewFromUtf8(isolate, "MyObject"));
            tpl->InstanceTemplate()->SetInternalFieldCount(1);

            //prototype
            NODE_SET_PROTOTYPE_METHOD(tpl, "timesTwo", TimesTwo);

            constructor.Reset(isolate, tpl->GetFunction());
            exports->Set(String::NewFromUtf8(isolate, "MyObject"), tpl->GetFunction());

        }

        void MyObject::New(const FunctionCallbackInfo<Value>&args){
            Isolate * isolate = args.GetIsolate();

            if (args.IsConstructCall()){
                //invoked as a constructor: `new MyObject(...)`
                double value = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
                MyObject* obj = new MyObject(value);
                obj->Wrap(args.This());
                args.GetReturnValue().Set(args.This());
            } else {
                //invoked as plain function `MyObject(...)`, turn into construct call
                const int argc = 1;
                Local<Value> argv[argc] = { args[0] };
                Local<Context> context = isolate->GetCurrentContext();
                Local<Function> cons = Local<Function>::New(isolate, constructor);
                Local<Object> result =
                cons->NewInstance(context, argc, argv).ToLocalChecked();
                args.GetReturnValue().Set(result);
            }
        }

        void MyObject::NewInstance(const FunctionCallbackInfo<Value>& args){
                Isolate * isolate = args.GetIsolate();

                const unsigned argc = 1;
                Local<Value> argv[argc] = { args[0] };
                Local<Function> cons = Local<Function>::New(isolate, constructor);
                Local<Context> context = isolate->GetCurrentContext();
                Local<Object> instance = cons->NewInstance(context, argc, argv).ToLocalChecked();
                args.GetReturnValue().Set(instance); 

        }

        void MyObject::TimesTwo(const FunctionCallbackInfo<Value>&args){
                Isolate * isolate = args.GetIsolate();

                MyObject* obj = ObjectWrap::Unwrap<MyObject>(args.Holder());
                obj->value_ *= 2;

                args.GetReturnValue().Set(Number::New(isolate, obj->value_));

        }

}