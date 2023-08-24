#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <glob.h>
#include <stdbool.h>
#include "dbg.h"

#define CONFIG_FILENAME ".logfind"
#define MAX_DATA 100

typedef struct {
    char **terms;
    size_t count;
    bool allMustMatch;
} searchTerms_t;

void extractSearchTerms(int argc, char *argv[], searchTerms_t *searchTerms);
const char *getNextPattern();
int handleGlobError(int rc);
bool areAllTermsFoundInFile(char *filename, searchTerms_t *searchTerms);
bool isAtLeastOneTermFoundInFile(char *filename, searchTerms_t *searchTerms);
void freeSearchTerms(searchTerms_t *searchTerms);


int main(int argc, char *argv[])
{
    char *pattern;
    searchTerms_t searchTerms;
    glob_t globResult;

    extractSearchTerms(argc, argv, &searchTerms);
    if (searchTerms.count == 0) {
        printf("usage: %s [OPTION], term1, term2, ...", argv[0]);
        return 1;
    }

    while ((pattern = (char*)getNextPattern()) != NULL) {
        log_debug("Pattern: (%s)", pattern);
        
        int rc = glob(pattern, 0, NULL, &globResult);
        check(handleGlobError(rc) == 0, "Glob failed to execute pattern %s", pattern);
        
        for (int i = 0; i < globResult.gl_pathc; ++i) {
            char *filename = globResult.gl_pathv[i];
            bool doesFileMatch = false;
            if (searchTerms.allMustMatch) {
                doesFileMatch = 
                    areAllTermsFoundInFile(filename, &searchTerms);
            } else {
                doesFileMatch = 
                    isAtLeastOneTermFoundInFile(filename, &searchTerms);
            }
            if (doesFileMatch) {
                printf("%s\n", filename);
            }
        }
        free(pattern);
        globfree(&globResult);
    }

    freeSearchTerms(&searchTerms);
    return 0;

error:
    if (pattern)
        free(pattern);
    globfree(&globResult);
    return -1;

    
}

void extractSearchTerms(int argc, char *argv[], searchTerms_t *searchTerms)
{
    searchTerms->terms = malloc(sizeof(char*) * (argc - 1));
    searchTerms->count = 0;
    searchTerms->allMustMatch = true;

    for (int i = 1; i < argc; ++i) {
        check(searchTerms->count < (argc - 1), "Created more than allocated");

        if (strcmp(argv[i], "-o") == 0) {
            log_debug("Encountered -0 option");
            searchTerms->allMustMatch = false;
        } else {
            searchTerms->terms[searchTerms->count] = strdup(argv[i]);
            log_debug("created term: %s", argv[i]);

            searchTerms->count++;
        }
    }

    log_debug("All must match? %d", searchTerms->allMustMatch);
    log_debug("terms count: %lu", searchTerms->count);
    return;

error:
    freeSearchTerms(searchTerms);
    return;
}

const char* getNextPattern() {
    char *line = NULL;
    size_t len = 0;
    int lineLength;
    static FILE *configFile;

    if (!configFile) {
        configFile = fopen(CONFIG_FILENAME, "r");
        check(configFile, "Failed to open file " CONFIG_FILENAME);
    }

    lineLength = getline(&line, &len, configFile);
    if (lineLength == -1) {
        fclose(configFile);
        if (line)
            free(line);
        return NULL;
    }

    line[lineLength - 1] = '\0';
    return line;

error:
    if (configFile)
        fclose(configFile);
    if (line)
        free(line);
    return NULL;
}

int handleGlobError(int rc)
{
    switch (rc) {
        case GLOB_NOSPACE:
            sentinel("Glob ran out of memory");
        case GLOB_ABORTED:
            log_info("Glob read error");
            break;
        case GLOB_NOMATCH:
            log_debug("Glob didn't find any matches");
            break;
        case -1:
            sentinel("Failed to execute glob");
    }

    return 0;

error:
    return 1;
}

bool areAllTermsFoundInFile(char *filename, searchTerms_t *searchTerms)
{
    char buffer[MAX_DATA];
    int termsFoundCnt = 0;
    bool doesFileMatch = false;
    FILE *fd = fopen(filename, "r");

    check(fd, "Failed to open file %s", filename);
    check(searchTerms->count != 0, "Count of terms should be positive");

    log_debug("Checking file %s", filename);
    while (!doesFileMatch && fgets(buffer, MAX_DATA, fd) != NULL) {
        termsFoundCnt = 0;
        for (int i = 0; i < searchTerms->count; ++i) {
            //substring
            if (strcasestr(buffer, searchTerms->terms[i]) != NULL) {
                log_debug("term %s found in %s", searchTerms->terms[i], filename);
                ++termsFoundCnt;
            }
        }
        if (termsFoundCnt == searchTerms->count) {
            doesFileMatch = true;
        }
    }

    fclose(fd);

    log_debug("returned %d", doesFileMatch);
    return doesFileMatch;

error:
    if (fd)
        fclose(fd);
    return false;
}

bool isAtLeastOneTermFoundInFile(char *filename, searchTerms_t *searchTerms) 
{
    char buffer[MAX_DATA];
    bool doesFileMatch = false;
    FILE *fd = fopen(filename, "r");
    check(fd, "Failed to open file %s", filename);

    check(searchTerms->count != 0, "Count should be positive");

    log_debug("Checking file %s", filename);
    while (!doesFileMatch && fgets(buffer, MAX_DATA, fd) != NULL) {
        for (int i = 0; i < searchTerms->count; ++i) {
            if (strcasestr(buffer, searchTerms->terms[i]) != NULL) {
                log_debug("term %s found in %s", searchTerms->terms[i], filename);
                doesFileMatch = true;
                break;
            }
        }
    }
    fclose(fd);
    log_debug("returned %d", doesFileMatch);
    return doesFileMatch;

error:
    if (fd)
        fclose(fd);
    return false;
}

void freeSearchTerms(searchTerms_t *searchTerms)
{
    for (int i = 0; i < searchTerms->count; ++i) {
        free(searchTerms->terms[i]);
    }
    free(searchTerms->terms);
}
