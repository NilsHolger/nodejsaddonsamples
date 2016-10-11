#include <node.h>
#include <v8.h>
#include "results.h"

using namespace v8;

sample unpack_sample(Isolate * isolate, const Handle<Object> sample_obj){
        sample s;
        Handle<Value> month_Value = sample_obj->Get(String::NewFromUtf8(isolate, "month"));
        Handle<Value> results_Value = sample_obj->Get(String::NewFromUtf8(isolate, "results"));

        v8::String::Utf8Value utfValue(month_Value);
        s.month = std::string(*utfValue);

        s.results = results_Value->NumberValue();

        return s;
}

location unpack_location(Isolate * isolate, const v8::FunctionCallbackInfo<v8::Value>& args){
        location loc;
        Handle<Object> location_obj = Handle<Object>::Cast(args[0]);
        Handle<Value> country_Value = location_obj->Get(String::NewFromUtf8(isolate, "country"));

        v8::String::Utf8Value utfValue(country_Value);
        loc.country = std::string(*utfValue);

        Handle<Array> array = Handle<Array>::Cast(location_obj->Get(String::NewFromUtf8(isolate, "samples")));

        int sample_count = array->Length();
        for (int i = 0; i < sample_count; i++){
            sample s = unpack_sample(isolate, Handle<Object>::Cast(array->Get(i)));
            loc.samples.push_back(s);
        }
        return loc;
}




void AvgSales(const v8::FunctionCallbackInfo<v8::Value>& args){
        Isolate * isolate = args.GetIsolate();

        location loc = unpack_location(isolate, args);
        double avg = avg_sales(loc);


        Local<Number> retVal = v8::Number::New(isolate, avg);
        args.GetReturnValue().Set(retVal);
}




void init(Handle<Object> exports, Handle<Object> module){
    NODE_SET_METHOD(exports, "avg_sales", AvgSales);
}

NODE_MODULE(results, init)
