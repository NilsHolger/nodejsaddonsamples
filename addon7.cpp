#include <cmath>
#include <nan.h>


void Power(const Nan::FunctionCallbackInfo<v8::Value>& info){


        if (info.Length() < 2){
            Nan::ThrowTypeError("You must enter 2 values");
            return;
        }

        if (!info[0]->IsNumber() || !info[1]->IsNumber()){
            Nan::ThrowTypeError("We only accept numbers");
            return;
        }

        double arg0 = info[0]->NumberValue();
        double arg1 = info[1]->NumberValue();

        v8::Local<v8::Number> num = Nan::New(pow(arg0, arg1));

        info.GetReturnValue().Set(num);        
}

void Init(v8::Local<v8::Object> exports){
    exports->Set(Nan::New("SuperPowers").ToLocalChecked(),
    Nan::New<v8::FunctionTemplate>(Power)->GetFunction());
}

NODE_MODULE(addon, Init)