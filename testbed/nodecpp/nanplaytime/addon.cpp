#include <nan.h>

using namespace Nan;
using namespace v8;

NAN_METHOD(PassNumber) {
    double value = info[0]->NumberValue();
    if (info.Length() < 1){
        info.GetReturnValue().Set(Nan::New(0));
        return;
    }
    if (!info[0]->IsNumber()){
        info.GetReturnValue().Set(Nan::New(-1));
        return;
    }
    Local<Number> retVal = Nan::New(value + 100);
    info.GetReturnValue().Set(retVal);
}

NAN_METHOD(PassInteger){
    int value = info[0]->IntegerValue();
    if (info.Length() < 1){
        info.GetReturnValue().Set(Nan::New(0));
        return;
    }
    if (!info[0]->IsInt32()){
        info.GetReturnValue().Set(Nan::New(-1));
        return;
    }
    Local<Integer> retVal = Nan::New(value +100);
    info.GetReturnValue().Set(retVal);
}

NAN_METHOD(PassBoolean){
    bool value = info[0]->BooleanValue();
    if (info.Length() < 1){
        info.GetReturnValue().Set(Nan::New(0));
        return;
    }
    if (!info[0]->IsBoolean()){
        info.GetReturnValue().Set(Nan::New(-1));
        return;
    }
    Local<Boolean> retVal = Nan::New(!value);
    info.GetReturnValue().Set(retVal);
}

NAN_METHOD(PassString){
    if (info.Length() < 1){
        info.GetReturnValue().Set(Nan::New<v8::String>("Enter a value").ToLocalChecked());
        return;
    }
    if (!info[0]->IsString()){
        info.GetReturnValue().Set(Nan::New<v8::String>("You must provide me a string").ToLocalChecked());
        return;
    }
    // Nan::MaybeLocal<String> tmp = Nan::To<String>(info[0]);
    // Local<String> local_string = tmp.ToLocalChecked();
    // Nan::Utf8String val(local_string);
    //more convenient way of getting Utf8 String from info object in 1 line
    v8::String::Utf8Value val(info[0]->ToString());
    std::string str(*val);
    std::reverse(str.begin(), str.end());
    info.GetReturnValue().Set(Nan::New<String>(str.c_str()).ToLocalChecked());
}

Local<Value> make_return(const Local<Object> input){
    Local<String> x_prop = Nan::New<String>("x").ToLocalChecked();
    Local<String> y_prop = Nan::New<String>("y").ToLocalChecked();
    Local<String> prod_prop = Nan::New<String>("product").ToLocalChecked();
    Local<String> sum_prop = Nan::New<String>("sum").ToLocalChecked();
    Local<String> divide_prop = Nan::New<String>("division").ToLocalChecked();
    Local<String> subtract_prop = Nan::New<String>("subtraction").ToLocalChecked();
    double x = input->Get(x_prop)->NumberValue();
    double y = input->Get(y_prop)->NumberValue();

    Local<Object> obj = Nan::New<Object>();
    obj->Set(prod_prop, Nan::New<Number>(x * y));
    obj->Set(sum_prop, Nan::New<Number>(x + y));
    obj->Set(divide_prop, Nan::New<Number>(x / y));
    obj->Set(subtract_prop, Nan::New<Number>(x - y));
    return obj;
}


NAN_METHOD(PassObject){
    if (info.Length() > 0){
        Local<Object> target = info[0]->ToObject();
        Local<Value> obj = make_return(target);
        info.GetReturnValue().Set(obj);
    }
}

NAN_METHOD(IncrementArray){
    Local<Array> array = Local<Array>::Cast(info[0]);
    for (unsigned int i = 0; i < array->Length(); i++){
        if (Nan::Has(array, i).FromJust()){
            double value = Nan::Get(array, i).ToLocalChecked()->NumberValue();
            Nan::Set(array, i, Nan::New<Number>(value + 100));
        }
    }
    Local<Array> a = New<v8::Array>(3);
    Nan::Set(a, 0, Nan::Get(array, 0).ToLocalChecked());
    Nan::Set(a, 1, Nan::Get(array, 1).ToLocalChecked());
    Nan::Set(a, 2, Nan::Get(array, 2).ToLocalChecked());
    info.GetReturnValue().Set(a);
}
NAN_MODULE_INIT(init){
    Nan::Set(target, New<String>("passnumber").ToLocalChecked(), GetFunction(New<FunctionTemplate>(PassNumber))
            .ToLocalChecked());
    Nan::Set(target, New<String>("passinteger").ToLocalChecked(), GetFunction(New<FunctionTemplate>(PassInteger))
            .ToLocalChecked()); 
    Nan::Set(target, New<String>("passboolean").ToLocalChecked(), GetFunction(New<FunctionTemplate>(PassBoolean))
            .ToLocalChecked());     
    Nan::Set(target, New<String>("passtring").ToLocalChecked(), GetFunction(New<FunctionTemplate>(PassString))
            .ToLocalChecked());
    Nan::Set(target, New<String>("passobject").ToLocalChecked(), GetFunction(New<FunctionTemplate>(PassObject))
            .ToLocalChecked());
    Nan::Set(target, New<String>("incrementarray").ToLocalChecked(), GetFunction(New<FunctionTemplate>(IncrementArray))
            .ToLocalChecked());
}

NODE_MODULE(addon, init)