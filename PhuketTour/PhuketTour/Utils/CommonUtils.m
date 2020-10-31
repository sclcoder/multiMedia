//
//  CommonUtils.m
//  PhuketTour
//
//  Created by sunchunlei on 2020/10/31.
//

#import "CommonUtils.h"

@implementation CommonUtils

+ (NSString *)bundlePath:(NSString *)fileName{
    return [[[NSBundle mainBundle]  bundlePath] stringByAppendingPathComponent:fileName];
}

+ (NSString *)documentPath:(NSString *)fileName{
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask , YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    return [documentsDirectory stringByAppendingPathComponent:fileName];
}

@end
