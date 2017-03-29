// Tencent is pleased to support the open source community by making Mars available.
// Copyright (C) 2016 THL A29 Limited, a Tencent company. All rights reserved.

// Licensed under the MIT License (the "License"); you may not use this file except in 
// compliance with the License. You may obtain a copy of the License at
// http://opensource.org/licenses/MIT

// Unless required by applicable law or agreed to in writing, software distributed under the License is
// distributed on an "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
// either express or implied. See the License for the specific language governing permissions and
// limitations under the License.


/*
 * bootrun.h
 *
 *  Created on: 2014-7-9
 *      Author: yerungui
 */

#ifndef COMM_BOOTRUN_H_
#define COMM_BOOTRUN_H_

#include <stdlib.h>
#include "comm/compiler_util.h"

#ifdef __cplusplus
extern "C" {
#endif

__inline int boot_run_atstartup(void (*func)(void)) { func(); return 0;}
    
/*
atexit函数的用途也是比较广泛的：可以按照你予设的顺序摧毁全局变量（类），例如有个log类，你在其它的全局类里也有可能调用到Log类写日志。所以log 类必须最后被析构 。假如没有规定析构顺序，那么程序在退出时将有可能首先析构log类，那么其它的全局类在此时将无法正确写日志。 把数据写回文件, 删除临时文件, 这才是真正有用的.
*/
__inline int boot_run_atexit(void (*func)(void)) { return atexit(func);}

#ifdef __cplusplus
}
#endif

#define BOOT_RUN_STARTUP(func) VARIABLE_IS_NOT_USED static int __anonymous_run_variable_startup_##func = boot_run_atstartup(func)
#define BOOT_RUN_EXIT(func) VARIABLE_IS_NOT_USED static int __anonymous_run_variable_exit_##func = boot_run_atexit(func)

#endif /* COMM_BOOTRUN_H_ */
