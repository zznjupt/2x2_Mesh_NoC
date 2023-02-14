#include "input_unit.h"

input_unit::input_unit() {
// #pragma HLS INTERFACE ap_ctrl_none port=return
}

void input_unit::update_combinational(
	flit_t in_flit_data, 					// input
	bool   in_flit_valid, 					// input
	bool   read[PORT_COUNT],				// input

	flit_t out_flit_data[PORT_COUNT],		// output
	bool   out_flit_valid[PROT_COUNT], 		// output
	bool*  VC_full,							// output
	input_unit_internal_wire* output_wire 	// output
) {
#pragma HLS INLINE
	int write_channel;

	if(flit_counter == 0 && in_flit_valid == true) { // Decide new VC channel
		ID_t flit_ID = in_flit_data.range(
			FLIT_DATA_WIDTH-PACKET_SEQ_NUM_WIDTH-1,
			FLIT_DATA_WIDTH-PACKET_SEQ_NUM_WIDTH-ROUTER_ID_WIDTH
		);

		if(flit_ID == router_ID) {
			write_channle = VC_NI;
		} else if(flit_ID.get_bit(1) == router_ID.get_bit(1)) { // Same row
			// Need change back
			if(flit_ID.get_bit(0) > router_ID.get_bit(0))
				write_channel = VC_WEST;
			else
				write_channel = VC_EAST;
		} else {
			if(flit_ID.get_bit(1) > router_ID.get_bit(1))
				write_channel = VC_NORTH;
			else
				write_channel = VC_SOUTH;
		}
	} else { // Keep old VC channel
		write_channel = last_ID;
	}

	for(int i = 0; i < PORT_COUNT; i++) {
#pragma HLS UNROLL
		out_flit_data[i] = VC_buffer[i].front();
		out_flit_valid[i] = (!VC_buffer[i].empty()) & read[i];
	}

	if(in_flit_valid == true)
		output_wire->last_ID_next = last_ID
}
