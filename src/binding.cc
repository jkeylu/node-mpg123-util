#include "v8.h"
#include "node.h"
#include "node_pointer.h"
#include "mpg123.h"

using namespace v8;
using namespace node;

namespace {
#define CONST_INT(value) \
  Nan::ForceSet(target, Nan::New(#value).ToLocalChecked(), Nan::New(value), \
      static_cast<PropertyAttribute>(ReadOnly|DontDelete));

  NAN_METHOD(node_mpg123_volume) {
    Nan::HandleScope scope;
    mpg123_handle *mh = UnwrapPointer<mpg123_handle *>(info[0]);
    double vol = info[1]->NumberValue();
    int ret = mpg123_volume(mh, vol);
    info.GetReturnValue().Set(Nan::New<v8::Integer>(ret));
  }

  NAN_METHOD(node_mpg123_getvolume) {
    Nan::HandleScope scope;
    mpg123_handle *mh = UnwrapPointer<mpg123_handle *>(info[0]);

    double base;
    int ret = mpg123_getvolume(mh, &base, NULL, NULL);

    if (ret == MPG123_OK) {
      info.GetReturnValue().Set(Nan::New<v8::Number>(base));
    } else {
      Nan::ThrowError(mpg123_plain_strerror(ret));
    }
  }

  void Initialize(Handle<Object> target) {
    Nan::HandleScope scope;

    Nan::SetMethod(target, "mpg123_volume", node_mpg123_volume);
    Nan::SetMethod(target, "mpg123_getvolume", node_mpg123_getvolume);
  }
} // anonymous namespace

NODE_MODULE(binding, Initialize)
