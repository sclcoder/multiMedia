//
//  Mp3Encoder.h
//  PhuketTour
//
//  Created by sunchunlei on 2020/10/24.
//

#ifndef Mp3Encoder_h
#define Mp3Encoder_h
#include "lame.h"

class Mp3Encoder{
    
private:
    FILE *pcmFile;
    FILE *mp3File;
    lame_t lameClient;

public:
    Mp3Encoder();
    ~Mp3Encoder();
    
    int Init(const char *pcmFilePath, const char *mp3FilePath, int sampleRate, int channels, int bitRate);
    void Encode();
    void Destory();
};

#endif /* Mp3Encoder_h */
