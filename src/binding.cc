#include "v8.h"
#include "node.h"
#include "node_pointer.h"
#include "mpg123.h"

using namespace v8;
using namespace node;

namespace {
#define CONST_INT(value) \
  target->ForceSet(NanNew<v8::String>(#value), NanNew<v8::Integer>(value), \
      static_cast<PropertyAttribute>(ReadOnly|DontDelete));

  NAN_METHOD(node_mpg123_volume) {
    NanScope();
    mpg123_handle *mh = UnwrapPointer<mpg123_handle *>(args[0]);
    double vol = args[1]->NumberValue();
    int ret = mpg123_volume(mh, vol);
    NanReturnValue(NanNew<v8::Integer>(ret));
  }

  NAN_METHOD(node_mpg123_getvolume) {
    NanScope();
    mpg123_handle *mh = UnwrapPointer<mpg123_handle *>(args[0]);

    double base;
    int ret = mpg123_getvolume(mh, &base, NULL, NULL);

    if (ret == MPG123_OK) {
      NanReturnValue(NanNew<v8::Number>(base));
    } else {
      NanThrowError(mpg123_plain_strerror(ret), ret);
    }
  }

  void Initialize(Handle<Object> target) {
    NanScope();

    NODE_SET_METHOD(target, "mpg123_volume", node_mpg123_volume);
    NODE_SET_METHOD(target, "mpg123_getvolume", node_mpg123_getvolume);
  }
} // anonymous namespace

NODE_MODULE(binding, Initialize)
