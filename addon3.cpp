#include <nan.h>

using namespace v8;

namespace noderocks {

void IsItaPalindrome(const FunctionCallbackInfo<Value>& info){
    
    String::Utf8Value sentence(info[0]->ToString());

    std::string str = std::string(*sentence);
    int len = str.length();
    int half = len / 2;
    int start = 0;
    int end = len - 1;
    int space = 32;
    bool isPal = true;

    while (half > 0 && isPal){
        bool startSpace = str.at(start) == space;
        bool endSpace = str.at(end) == space;

        if (str.at(start) == str.at(end)){
            startSpace && start++;
            endSpace && end--;
        } else {
            isPal = false;
        }
        half--;
    }
    info.GetReturnValue().Set(isPal);
}

    void init(Local<Object> exports){
        NODE_SET_METHOD(exports, "isItaPalindrome", IsItaPalindrome);
    }

    NODE_MODULE(addon, init)

}