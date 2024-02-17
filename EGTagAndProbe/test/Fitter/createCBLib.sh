#!/bin/bash

cd ext
root  -l -b << EOF
.L FuncCB.cpp++
.q
EOF

mv FuncCB_cpp.so FuncCB_cpp_ACLiC_dict_rdict.pcm ../obj
rm FuncCB_cpp.d