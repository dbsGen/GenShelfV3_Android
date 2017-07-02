//
//  DIManager.h
//  DownloadInterface
//
//  DIManager 是一个资源管理模块
//  包含下载，缓存相关功能。
//
//  Created by gen on 03/12/2016.
//  Copyright © 2016 gen. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum : NSUInteger {
    DIPostTypeForm = 0,
    DIPostTypeJson,
} DIPostType;

/**
 * 下载状态
 */
typedef enum : NSUInteger {
    DIStatusNone = 0,   //未开始
    DIStatusProcess,    //下载中
    DIStatusDone,       //已完成
    DIStatusPause,      //中间状态，当出现错误暂停也算Pause状态。
} DIStatus;

@class DIItem;

@protocol DIItemDelegate <NSObject>

// 当开始下载的时候调用
- (void)itemStarted:(DIItem*)item;
// 当状态百分比改变的时候调用
- (void)item:(DIItem*)item process:(float)percent;
// 当取下下载的时候调用
- (void)itemCanceled:(DIItem*)item;
// 当移除的时候调用
- (void)itemRemoved:(DIItem*)item;

- (void)itemFailed:(DIItem *)item error:(NSError *)error;

- (void)itemComplete:(DIItem *)item;

- (void)itemPaused:(DIItem *)item;

@end

@class DIManager;

// 可以放入DIItem 的 datas中

@interface DIData : NSObject

@property (nonatomic, strong) NSString  *mineType;
@property (nonatomic, strong) NSData    *data;
@property (nonatomic, strong) NSString  *fileName;

@end

/**
 * Item代表一个下载对象。
 * 不仅管理下载进度状态，还会管理缓存数据。
 */

@interface DIItem : NSObject {
@private
    // 标记是否已经移除，移除后不能进行下载操作。
    BOOL _removed;
}

@property (nonatomic, readonly, weak) DIManager *manager;

@property (nonatomic, assign) BOOL  readCache;
@property (nonatomic, assign) BOOL  readCacheWhenError;

@property (nonatomic, assign) BOOL  download;

@property (nonatomic, assign) NSTimeInterval    timeout;

@property (nonatomic, assign) DIPostType postType;
// post upload datas
@property (nonatomic, strong) NSDictionary *datas;
// http method
@property (nonatomic, strong) NSDictionary *headers;
// post http method
@property (nonatomic, strong) NSString *method;
// Url
@property (nonatomic, readonly) NSString *urlString;
// 本文件路径
@property (nonatomic, strong) NSString *path;
// 当前状态
@property (nonatomic, assign) DIStatus status;
// 文件总大小
@property (nonatomic, readonly) NSInteger totalSize;

// 文件当前尺寸
//@property (nonatomic, readonly) NSInteger size;
@property (nonatomic, assign) long long size;
// 下载进度
@property (nonatomic, assign) float percent;
//请求日期
@property (nonatomic, strong) NSDate *requestDate;
//无用计数
@property (nonatomic, assign) NSInteger unlessCount;
// 回调
@property (nonatomic, weak) id<DIItemDelegate> delegate;
// 回调2,请把block方式的回调也实现了，实际使用中会很好用。
typedef enum : NSUInteger {
    DICallbackStart = 0,
    DICallbackProcess,
    DICallbackCancel,
    DICallbackRemoved,
    DICallbackPause,
    DICallbackComplete,
    DICallbackFailed
} DICallbackType;
typedef void(^DIItemBlock)(DIItem* item, DICallbackType type, id data);
@property (nonatomic, copy) DIItemBlock block;

- (instancetype)initWithManager:(DIManager*)manager;

/**
 * 开始下载
 * 如果状态是完成状态直接回调
 * 如果状态是pause,需要在http headers
 * 中设置range，来实现断点续传。
 */
- (void)start;
// 取消下载
- (void)cancel;
// 移除缓存,并且移除这个对象
- (void)remove;

- (void)pause;

// 下载数据
- (NSData *)data;

//--- 下载之外逻辑
/**
 * 解压文件 
 * 解压完成后删除本zip文件，
 * 并且把path改为解压后的文件夹路径
 */
- (BOOL)extract:(BOOL*)extracted;

@end


//typedef enum : NSUInteger {
//    DINetworkStatusNone = 0,
//    DINetworkStatusWifi,
//    DINetworkStatus3G,
//} DINetworkStatus;

extern NSString *const DIManagerBasePathKey;

@interface DIManager : NSObject {
    /**
     * 所有对象并且按照时间顺序排序
     * 在存储缓存的时候写入本地索引文件中
     * DIManager初始化的时候从本地索引文件中读取
     */
    NSMutableArray<DIItem*> *_items;
    /**
     * items索引更快更方便的找到具体Item
     * 在DIManager初始化的时候，根据读取到的_items数据 
     * 初始化_itemIndexes。
     */
    NSMutableDictionary<NSString*, DIItem*> *_itemIndexes;
}

+ (instancetype)defaultManager;

/**
 * 缓存路径
 * 文件缓存地址
 */
@property (nonatomic, strong) NSString* path;

/**
 * 所有缓存使用的大小
 * 在初始化中读区索引的时候累加缓存大小
 * 在下载中或者删除的时候改变大小即可
 */
@property (nonatomic, readonly) NSInteger totalSize;

// 获得网络状态
//@property (nonatomic, readonly) DINetworkStatus networkStatus;

/**
 * 获得一个item
 * 如果这个Item在_itemIndexes以及_cacheItems中那么直接返回这个对象。
 * 否则，创建一个新对象并放入cacheItems
 */
- (DIItem *)itemWithURLString:(NSString *)urlString;
- (DIItem *)itemWithURLString:(NSString *)urlString
                        cache:(NSString *)cacheUrl;

//移除所有item，包括缓存。
- (void)clear;

- (void)removeItem:(DIItem *)item;

- (void)removeItemWithIdentifier:(NSString *)identifier;

/**
 * 保存_items数据到文件中
 * 除此之外Manager中还应该实现定时保存机制。
 */
- (void)save;

//--- 下载之外逻辑
// 获得所有AR看车的下载文件的地址
- (void)getCarUrls:(void(^)(NSArray<NSString*>*))urls;

- (NSString *)stringMD5:(NSString *)originalString;

// 加载配置文件
- (void)loadConfig:(NSString *)path;

// 当前不能删的item
- (void)setProtectingItem:(DIItem *)item;

// 自动清除item
//- (void)autoClear;
- (void)autoClearIncreaseUnlessCount:(BOOL)increaseUnlessCount;

//自动删除配置文件路径
- (NSString *)autoClearConfigPath;

// 暂停所有正在请求的item
- (void)pauseProcessItems;

- (void)restartPauseItems;

- (void)dispalyItems;

@end
