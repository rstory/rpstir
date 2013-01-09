#ifndef _LIB_CONFIG_CONFIG_H
#define _LIB_CONFIG_CONFIG_H


#include <inttypes.h>
#include <stdbool.h>

#include "configlib/configlib.h"


/**
    This is the only file that needs to be directly included to use rpstir's
    configuration system. See lib/configlib/configlib.h for more detail about
    extending the configuration system.
*/


enum config_key {
    CONFIG_ROOT_DIR,
    CONFIG_RPKI_PORT,
    CONFIG_DATABASE,
    CONFIG_DATABASE_USER,
    CONFIG_DATABASE_PASSWORD,
    CONFIG_DATABASE_ROOT_PASSWORD,
    CONFIG_DATABASE_DSN,
    CONFIG_DOWNLOAD_CONCURRENCY,
    CONFIG_RPKI_RTR_RETENTION_HOURS,
    CONFIG_RPKI_ALLOW_STALE_VALIDATION_CHAIN,
    CONFIG_RPKI_ALLOW_NO_MANIFEST,
    CONFIG_RPKI_ALLOW_STALE_CRL,
    CONFIG_RPKI_ALLOW_STALE_MANIFEST,
    CONFIG_RPKI_ALLOW_NOT_YET,
    CONFIG_RPKI_EXTRA_PUBLICATION_POINTS,
    CONFIG_NEW_VERSION_CHECK,

    CONFIG_NUM_OPTIONS
};


/**
    The below macro calls generate helper functions to access the configuration
    values. See the definitions of each macro in lib/configlib/configlib.h for
    more detail, but here's a summary of how to access some of the below
    options:

        const char * root_dir = CONFIG_ROOT_DIR_get();

        uint16_t rpki_port = CONFIG_RPKI_PORT_get();

        for (size_t i = 0;
            i < config_get_length(CONFIG_RPKI_EXTRA_PUBLICATION_POINTS);
            ++i)
        {
            const char * rpki_extra_pub_pt =
                CONFIG_RPKI_EXTRA_PUBLICATION_POINTS_get(i);
            printf("extra publication point: %s\n", rpki_extra_pub_pt);
        }
*/

CONFIG_GET_HELPER(CONFIG_ROOT_DIR, char)
CONFIG_GET_HELPER_DEREFERENCE(CONFIG_RPKI_PORT, uint16_t)
CONFIG_GET_HELPER(CONFIG_DATABASE, char)
CONFIG_GET_HELPER(CONFIG_DATABASE_USER, char)
CONFIG_GET_HELPER(CONFIG_DATABASE_PASSWORD, char)
CONFIG_GET_HELPER(CONFIG_DATABASE_ROOT_PASSWORD, char)
CONFIG_GET_HELPER(CONFIG_DATABASE_DSN, char)
CONFIG_GET_HELPER_DEREFERENCE(CONFIG_DOWNLOAD_CONCURRENCY, size_t)
CONFIG_GET_HELPER_DEREFERENCE(CONFIG_RPKI_RTR_RETENTION_HOURS, size_t)
CONFIG_GET_HELPER_DEREFERENCE(CONFIG_RPKI_ALLOW_STALE_VALIDATION_CHAIN, bool)
CONFIG_GET_HELPER_DEREFERENCE(CONFIG_RPKI_ALLOW_NO_MANIFEST, bool)
CONFIG_GET_HELPER_DEREFERENCE(CONFIG_RPKI_ALLOW_STALE_CRL, bool)
CONFIG_GET_HELPER_DEREFERENCE(CONFIG_RPKI_ALLOW_STALE_MANIFEST, bool)
CONFIG_GET_HELPER_DEREFERENCE(CONFIG_RPKI_ALLOW_NOT_YET, bool)
CONFIG_GET_ARRAY_HELPER(CONFIG_RPKI_EXTRA_PUBLICATION_POINTS, char)
CONFIG_GET_HELPER(CONFIG_NEW_VERSION_CHECK, char)



/**
    Wrapper around config_load() with rpstir-specific data.

    The notes about thread-safety and logging from config_load() in
    lib/configlib/configlib.h apply to this too.

    See also config_unload() in configlib.h.
*/
bool my_config_load(
    );


#endif
