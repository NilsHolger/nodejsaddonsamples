#include <nan.h>

using namespace Nan;
using namespace v8;
using namespace std;



NAN_METHOD(LoginSync){
    v8::String::Utf8Value user(info[0]->ToString());
    std::string userstr(*user);
    v8::String::Utf8Value password(info[1]->ToString());
    std::string passwordstr(*password);
    std::string response = "not authorized";
    if (userstr == "sexy" && passwordstr == "code"){
    response = "authorized";
    }
    Callback * callback = new Callback(info[2].As<Function>());
    Local<Value> lv[] = {Nan::New<v8::String>(response).ToLocalChecked()};
    callback->Call(1, lv);
}

class LoginWorker : public AsyncWorker {
public:
LoginWorker(Callback * callback, string user, string password)
: AsyncWorker(callback), user(user), password(password) {
}
// Executes in worker thread, invoke C++ API Here, here is lib_uv under the covers
void Execute() {
    response = "not authorized too bad try again.";
    if (user == "sexy" && password == "code"){
    response = "authorized for your eyes only ...";
    }
}
// Executes in event loop
void HandleOKCallback () {
Local<Value> lv[] = {Nan::New<v8::String>(response).ToLocalChecked()};
callback->Call(1, lv);
}
private:
string user;
string password;
string response;
};

NAN_METHOD(LoginAsync){
    v8::String::Utf8Value user(info[0]->ToString());
    string userstr(*user);
    v8::String::Utf8Value password(info[1]->ToString());
    string passwordstr(*password);
    Callback *callback = new Callback(info[2].As<Function>());
    AsyncQueueWorker(new LoginWorker(callback, userstr, passwordstr));
}

NAN_MODULE_INIT(init){
    Nan::Set(target, New<String>("loginsync").ToLocalChecked(), GetFunction(New<FunctionTemplate>(LoginSync))
    .ToLocalChecked());
    Nan::Set(target, New<String>("loginasync").ToLocalChecked(), GetFunction(New<FunctionTemplate>(LoginAsync))
    .ToLocalChecked());
}

NODE_MODULE(addon, init)