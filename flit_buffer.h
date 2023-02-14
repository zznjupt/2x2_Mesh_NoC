#ifndef FLIT_BUFFER_H_
#define FLIT_BUFFER_H_

#include <ap_int.h>
#include <ap_shift_reg.h>
#include "def.h"

#define FIFO_DEPTH VC_BUFFER_SIZE

typedef struct {
	int read_index_next;
	int write_index_next;
	int length_next;
	int write_addr;
	bool write_enable;
	flit_t write_data;
}flit_buffer_internal_wire;

class flit_buffer {
private:
	int read_index = 0;
	int write_index = 0;
	int length = 0;
	flit_t preloaded_data;
	flit_t buffer[FIFO_DEPTH];
public:
	flit_buffer() {
#pragma HLS bind_storage variable=buffer type=RAM_S2P impl=BRAM latency=1
	}

	bool empty() {
#pragma HLS INLINE
		return (length == 0);
	}

	boll full() {
#pragma HLS INLINE
		return (length == FIFO_DEPTH);
	}

	int size() {
#pragma HLS INLINE
		return length;
	}

	flit_t front() {
#pragma HLS INLINE
		return preloaded_data;
	}

	void update_combinational(flit_t data, bool read, bool write, flit_buffer_internal_wire* output_wire) {

	}



};
