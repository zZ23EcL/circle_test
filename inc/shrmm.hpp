//
// Created by graphite on 22-9-8.
//

#ifndef SHAREDLIB_SHRMM_HPP
#define SHAREDLIB_SHRMM_HPP

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>

class Memory
{
public:
    Memory() {addr = NULL; shmid = 0; size = 0;};
    int open_shm(int share_memory_key, int share_feature);
    int close_shm();
    void* get_address();
    int get_maxsize();
private:
    int shmid = 0;
    int size = 0;
    void* addr = NULL;
};

#endif //SHAREDLIB_SHRMM_HPP
