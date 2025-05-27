
#ifndef GSM_TEST_H
#define GSM_TEST_H

#define PREFIX_PATH "/home/sbn/Work/Paper/perf_counter_exploit/mibench/telecomm/gsm/data/"

#define INPUT_LARGE_AU    PREFIX_PATH   "large.au"
#define INPUT_LARGE_GSM      PREFIX_PATH  "large.au.run.gsm"

#define INPUT_SMALL_AU      PREFIX_PATH "small.au"
#define INPUT_SMALL_GSM     PREFIX_PATH  "small.au.run.gsm"

int __toast (int ac, char **av);

void _toast_large() {
    __toast(4, (char *[]){"toast", "-fps", "-c", INPUT_LARGE_AU});
    __toast(4, (char *[]){"toast", "-fps", "-c", INPUT_LARGE_GSM});
}

void _toast_small() {
    __toast(4, (char *[]){"toast", "-fps", "-c", INPUT_SMALL_AU});
    __toast(4, (char *[]){"toast", "-fps", "-c", INPUT_SMALL_GSM});
}


#endif //GSM_TEST_H
