
/*
 * Helper functions for treating node Buffer instances as C "pointers".
 */

#include "v8.h"
#include "nan.h"
#include "node_buffer.h"

//NAN 2.x compat: -DJ
//other modules used as example
//#define NanNewBufferHandle  Nan::NewBuffer
#define NanNewBufferHandle(ptr, len, cb, data)  Nan::CopyBuffer(ptr, len).ToLocalChecked()
//#define v8_Handle  v8::Handle
#define v8_Handle  Nan::MaybeLocal


/*
 * Called when the "pointer" is garbage collected.
 */

inline static void wrap_pointer_cb(char *data, void *hint) {
  //fprintf(stderr, "wrap_pointer_cb\n");
}

/*
 * Wraps "ptr" into a new SlowBuffer instance with size "length".
 */

inline static v8_Handle<v8::Value> WrapPointer(void *ptr, size_t length) {
  void *user_data = NULL;
  return NanNewBufferHandle((char *)ptr, length, wrap_pointer_cb, user_data);
}

/*
 * Wraps "ptr" into a new SlowBuffer instance with length 0.
 */

inline static v8_Handle<v8::Value> WrapPointer(void *ptr) {
  return WrapPointer((char *)ptr, 0);
}

/*
 * Unwraps Buffer instance "buffer" to a C `char *` with the offset specified.
 */

inline static char * UnwrapPointer(v8::Handle<v8::Value> buffer, int64_t offset = 0) {
  if (node::Buffer::HasInstance(buffer)) {
    return node::Buffer::Data(buffer.As<v8::Object>()) + offset;
  } else {
    return NULL;
  }
}

/**
 * Templated version of UnwrapPointer that does a reinterpret_cast() on the
 * pointer before returning it.
 */

template <typename Type>
inline static Type UnwrapPointer(v8::Handle<v8::Value> buffer) {
  return reinterpret_cast<Type>(UnwrapPointer(buffer));
}
