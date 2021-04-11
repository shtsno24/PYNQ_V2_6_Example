#include <iostream>
#include <cstdint>
#include "axis_inout_block_hls.hpp"

int main(){
    // init val/const
    const int16_t loop_limit = 4 * 2 + 2;
    const int16_t limit = 8 + 3 + 5;
    int16_t cnt_limit = 0;

    hls::stream<axis> _result_gcc;
    hls::stream<axis> _result_hls;
    hls::stream<axis> _trigger;
    hls::stream<axis> result_gcc, result_hls;
    axis buff;

    for(int16_t j = 0; j < loop_limit; j++){
        for(int16_t i = 0; i < 1; i++){
            buff.data = -999;
            buff.user = (i == 0);
            buff.last = (i == limit - 1);
            buff.keep = 0;
            buff.strb = 0;
            buff.id = 0;
            buff.dest = 0;
            _trigger << buff;
        }
        // Test with gcc
        testblock<axis>(_trigger, _result_gcc);
        // Test with hls
        _trigger >> _buff;
        testblock_fpga(_buff, _result_hls);

        std::cout << "times : " << j << std::endl;
        std::cout << "_result_gcc : [";
        for(int16_t k = 0; k < 8; k++){
            _result_gcc >> buff;
            std::cout << buff.data;
            if(j % 4 == 0){
                result_gcc << buff;
            }
            std::cout << ((k == 8 - 1) ? "" : ", ");
        }
        std::cout << "]\n";

        std::cout << "_result_hls : [";
        for(int16_t k = 0; k < 8; k++){
            _result_hls >> buff;
            std::cout << buff.data;
            if(j % 4 == 0){
                result_hls << buff;
            }
            std::cout << ((k == 8 - 1) ? "" : ", ");
        }
        std::cout << "]\n";

        std::cout << std::endl;
        if(j % 4 == 0){
            cnt_limit += 1;
            cnt_limit %= 2;
        }
    }

    std::cout << "result_gcc : [";
    for(int16_t k = 0; k < limit; k++){
        result_gcc >> buff;
        std::cout << buff.data;
        std::cout << ((k == limit - 1) ? "" : ", ");
    }
    std::cout << "]\n";

    std::cout << "result_hls : [";
    for(int16_t k = 0; k < limit; k++){
        result_hls >> buff;
        std::cout << buff.data;
        std::cout << ((k == limit - 1) ? "" : ", ");
    }
    std::cout << "]\n";

    return 0;

}
