/* Tiny unit-test helper that prints to stdout and writes a JUnit XML report
 * so Jenkins can show pass / fail / skipped per requirement. */
#ifndef MINI_JUNIT_H
#define MINI_JUNIT_H

#include <stdio.h>
#include <string.h>

#define MJ_MAX_CASES 64

typedef enum { MJ_PASS = 0, MJ_FAIL = 1, MJ_XFAIL = 2 } mj_status_t;

typedef struct {
  const char *name;
  mj_status_t status;
  char msg[512];
} mj_case_t;

static mj_case_t mj_cases[MJ_MAX_CASES];
static int mj_n = 0;
static int mj_cur_failed = 0;
static char mj_cur_msg[256];

#define MJ_CHECK(cond, ...)                                                \
  do {                                                                     \
    if (!(cond) && !mj_cur_failed) {                                       \
      mj_cur_failed = 1;                                                   \
      snprintf(mj_cur_msg, sizeof(mj_cur_msg), __VA_ARGS__);               \
    }                                                                      \
  } while (0)

/* Run one test. expect_fail != 0 marks a known issue: a failure is reported
 * as "skipped" (XFAIL) so the build stays green but the issue stays visible.
 * If a known issue unexpectedly passes, it is reported as a failure so the
 * flag gets removed. */
static void mj_run(const char *name, void (*fn)(void), int expect_fail,
                   const char *issue)
{
  mj_case_t *c = &mj_cases[mj_n++];
  mj_cur_failed = 0;
  mj_cur_msg[0] = '\0';
  fn();
  c->name = name;
  if (!expect_fail) {
    c->status = mj_cur_failed ? MJ_FAIL : MJ_PASS;
    snprintf(c->msg, sizeof(c->msg), "%s", mj_cur_msg);
  } else if (mj_cur_failed) {
    c->status = MJ_XFAIL;
    snprintf(c->msg, sizeof(c->msg), "known issue %s: %s", issue, mj_cur_msg);
  } else {
    c->status = MJ_FAIL;
    snprintf(c->msg, sizeof(c->msg),
             "known issue %s now passes - remove the expect_fail flag", issue);
  }
  printf("[%s] %s%s%s\n",
         c->status == MJ_PASS ? " PASS" : (c->status == MJ_FAIL ? " FAIL" : "XFAIL"),
         name, c->msg[0] ? " -- " : "", c->msg);
}

static void mj_xml_escape(FILE *f, const char *s)
{
  for (; *s; s++) {
    switch (*s) {
      case '<': fputs("&lt;", f); break;
      case '>': fputs("&gt;", f); break;
      case '&': fputs("&amp;", f); break;
      case '"': fputs("&quot;", f); break;
      default: fputc(*s, f); break;
    }
  }
}

/* Returns number of hard failures (exit code for the test binary). */
static int mj_finish(const char *suite, const char *xml_path)
{
  int fails = 0, skips = 0, i;
  FILE *f;
  for (i = 0; i < mj_n; i++) {
    if (mj_cases[i].status == MJ_FAIL) fails++;
    if (mj_cases[i].status == MJ_XFAIL) skips++;
  }
  printf("%s: %d tests, %d failed, %d known issues\n", suite, mj_n, fails, skips);
  if (xml_path && (f = fopen(xml_path, "w")) != NULL) {
    fprintf(f, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(f, "<testsuite name=\"%s\" tests=\"%d\" failures=\"%d\" skipped=\"%d\">\n",
            suite, mj_n, fails, skips);
    for (i = 0; i < mj_n; i++) {
      fprintf(f, "  <testcase classname=\"%s\" name=\"", suite);
      mj_xml_escape(f, mj_cases[i].name);
      fprintf(f, "\">");
      if (mj_cases[i].status == MJ_FAIL) {
        fprintf(f, "<failure message=\"");
        mj_xml_escape(f, mj_cases[i].msg);
        fprintf(f, "\"/>");
      } else if (mj_cases[i].status == MJ_XFAIL) {
        fprintf(f, "<skipped message=\"");
        mj_xml_escape(f, mj_cases[i].msg);
        fprintf(f, "\"/>");
      }
      fprintf(f, "</testcase>\n");
    }
    fprintf(f, "</testsuite>\n");
    fclose(f);
  }
  return fails;
}

#endif /* MINI_JUNIT_H */
