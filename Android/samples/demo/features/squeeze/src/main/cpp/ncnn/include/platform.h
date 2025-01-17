// Tencent is pleased to support the open source community by making ncnn available.
//
// Copyright (C) 2017 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#ifndef NCNN_PLATFORM_H
#define NCNN_PLATFORM_H

#define NCNN_STDIO 1
#define NCNN_STRING 1
#define NCNN_OPENCV 0
#define NCNN_BENCHMARK 0
#define NCNN_PIXEL 1
#define NCNN_PIXEL_ROTATE 0
#define NCNN_VULKAN 0
#define NCNN_REQUANT 0
#define NCNN_AVX2 0

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else

#include <pthread.h>

#endif

namespace ncnn {

#ifdef _WIN32
    class Mutex
    {
    public:
        Mutex() { InitializeSRWLock(&srwlock); }
        ~Mutex() {}
        void lock() { AcquireSRWLockExclusive(&srwlock); }
        void unlock() { ReleaseSRWLockExclusive(&srwlock); }
    private:
        // NOTE SRWLock is available from windows vista
        SRWLOCK srwlock;
    };
#else // _WIN32

    class Mutex {
    public:
        Mutex() { pthread_mutex_init(&mutex, 0); }

        ~Mutex() { pthread_mutex_destroy(&mutex); }

        void lock() { pthread_mutex_lock(&mutex); }

        void unlock() { pthread_mutex_unlock(&mutex); }

    private:
        pthread_mutex_t mutex;
    };

#endif // _WIN32

    class MutexLockGuard {
    public:
        MutexLockGuard(Mutex &_mutex) : mutex(_mutex) { mutex.lock(); }

        ~MutexLockGuard() { mutex.unlock(); }

    private:
        Mutex &mutex;
    };

} // namespace ncnn

#endif // NCNN_PLATFORM_H
