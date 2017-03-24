// Tencent is pleased to support the open source community by making Mars available.
// Copyright (C) 2016 THL A29 Limited, a Tencent company. All rights reserved.

// Licensed under the MIT License (the "License"); you may not use this file except in 
// compliance with the License. You may obtain a copy of the License at
// http://opensource.org/licenses/MIT

// Unless required by applicable law or agreed to in writing, software distributed under the License is
// distributed on an "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
// either express or implied. See the License for the specific language governing permissions and
// limitations under the License.

//
//  NetworkStatus.m
//  iOSDemo
//
//  Created by yanguoyue on 16/12/19.
//  Copyright © 2016年 Tencent. All rights reserved.
//

#import "NetworkStatus.h"

#import <Foundation/Foundation.h>
#import <SystemConfiguration/CaptiveNetwork.h>
#import <SystemConfiguration/SCNetworkReachability.h>
#import <netinet/in.h>


SCNetworkReachabilityRef g_Reach;


static void ReachCallback(SCNetworkReachabilityRef target, SCNetworkConnectionFlags flags, void* info)
{
    @autoreleasepool {
        [(__bridge id)info performSelector:@selector(ChangeReach)];
    }
}

@implementation NetworkStatus

static NetworkStatus * sharedSingleton = nil;

+ (NetworkStatus*)sharedInstance {
    @synchronized (self) {
        if (sharedSingleton == nil) {
            sharedSingleton = [[NetworkStatus alloc] init];
        }
    }
    
    return sharedSingleton;
}

-(void) Start:(__unsafe_unretained id<NetworkStatusDelegate>)delNetworkStatus {
    
    m_delNetworkStatus = delNetworkStatus;
    
    if (g_Reach == nil) {
        //创建零地址，0.0.0.0的地址表示查询本机的网络连接状态
        struct sockaddr_in zeroAddress;
        bzero(&zeroAddress, sizeof(zeroAddress));
        zeroAddress.sin_len = sizeof(zeroAddress);
        zeroAddress.sin_family = AF_INET;
        g_Reach = SCNetworkReachabilityCreateWithAddress(kCFAllocatorDefault, (struct sockaddr *)&zeroAddress);
    }
    
    //SCNetworkReachabilitySetCallback函数为指定一个target（此处为reachabilityRef，即www.apple.com,在reachabilityWithHostName里设置的）
    //当设备对于这个target链接状态发生改变时(比如断开链接，或者重新连上)，则回调reachabilityCallback函数，
    SCNetworkReachabilityContext context = {0, (__bridge void *)self, NULL, NULL, NULL};
    if(SCNetworkReachabilitySetCallback(g_Reach, ReachCallback, &context)) {
        //指定一个runloop给指定的target
        if(!SCNetworkReachabilityScheduleWithRunLoop(g_Reach, CFRunLoopGetCurrent(), kCFRunLoopCommonModes)) {
            
            SCNetworkReachabilitySetCallback(g_Reach, NULL, NULL);
            return;
        }
    }
    
    
    
}

-(void) Stop {
    if(g_Reach != nil) {
        SCNetworkReachabilitySetCallback(g_Reach, NULL, NULL);
        SCNetworkReachabilityUnscheduleFromRunLoop(g_Reach, CFRunLoopGetCurrent(), kCFRunLoopCommonModes);
        CFRelease(g_Reach);
        g_Reach = nil;
    }
    
    m_delNetworkStatus = nil;
}

-(void) ChangeReach {
    
    SCNetworkConnectionFlags connFlags;
    //获得连接的标志
    if(!SCNetworkReachabilityGetFlags(g_Reach, &connFlags)) {
        return;
    }
    
    if(m_delNetworkStatus != nil) {
        [m_delNetworkStatus ReachabilityChange:connFlags];
    }
    
    
}

@end
