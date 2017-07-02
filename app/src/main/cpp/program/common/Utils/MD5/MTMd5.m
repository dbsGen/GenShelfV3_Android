//
//  MTMd5.m
//  DateManager
//
//  Created by apple on 12-2-9.
//  Copyright (c) 2012年 zrz. All rights reserved.
//

#import "MTMd5.h"
#import "md5.h"

@implementation MTMd5

@end
NSString *MD5String(NSData *data)
{
    return MD5StringFrom((const void*)data.bytes, data.length);
}

NSString *MD5StringFrom(const void* bytes, unsigned long size)
{
    md5_state_t state;
    md5_init(&state);
    md5_append(&state, bytes, size);
    md5_byte_t outPut[17];
    memset((void*)outPut, 0, sizeof(md5_byte_t) * 17);
    char outStr[33];
    md5_finish(&state, outPut);
    for (int di = 0; di < 16; ++di)
        sprintf(outStr + di * 2, "%02x", outPut[di]);
    outStr[32] = 0;
    return [NSString stringWithUTF8String:outStr];
}

@implementation NSString (MTMd5)

- (NSString *)MD5String {
    const char *chs = self.UTF8String;
    return MD5StringFrom(chs, strlen(chs));
}

@end
