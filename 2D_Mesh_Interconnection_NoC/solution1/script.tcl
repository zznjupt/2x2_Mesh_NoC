############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
############################################################
open_project 2D_Mesh_Interconnection_NoC
add_files def.h
add_files flit_buffer.h
add_files input_unit.cpp
add_files input_unit.h
open_solution "solution1" -flow_target vivado
set_part {xczu4eg-sfvc784-1-i}
create_clock -period 10 -name default
#source "./2D_Mesh_Interconnection_NoC/solution1/directives.tcl"
#csim_design
csynth_design
#cosim_design
export_design -format ip_catalog
