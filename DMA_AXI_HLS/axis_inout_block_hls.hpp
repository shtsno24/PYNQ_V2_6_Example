#include </tools/Xilinx/Vivado/2020.1/include/gmp.h>
#include <iomanip>
#include <stdint.h>
#include "hls_stream.h"
#include "ap_int.h"
#include "ap_axi_sdata.h"

using axis = ap_axis<32, 1, 1, 1>;

template <typename data_t>
void testblock(hls::stream<data_t> &output_data, data_t tmp) {

    data_t _rom_0[8];
    for(int16_t i = 0; i < 8; i++){
        _rom_0[i].data = -1;
        _rom_0[i].user = (i == 0);
        _rom_0[i].last = (i == 7);
    }

    data_t _rom_1[8];
    for(int16_t i = 0; i < 3; i++){
        _rom_1[i].data = i + 1;
        _rom_1[i].user = (i == 0);
        _rom_1[i].last = (i == 7);
    }
    for(int16_t i = 3; i < 8; i++){
        _rom_1[i].data = -1;
        _rom_1[i].user = (i == 0);
        _rom_1[i].last = (i == 7);
    }

    data_t _rom_2[8];
    for(int16_t i = 0; i < 8; i++){
        _rom_2[i].data = (i + 1) * 5;
        _rom_2[i].user = (i == 0);
        _rom_2[i].last = (i == 7);
    }

    static int16_t loop_times = 0;
    static int16_t rom_selector = 0;
    #pragma HLS RESET variable=loop_times
    #pragma HLS RESET variable=rom_selector
    data_t buff;

    if(loop_times % 4 == 0){
        switch (rom_selector){
        case 0:
            for(int16_t i = 0; i < 8; i++){
#pragma HLS PIPELINE
                buff = _rom_1[i];
                buff.keep = tmp.keep;
                buff.strb = tmp.strb;
                buff.id = tmp.id;
                buff.dest = tmp.dest;
                output_data << buff;
            }
            break;
        case 1:
            for(int16_t i = 0; i < 8; i++){
#pragma HLS PIPELINE
                buff = _rom_2[i];
                buff.keep = tmp.keep;
                buff.strb = tmp.strb;
                buff.id = tmp.id;
                buff.dest = tmp.dest;
                output_data << buff;
            }
            rom_selector = -1;
            break;
        default:
            break;
        }
        rom_selector += 1;
    } else {
        for(int16_t i = 0; i < 8; i++){
#pragma HLS PIPELINE
            buff = _rom_0[i];
            buff.keep = tmp.keep;
            buff.strb = tmp.strb;
            buff.id = tmp.id;
            buff.dest = tmp.dest;
            output_data << buff;
        }
    }

    loop_times += 1;
    loop_times %= 4;
}

template <typename data_t>
void _testblock(hls::stream<data_t> &output_data, data_t tmp) {

    data_t _rom_0[8];
    for(int16_t i = 0; i < 8; i++){
        _rom_0[i].data = -1;
        _rom_0[i].user = (i == 0);
        _rom_0[i].last = (i == 7);
    }

    data_t _rom_1[8];
    for(int16_t i = 0; i < 3; i++){
        _rom_1[i].data = i + 1;
        _rom_1[i].user = (i == 0);
        _rom_1[i].last = (i == 7);
    }
    for(int16_t i = 3; i < 8; i++){
        _rom_1[i].data = -1;
        _rom_1[i].user = (i == 0);
        _rom_1[i].last = (i == 7);
    }

    data_t _rom_2[8];
    for(int16_t i = 0; i < 8; i++){
        _rom_2[i].data = (i + 1) * 5;
        _rom_2[i].user = (i == 0);
        _rom_2[i].last = (i == 7);
    }

    static int16_t loop_times = 0;
    static int16_t rom_selector = 0;
    #pragma HLS RESET variable=loop_times
    #pragma HLS RESET variable=rom_selector
    data_t buff;

    if(loop_times % 4 == 0){
        switch (rom_selector){
        case 0:
            for(int16_t i = 0; i < 8; i++){
#pragma HLS PIPELINE
                buff = _rom_1[i];
                buff.keep = tmp.keep;
                buff.strb = tmp.strb;
                buff.id = tmp.id;
                buff.dest = tmp.dest;
                output_data << buff;
            }
            break;
        case 1:
            for(int16_t i = 0; i < 8; i++){
#pragma HLS PIPELINE
                buff = _rom_2[i];
                buff.keep = tmp.keep;
                buff.strb = tmp.strb;
                buff.id = tmp.id;
                buff.dest = tmp.dest;
                output_data << buff;
            }
            rom_selector = -1;
            break;
        default:
            break;
        }
        rom_selector += 1;
    } else {
        for(int16_t i = 0; i < 8; i++){
#pragma HLS PIPELINE
            buff = _rom_0[i];
            buff.keep = tmp.keep;
            buff.strb = tmp.strb;
            buff.id = tmp.id;
            buff.dest = tmp.dest;
            output_data << buff;
        }
    }

    loop_times += 1;
    loop_times %= 4;
}

void testblock_fpga(hls::stream<axis> &trigger, hls::stream<axis> &output_data);
