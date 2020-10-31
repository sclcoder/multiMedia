//
//  ViewController.m
//  PhuketTour
//
//  Created by sunchunlei on 2020/10/24.
//

#import "ViewController.h"
#import "Mp3Encoder.h"
#import "CommonUtils.h"
@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}
- (IBAction)startEncode:(UIButton *)sender { 
    NSLog(@"Start Encode...");
    Mp3Encoder* encoder = new Mp3Encoder();
    const char* pcmFilePath = [[CommonUtils bundlePath:@"vocal.pcm"] cStringUsingEncoding:NSUTF8StringEncoding];
    const char *mp3FilePath = [[CommonUtils documentPath:@"vocal.mp3"] cStringUsingEncoding:NSUTF8StringEncoding];
    int sampleRate = 44100;
    int channels = 2;
    int bitRate = 128 * 1024;
    encoder->Init(pcmFilePath, mp3FilePath, sampleRate, channels, bitRate);
    encoder->Encode();
    encoder->Destory();
    delete encoder;
    NSLog(@"Encode Success");
}


@end
