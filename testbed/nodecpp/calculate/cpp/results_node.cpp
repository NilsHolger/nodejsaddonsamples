#include <node.h>
#include <v8.h>
#include "results.h"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>

using namespace v8;


void pack_country_result(v8::Isolate * isolate, v8::Local<v8::Object> & obj, country_result & result){
            obj->Set(
            String::NewFromUtf8(isolate, "mean"),
            Number::New(isolate, result.mean));
        obj->Set(
            String::NewFromUtf8(isolate, "median"),
            Number::New(isolate, result.median));
        obj->Set(
            String::NewFromUtf8(isolate, "standard_deviation"),
            Number::New(isolate, result.standard_deviation));
        obj->Set(
            String::NewFromUtf8(isolate, "n"),
            Integer::New(isolate, result.n));
}

sample unpack_sample(Isolate * isolate, const Handle<Object> sample_obj){
        sample s;
        Handle<Value> month_Value = sample_obj->Get(String::NewFromUtf8(isolate, "month"));
        Handle<Value> results_Value = sample_obj->Get(String::NewFromUtf8(isolate, "results"));

        v8::String::Utf8Value utfValue(month_Value);
        s.month = std::string(*utfValue);

        s.results = results_Value->NumberValue();

        return s;
}

location unpack_location(Isolate * isolate, const Handle<Object> location_obj){
        location loc;
        //Handle<Object> location_obj = Handle<Object>::Cast(args[0]);
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

void CountryData(const v8::FunctionCallbackInfo<v8::Value>&args){
        Isolate * isolate = args.GetIsolate();

        location loc = unpack_location(isolate, Handle<Object>::Cast(args[0]));
        country_result result = calc_country_stats(loc);

        //create a new object on the V8 heap
        Local<Object> obj = Object::New(isolate);
        //transfer the data from result to obj
        obj->Set(
            String::NewFromUtf8(isolate, "mean"),
            Number::New(isolate, result.mean));
        obj->Set(
            String::NewFromUtf8(isolate, "median"),
            Number::New(isolate, result.median));
        obj->Set(
            String::NewFromUtf8(isolate, "standard_deviation"),
            Number::New(isolate, result.standard_deviation));
        obj->Set(
            String::NewFromUtf8(isolate, "n"),
            Integer::New(isolate, result.n));
        //return the object
        args.GetReturnValue().Set(obj);                
}


void AvgSales(const v8::FunctionCallbackInfo<v8::Value>& args){
        Isolate * isolate = args.GetIsolate();
        location loc = unpack_location(isolate, Handle<Object>::Cast(args[0]));
        double avg = avg_sales(loc);
        Local<Number> retVal = v8::Number::New(isolate, avg);
        args.GetReturnValue().Set(retVal);
}

void CalculateResults(const v8::FunctionCallbackInfo<v8::Value>& args){
    Isolate * isolate = args.GetIsolate();
    std::vector<location> locations;
    std::vector<country_result> results;

    Local<Array> input = Local<Array>::Cast(args[0]);
    unsigned int num_locations = input->Length();

    for (unsigned int i = 0; i < num_locations; i++){
        locations.push_back(unpack_location(isolate, Local<Object>::Cast(input->Get(i))));
    }

    results.resize(locations.size());
    std::transform(locations.begin(), locations.end(), results.begin(), calc_country_stats);

    Local<Array> result_list = Array::New(isolate);
    for (unsigned int i = 0; i < results.size(); i++){
        Local<Object> result = Object::New(isolate);
        pack_country_result(isolate, result, results[i]);
        result_list->Set(i, result);
    }
    args.GetReturnValue().Set(result_list);
}




void init(Handle<Object> exports, Handle<Object> module){
    NODE_SET_METHOD(exports, "avg_sales", AvgSales);
    NODE_SET_METHOD(exports, "data_country", CountryData);
    NODE_SET_METHOD(exports, "calculate_results", CalculateResults);
}

NODE_MODULE(results, init)
