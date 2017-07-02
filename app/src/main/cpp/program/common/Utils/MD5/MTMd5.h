//
//  MTMd5.h
//  DateManager
//
//  Created by apple on 12-2-9.
//  Copyright (c) 2012年 zrz. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MTMd5 : NSObject

@end

NSString *MD5String(NSData *data);
NSString *MD5StringFrom(const void* bytes, unsigned long size);

@interface NSString (MTMd5)

- (NSString *)MD5String;

@end