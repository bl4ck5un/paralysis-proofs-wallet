#!/usr/bin/env bash

clang-format -style=file -i Enclave/*.cpp common/* untrusted/*.cpp Enclave/*.h untrusted/*.h
