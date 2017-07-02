//
//  DIConfig.h
//  AHARSDK
//
//  解析读取config文件
//  config:
//  <100m
//  during 7d
//  and
//  count  5
//  <300m
//  during 5d
//  or
//  count 3
//
//  Created by gen on 2017/2/13.
//  Copyright © 2017年 JT Ma. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef BOOL (*DIConfigOperator)(size_t, size_t);
typedef BOOL (*DIConfigComOperator)(BOOL, BOOL);

@interface DIConfig : NSObject {
}

@property (nonatomic, readonly) NSDate  *date;
@property (nonatomic, readonly) NSInteger count;
@property (nonatomic, readonly) DIConfigOperator op;
@property (nonatomic, readonly) DIConfigComOperator comOp;
@property (nonatomic, readonly) size_t size;

+ (NSArray *)defaultConfigs;
+ (NSArray *)configsFromString:(NSString *)content;
+ (NSArray *)configsFromPath:(NSString *)path;

@end
