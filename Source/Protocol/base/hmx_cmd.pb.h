// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: hmx_cmd.proto

#ifndef PROTOBUF_hmx_5fcmd_2eproto__INCLUDED
#define PROTOBUF_hmx_5fcmd_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3000000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3000000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
// @@protoc_insertion_point(includes)

namespace hmx_cmd {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_hmx_5fcmd_2eproto();
void protobuf_AssignDesc_hmx_5fcmd_2eproto();
void protobuf_ShutdownFile_hmx_5fcmd_2eproto();


enum h_cmd {
  msg_login = 1,
  msg_role = 2
};
bool h_cmd_IsValid(int value);
const h_cmd h_cmd_MIN = msg_login;
const h_cmd h_cmd_MAX = msg_role;
const int h_cmd_ARRAYSIZE = h_cmd_MAX + 1;

const ::google::protobuf::EnumDescriptor* h_cmd_descriptor();
inline const ::std::string& h_cmd_Name(h_cmd value) {
  return ::google::protobuf::internal::NameOfEnum(
    h_cmd_descriptor(), value);
}
inline bool h_cmd_Parse(
    const ::std::string& name, h_cmd* value) {
  return ::google::protobuf::internal::ParseNamedEnum<h_cmd>(
    h_cmd_descriptor(), name, value);
}
// ===================================================================


// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace hmx_cmd

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::hmx_cmd::h_cmd> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::hmx_cmd::h_cmd>() {
  return ::hmx_cmd::h_cmd_descriptor();
}

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_hmx_5fcmd_2eproto__INCLUDED