#ifndef STDSTRING_H
#define STDSTRING_H

#include <string>
#include <node.h>

class STDStringWrapper : public node::ObjectWrap {

public:
    static void Init(v8::Handle<v8::Object> exports); 

private:
    std::string * s_;
    explicit STDStringWrapper(std::string s = "");
    ~STDStringWrapper();
    
    static v8::Handle<v8::Value> New(const v8::Arguments& args);
    static v8::Handle New(const v8::Arguments& args);
    static v8::Handle<v8::Value> add(const v8::Arguments& args);
    static v8::Handle<v8::Value> toString(const v8::Arguments& args);
};

#endif