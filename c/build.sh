#!/usr/bin/env bash

mkdir c_output
cd c_output && cmake .. && make
cd .. && rm -rf c_output
