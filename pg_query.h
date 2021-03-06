#ifndef PG_QUERY_H
#define PG_QUERY_H

#include "c.h"
#include "lib/stringinfo.h"

typedef struct {
	char* message; // exception message
	char* funcname; // source function of exception (e.g. SearchSysCache)
	char* filename; // source of exception (e.g. parse.l)
	int lineno; // source of exception (e.g. 104)
	int cursorpos; // char in query at which exception occurred
	char* context; // additional context (optional, can be NULL)
} PgQueryError;

typedef struct {
  char* parse_tree;
  char* stderr_buffer;
  PgQueryError* error;
} PgQueryParseResult;

typedef struct {
  char* plpgsql_funcs;
  PgQueryError* error;
} PgQueryPlpgsqlParseResult;

typedef struct {
  char* hexdigest;
  char* stderr_buffer;
  PgQueryError* error;
} PgQueryFingerprintResult;

typedef struct {
  char* normalized_query;
  PgQueryError* error;
} PgQueryNormalizeResult;

#ifdef __cplusplus
extern "C" {
#endif

PgQueryNormalizeResult pg_query_normalize(const char* input);
PgQueryParseResult pg_query_parse(const char* input);
PgQueryPlpgsqlParseResult pg_query_parse_plpgsql(const char* input);

PgQueryFingerprintResult pg_query_fingerprint(const char* input);

void pg_query_free_normalize_result(PgQueryNormalizeResult result);
void pg_query_free_parse_result(PgQueryParseResult result);
void pg_query_free_plpgsql_parse_result(PgQueryPlpgsqlParseResult result);
void pg_query_free_fingerprint_result(PgQueryFingerprintResult result);

// Deprecated APIs below

void pg_query_init(void); // Deprecated as of 9.5-1.4.1, this is now run automatically as needed

#ifdef __cplusplus
}
#endif

#endif
