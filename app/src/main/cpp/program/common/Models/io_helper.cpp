//
//  io_helper.c
//  GenS
//
//  Created by mac on 2017/5/21.
//  Copyright © 2017年 gen. All rights reserved.
//

#include "io_helper.h"
#include <string>
#include <unistd.h>

using namespace std;

void nl::removeDir(const char*  dir_path) {
    DIR *dir = opendir(dir_path);
    if (dir) {
        struct dirent* ent = NULL;
        while (NULL != (ent = readdir(dir))) {
            if (ent->d_name[0] == '.' && (ent->d_name[1] == 0 || (ent->d_name[1] == '.' && ent->d_name[2] == 0))) {
                continue;
            }
            string path(dir_path);
            path.push_back('/');
            path += ent->d_name;
            if (ent->d_type==8) {
                remove(path.c_str());
            }else {
                removeDir(path.c_str());
            }
        }
        closedir(dir);
    }
    rmdir(dir_path);
}
