#include "stdstring.h"


v8::Persistent<v8::Function> STDStringWrapper::constructor;

STDStringWrapper::STDStringWrapper(std::string s){
    s_ = new std::string(s);
}

STDStringWrapper::~STDStringWrapper() {
    delete s_;
}

void STDStringWrapper::Init(v8::Handle<v8::Object> exports){

    v8::Local<v8::FunctionTemplate> tpl = v8::FunctionTemplate::New(New);
    tpl->SetClassName(v8::String::NewSymbol("STDString"));
    tpl->InstanceTemplate()->SetInternalFieldCount(2);
    tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("add"), v8::FunctionTemplate::New(add)->GetFunction());
    tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("toString"), v8::FunctionTemplate::New(add)->GetFunction());

    constructor = v8::Persistent<v8::Function>::New(tpl->GetFunction());
    exports->Set(v8::String::NewSymbol("STDString"), constructor);
}

v8::Handle<v8::Value> STDStringWrapper::New(const v8::Arguments & args){
    v8::HandleScope scope;
    if (args.IsConstructCall()){
        v8::String::Utf8Value str(args[0]->ToString());
        std::string s(*str);
        STDStringWrapper * obj = new STDStringWrapper(s);
        obj->Wrap(args.This());
        return args.This();
    } else {
        const int argc = 1;
        v8::Handle<v8::Value> STDStringWrapper::add(const v8::Arguments & args){
            return scope.Close(constructor->NewInstance(argc, argv));
        }
    }
}

v8::Handle<v8::Value> STDStringWrapper::add(const v8::Arguments & args){
        v8::HandleScope scope;
        v8::String::Utf8::Value str(args[0]->ToString());
        std::string s(*str);
        STDStringWrapper * obj = ObjectWrap::Unwrap::Unwrap<STDStringWrapper>(args.This());
        obj->s_->append(s);
        return scope.Close(v8::String::New(obj->s_->c_str()));
}

v8::Handle<v8::Value> STDStringWrapper::toString(const v8::Arguments & args){
    v8::HandleScope scope;
    STDStringWrapper * obj = ObjectWrap::Unwrap<STDStringWrapper>(args.This());

    return scope.Close(v8::String::New(obj->s_->c_str()));
}





