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
//  LogUtil.h
//  iOSDemo
//
//  Created by caoshaokun on 16/11/30.
//  Copyright © 2016年 caoshaokun. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "LogHelper.h"

@interface LogUtil : NSObject

@end

/*__FILE__ 是文件绝对路径，如filetest /srv/example/c/test/LogUtil.h, 也有可能是LogUtil.h
 *  char * strrchr(const char *str, int c); 将会找出 str 字符串中最后一次出现的字符 c 的地址，然后将该地址返回
 * 如果希望查找某字符在字符串中第一次出现的位置，可以使用 strchr() 函数
 */
#define __FILENAME__ (strrchr(__FILE__,'/')+1)

/**
 *  Module Logging
 */
#define LOG_ERROR(module, format, ...) LogInternal(kLevelError, module, __FILENAME__, __LINE__, __FUNCTION__, @"Error:", format, ##__VA_ARGS__)
#define LOG_WARNING(module, format, ...) LogInternal(kLevelWarn, module, __FILENAME__, __LINE__, __FUNCTION__, @"Warning:", format, ##__VA_ARGS__)
#define LOG_INFO(module, format, ...) LogInternal(kLevelInfo, module, __FILENAME__, __LINE__, __FUNCTION__, @"Info:", format, ##__VA_ARGS__)
#define LOG_DEBUG(module, format, ...) LogInternal(kLevelDebug, module, __FILENAME__, __LINE__, __FUNCTION__, @"Debug:", format, ##__VA_ARGS__)

static const char *kModuleViewController = "ViewController";
static const char *kNetwork = "Network";
