
#ifndef GSM_TEST_H
#define GSM_TEST_H

#define GSM_PREFIX_PATH "/home/sbn/Work/Paper/perf_counter_exploit/mibench/telecomm/gsm/data/"

#define GSM_INPUT_LARGE_AU    GSM_PREFIX_PATH   "large.au"
#define GSM_INPUT_LARGE_GSM      GSM_PREFIX_PATH  "large.au.run.gsm"

#define GSM_INPUT_SMALL_AU      GSM_PREFIX_PATH "small.au"
#define GSM_INPUT_SMALL_GSM     GSM_PREFIX_PATH  "small.au.run.gsm"

int __toast (int ac, char **av);

static inline void _toast_large() {
    __toast(4, (char *[]){"toast", "-fps", "-c", GSM_INPUT_LARGE_AU});
    __toast(4, (char *[]){"toast", "-fps", "-c", GSM_INPUT_LARGE_GSM});
}

static inline void _toast_small() {
    __toast(4, (char *[]){"toast", "-fps", "-c", GSM_INPUT_SMALL_AU});
    __toast(4, (char *[]){"toast", "-fps", "-c", GSM_INPUT_SMALL_GSM});
}


#endif //GSM_TEST_H
