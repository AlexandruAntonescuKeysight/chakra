#!/bin/bash
set -e

# set paths
SCRIPT_DIR=/home/tony/chakra_fork/chakra
BUILD_DIR="${SCRIPT_DIR:?}"/build
CHAKRA_ET_DIR="${SCRIPT_DIR:?}"/et_def

# set functions
function compile_chakra_et() {
  # compile et_def.proto if one doesn't exist
  if [[ ! -f "${CHAKRA_ET_DIR:?}"/et_def.pb.h || ! -f "${CHAKRA_ET_DIR:?}"/et_def.pb.cc ]]; then
    protoc et_def.proto \
      --proto_path="${CHAKRA_ET_DIR:?}" \
      --cpp_out="${CHAKRA_ET_DIR:?}"
  fi

#   if [[ ! -f "${CHAKRA_ET_DIR:?}"/et_def_pb2.py ]]; then
#     protoc et_def.proto \
#       --proto_path="${CHAKRA_ET_DIR:?}" \
#       --python_out="${CHAKRA_ET_DIR:?}"
#   fi

g++ -shared -fPIC -O3 -I "${SCRIPT_DIR:?}"  et_feeder/et_feeder.cpp et_feeder/et_feeder_node.cpp

}

compile_chakra_et