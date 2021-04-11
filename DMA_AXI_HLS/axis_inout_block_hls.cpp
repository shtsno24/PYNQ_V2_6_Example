#include "axis_inout_block_hls.hpp"

void testblock_fpga(hls::stream<axis> &output_data, hls::stream<axis> &trigger){
//#pragma HLS INTERFACE axis register both port=trigger depth=10
//#pragma HLS INTERFACE axis register both port=output_data depth=10
#pragma HLS INTERFACE axis register both port=trigger
#pragma HLS INTERFACE axis register both port=output_data
#pragma HLS INTERFACE s_axilite register port=return

	axis _buff;
	int16_t cnt = 0;
	do{
		trigger >> _buff;
		cnt += 1;
	}
	while (_buff.last == 1);

	_testblock<axis>(output_data, _buff);
//    return 0;
}
