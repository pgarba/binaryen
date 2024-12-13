/*
 * Copyright 2015 WebAssembly Community Group participants
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "asm_v_wasm.h"
#include "support/utilities.h"
#include "wasm.h"

namespace wasm {

JsType wasmToJsType(Type type) {
  if (type.isRef()) {
    return JS_REF;
  }

  TODO_SINGLE_COMPOUND(type);
  switch (type.getBasic()) {
    case Type::i32:
      return JS_INT;
    case Type::f32:
      return JS_FLOAT;
    case Type::f64:
      return JS_DOUBLE;
    case Type::i64:
      return JS_INT64;
    case Type::v128:
      WASM_UNREACHABLE("v128 not implemented yet");
    case Type::none:
      return JS_NONE;
    case Type::unreachable:
      WASM_UNREACHABLE("invalid type");
  }
  WASM_UNREACHABLE("invalid type");
}

CType wasmToCType(Type type) {
  if (type.isRef()) {
    return CTYPE_REF;
  }

  TODO_SINGLE_COMPOUND(type);
  switch (type.getBasic()) {
    case Type::i32:
      return CTYPE_INT;
    case Type::f32:
      return CTYPE_FLOAT;
    case Type::f64:
      return CTYPE_DOUBLE;
    case Type::i64:
      return CTYPE_INT64;
    case Type::v128:
      WASM_UNREACHABLE("v128 not implemented yet");
    case Type::none:
      return CTYPE_NONE;
    case Type::unreachable:
      WASM_UNREACHABLE("invalid type");
  }
  WASM_UNREACHABLE("invalid type");
}

IString getCType(CType type, bool isStatic, bool isConstant) {
  std::string ret;

  switch (type) {
    case CTYPE_INT:
      ret = "int";
      break;
    case CTYPE_DOUBLE:
      ret = "double";
      break;
    case CTYPE_FLOAT:
      ret = "float";
      break;
    case CTYPE_FLOAT32X4:
      ret = "float32x4";
      break;
    case CTYPE_FLOAT64X2:
      ret = "float64x2";
      break;
    case CTYPE_INT8X16:
      ret = "int8x16";
      break;
    case CTYPE_INT16X8:
      ret = "int16x8";
      break;
    case CTYPE_INT32X4:
      ret = "int32x4";
      break;
    case CTYPE_INT64:
      ret = "int64";
      break;
    case CTYPE_REF:
      ret = "ref";
      break;
    case CTYPE_NONE:
      ret = "void";
      break;
    default:
      WASM_UNREACHABLE("invalid type");
      break;
  }

  if (isConstant) {
    ret = "const " + ret;
  }

  if (isStatic) {
    ret = "static " + ret;
  }

  return IString(ret);
}

char getSig(Type type) {
  TODO_SINGLE_COMPOUND(type);
  switch (type.getBasic()) {
    case Type::i32:
      return 'i';
    case Type::i64:
      return 'j';
    case Type::f32:
      return 'f';
    case Type::f64:
      return 'd';
    case Type::v128:
      return 'V';
    case Type::none:
      return 'v';
    case Type::unreachable:
      WASM_UNREACHABLE("invalid type");
  }
  WASM_UNREACHABLE("invalid type");
}

std::string getSig(Type results, Type params) {
  assert(!results.isTuple());
  std::string sig;
  sig += getSig(results);
  for (const auto& param : params) {
    sig += getSig(param);
  }
  return sig;
}

} // namespace wasm
