// via: http://c.learncodethehardway.org/book/ex20.html

#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <time.h>

typedef struct {char str[24];} time_str;

time_str
curtime()
{
    time_t ltime; /* calendar time */
    ltime=time(NULL); /* get current cal time */
    struct tm *tm = localtime(&ltime);
    time_str ctime_str;
    sprintf(
        ctime_str.str,
        "%04d-%02d-%02d %02d:%02d:%02d",
        1900 + tm->tm_year,
        1 + tm->tm_mon,
        tm->tm_mday,
        tm->tm_hour,
        tm->tm_min,
        tm->tm_sec
    );
    return ctime_str;
}


#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...) fprintf(stdout, "[%s] DEBUG %s:%d:%s " M "\n", curtime().str, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#endif

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#define log_err(M, ...) fprintf(stderr, "[%s][ERROR] (%s:%d:%s errno: %s) " M "\n", curtime().str, __FILE__, __LINE__, __FUNCTION__, clean_errno(), ##__VA_ARGS__)

#define log_warn(M, ...) fprintf(stdout, "[%s][WARN] (%s:%d:%s errno: %s) " M "\n", curtime().str, __FILE__, __LINE__, __FUNCTION__, clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stdout, "[%s][INFO] (%s:%d:%s) " M "\n", curtime().str, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)

#define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

#define sentinel(M, ...)  { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

#define check_mem(A) check((A), "Out of memory.")

#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error; }

#endif
