//
//  io_helper.h
//  GenS
//
//  Created by mac on 2017/5/21.
//  Copyright © 2017年 gen. All rights reserved.
//

#ifndef io_helper_h
#define io_helper_h

#include <dirent.h>
#include <sys/stat.h>
#include <zconf.h>

namespace nl {
    void removeDir(const char*  dir_path);
}

#endif /* io_helper_h */
