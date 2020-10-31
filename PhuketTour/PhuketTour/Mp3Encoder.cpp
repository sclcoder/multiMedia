//
//  Mp3Encoder.cpp
//  PhuketTour
//
//  Created by sunchunlei on 2020/10/24.
//

#include "Mp3Encoder.h"

Mp3Encoder::Mp3Encoder(){

}
Mp3Encoder::~Mp3Encoder(){

}


// https://blog.csdn.net/bjrxyz/article/details/73435407?locationNum=15&fps=1
int Mp3Encoder::Init(const char *pcmFilePath, const char *mp3FilePath, int sampleRate, int channels, int bitRate){
    int ret = -1;
    pcmFile = fopen(pcmFilePath, "rb");
    if (pcmFile) {
        mp3File = fopen(mp3FilePath, "wb");
        if (mp3File) {
            
            // 初始化编码器
            lameClient = lame_init();
            // 设置被输入编码器的原始数据的采样率。
            lame_set_in_samplerate(lameClient, sampleRate);
            // 设置最终mp3编码输出的声音的采样率，如果不设置则和输入采样率一样。
            lame_set_out_samplerate(lameClient, sampleRate);
            // 设置被输入编码器的原始数据的声道数。
            lame_set_num_channels(lameClient, channels);
            // 设置最终mp3编码输出的声道模式，如果不设置则和输入声道数一样。参数是枚举，STEREO代表双声道，MONO代表单声道
            lame_set_mode(lameClient, STEREO);
            /**
             设置比特率控制模式，默认是CBR，但是通常我们都会设置VBR。参数是枚举，vbr_off代表CBR，vbr_abr代表ABR（因为ABR不常见，所以本文不对ABR做讲解）vbr_mtrh代表VBR。
             */
            // lame_set_VBR(lameClient, vbr_mtrh);

            // lame_set_brate：设置CBR的比特率，只有在CBR模式下才生效。
            lame_set_brate(lameClient, bitRate / 1000); // 比特率（bitrate):每秒钟的数据量，越高音质越好。

            // lame_set_VBR_mean_bitrate_kbps：设置VBR的比特率，只有在VBR模式下才生效。


            //根据上面设置好的参数建立编码器
            lame_init_params(lameClient);
            
            ret = 0;
        }
    }
    
    return ret;
}


/**
 https://blog.csdn.net/bjrxyz/article/details/73435407?locationNum=15&fps=1
 编码PCM数据
 lame_encode_buffer或lame_encode_buffer_interleaved：将PCM数据送入编码器，获取编码出的mp3数据。这些数据写入文件就是mp3文件。
 其中lame_encode_buffer输入的参数中是双声道的数据分别输入的，lame_encode_buffer_interleaved输入的参数中双声道数据是交错在一起输入的。具体使用哪个需要看采集到的数据是哪种格式的，不过现在的设备采集到的数据大部分都是双声道数据是交错在一起。
 单声道输入只能使用lame_encode_buffer，把单声道数据当成左声道数据传入，右声道传NULL即可。
 调用这两个函数时需要传入一块内存来获取编码器出的数据，这块内存的大小lame给出了一种建议的计算方式：采样率/20+7200。
 */
void Mp3Encoder::Encode(){
    /**
     描述
     C 库函数 size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream) 从给定流 stream 读取数据到 ptr 所指向的数组中。

     声明
     下面是 fread() 函数的声明。

     size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
     参数
     ptr -- 这是指向带有最小尺寸 size*nmemb 字节的内存块的指针。
     size -- 这是要读取的每个元素的大小，以字节为单位。
     nmemb -- 这是元素的个数，每个元素的大小为 size 字节。
     stream -- 这是指向 FILE 对象的指针，该 FILE 对象指定了一个输入流。
     
     返回值
     成功的返回值为实际读回的数据个数 即nmemb
     成功读取的元素总数会以 size_t 对象返回，size_t 对象是一个整型数据类型。如果总数与 nmemb 参数不同，则可能发生了一个错误或者到达了文件末尾。
     */
    
    
    /**
     为什么设置这个大小?
     因为引入的pcm文件大小为1.9M; int大小为8个字节，所以bufferSize的大小为 8 * 1024 * 256 Byte == 2 MB 刚好容下pcm文件
     */
    int bufferSize = 1024 * 256;  /// 内存大小为 1024 * 256 * 8 (int类型)
    short* buffer = new short[bufferSize / 2]; /// 内存大小为 1024 * 256 / 2 * 4 (short类型)
    short* leftBuffer = new short[bufferSize / 4];
    short* rightBuffer = new short[bufferSize / 4];
    unsigned char* mp3_buffer = new unsigned char[bufferSize];
    size_t readBufferSize = 0;
    /**
        每次从文件流pcmFile中读取2个字节，读取bufferSize / 2次，共读取bufferSize
        注意buffer中存放的是short类型的数据, int是2倍的short
        
     每次循环读取 bufferSize / 2 次数据（即每次读取成功readBufferSize的值为bufferSize / 2）,每次读2个字节的大小，所以一次while循环读取的数据大小为bufferSize个字节。
     注意实际开辟的大小为 8 * bufferSize
     所以while会循环8次，即每次写入的数据为1024 * 256 * 8的八分之一
     buffer的大小为 024 * 256 / 2 * 4 是实际开辟内存 1024 * 256 * 8大小的 4 分之一 , 每次读取的大小bufferSize为 1024 * 256 即buffer是2倍每次读取的大小，足够容纳每次读取的数据
     */
    while ((readBufferSize = fread(buffer, 2, bufferSize / 2, pcmFile)) > 0) {
        printf("次数\n"); /// 8次
        for (int i = 0; i < readBufferSize; i++) {
            // 将每个字节分发到对应的声道
            if (i % 2 == 0) {
                leftBuffer[i / 2] = buffer[i];
            } else {
                rightBuffer[i / 2] = buffer[i];
            }
        }
        /// 开始进行mp3编码
        size_t wroteSize = lame_encode_buffer(lameClient, (short int *) leftBuffer, (short int *) rightBuffer, (int)(readBufferSize / 2), mp3_buffer, bufferSize);
        fwrite(mp3_buffer, 1, wroteSize, mp3File);
    }
    delete[] buffer;
    delete[] leftBuffer;
    delete[] rightBuffer;
    delete[] mp3_buffer;
    
}


void Mp3Encoder::Destory(){
    if (pcmFile) {
        fclose(pcmFile);
    }
    if (mp3File) {
        fclose(mp3File);
        lame_close(lameClient);
    }
}
