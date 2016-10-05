//asynchronous node js cpp addon

#include <node.h>
#include <uv.h>
#include <iostream>
#include <Windows.h>

using namespace std;

namespace nodetalks {

        using v8::Function;
        using v8::FunctionCallbackInfo;
        using v8::Isolate;
        using v8::Local;
        using v8::Object;
        using v8::String;
        using v8::Value;
        using v8::Persistent;

        struct Work {
            uv_work_t request; //libuv at work, thread pool work scheduling, work request type
            Persistent<Function> callback;
            string result;
        };

        static void WorkAsync(uv_work_t *req){
            Work *work = static_cast<Work *>(req->data);
            Sleep(4000);
            work->result = "The async operation is comp(l)ete";
        }

        static void WorkAsyncComplete(uv_work_t *req, int status){

            Isolate* isolate = Isolate::GetCurrent();
            v8::HandleScope handleScope(isolate);
            Work *work = static_cast<Work *>(req->data);

            const char *result = work->result.c_str();

            Local<Value> argv[1] = { String::NewFromUtf8(isolate, result)};

            Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 1, argv);

            work->callback.Reset();

            delete work;
        }

        void ExecuteTaskAsync(const FunctionCallbackInfo<Value>&args){

            Isolate * isolate = args.GetIsolate();
            Work * work = new Work();
            work->request.data = work;

            Local<Function> callback = Local<Function>::Cast(args[0]);
            work->callback.Reset(isolate, callback);

            //libuv library starts worker thread
            //uv_queue_work initializes a work request which will run the given
            //workasync in a thread from the threadpool. once workasync has completed
            //workasynccomplete will be called on the loop thread
            uv_queue_work(uv_default_loop(), &work->request, WorkAsync, WorkAsyncComplete);
            args.GetReturnValue().Set(Undefined(isolate));

        }

        void init(Local<Object> exports){
            NODE_SET_METHOD(exports, "executeTaskAsync", ExecuteTaskAsync);
        }

        NODE_MODULE(addon, init)



}
