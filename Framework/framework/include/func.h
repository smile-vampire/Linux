#ifndef __FUNC_H__
#define __FUNC_H__
void init_proctitle();
void set_proctitle(const char* name);
int get_int_default(const char *key,const int def);
void rtrim(char *str);
void ltrim(char *str);
int init_signal();
void master_process_cycle();
int set_daemon();
#endif
