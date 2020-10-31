//
//  CommonUtils.h
//  PhuketTour
//
//  Created by sunchunlei on 2020/10/31.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface CommonUtils : NSObject

+ (NSString *)bundlePath:(NSString *)fileName;

+ (NSString *)documentPath:(NSString *)fileName;

@end

NS_ASSUME_NONNULL_END
