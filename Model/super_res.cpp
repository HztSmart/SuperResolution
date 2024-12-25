#include <iostream>  
#include <libavformat/avformat.h>  
#include <libavcodec/avcodec.h>  
#include <libavutil/log.h>  

void init() {  
    // 初始化网络  
    avformat_network_init();  
}  

void cleanup() {  
    //  清理  
    avformat_network_deinit();  
}   

int main() {  
    init();  

    const char* input_files[] = {"video1.mp4", "video2.mp4"};  
    const char* output_file = "output.mp4";  

    AVFormatContext* output_ctx = nullptr;  
    avformat_alloc_output_context2(&output_ctx, nullptr, nullptr, output_file);  
    if (!output_ctx) {  
        std::cerr << "Could not create output context" << std::endl;  
        return -1;  
    }  

    // 处理每个输入文件  
    for (const char* input_file : input_files) {  
        AVFormatContext* input_ctx = nullptr;  
        if (avformat_open_input(&input_ctx, input_file, nullptr, nullptr) < 0) {  
            std::cerr << "Could not open input file " << input_file << std::endl;  
            cleanup();  
            return -1;  
        }  

        if (avformat_find_stream_info(input_ctx, nullptr) < 0) {  
            std::cerr << "Could not find stream information for " << input_file << std::endl;  
            avformat_close_input(&input_ctx);  
            cleanup();  
            return -1;  
        }  

        // 复制每一个流到输出文件  
        for (unsigned int i = 0; i < input_ctx->nb_streams; i++) {  
            AVStream* in_stream = input_ctx->streams[i];  
            AVStream* out_stream = avformat_new_stream(output_ctx, nullptr);  
            if (!out_stream) {  
                std::cerr << "Failed to allocate output stream" << std::endl;  
                avformat_close_input(&input_ctx);  
                cleanup();  
                return -1;  
            }  

            // 复制流信息  
            avcodec_parameters_copy(out_stream->codecpar, in_stream->codecpar);  
            out_stream->codecpar->codec_tag = 0; // 清空 codec_tag  
        }  

        // 将输入文件流写入到输出文件  
        if (avformat_write_header(output_ctx, nullptr) < 0) {  
            std::cerr << "Error occurred when writing header to output file" << std::endl;  
            avformat_close_input(&input_ctx);  
            cleanup();  
            return -1;  
        }  

        // 读取数据包并写入输出文件  
        AVPacket pkt;  
        while (av_read_frame(input_ctx, &pkt) >= 0) {  
            // 找出流索引  
            pkt.stream_index = 0; // 修改为合适的流索引  

            // 写入输出文件  
            if (av_interleaved_write_frame(output_ctx, &pkt) < 0) {  
                std::cerr << "Error occurred when writing a frame to output file" << std::endl;  
                break;  
            }  
            av_packet_unref(&pkt);  
        }  

        avformat_close_input(&input_ctx);  
    }  

    av_write_trailer(output_ctx);  
    avformat_free_context(output_ctx);  
    cleanup();  

    std::cout << "视频拼接成功，输出文件为 " << output_file << std::endl;  
    return 0;  
}  