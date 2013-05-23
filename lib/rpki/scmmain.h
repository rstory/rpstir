/*
 * $Id: scmmain.h 1285 2010-10-01 19:43:05Z bkohler $ 
 */


#ifndef _SCMMAIN_H_
#define _SCMMAIN_H_

#ifdef SCM_DEFINED_HERE

/*
 * Table definitions 
 */

/*
 * The sceme for adding in SQL statements to scmtabbuilder is the following:
 * column names should start with a lowercase letter all SQL keywords should
 * be uppercase 
 */

static scmtab scmtabbuilder[] = {
    {                           /* RPKI_CERT */
     /*
      * Usage notes: valfrom and valto are stored in GMT. local_id is a unique
      * identifier with the new one obtained via max(local_id) + 1 
      */
     "rpki_cert",
     "CERTIFICATE",
     "filename VARCHAR(256) NOT NULL,"
     "dir_id   INT UNSIGNED NOT NULL DEFAULT 1,"
     "subject  VARCHAR(512),"
     "issuer   VARCHAR(512) NOT NULL,"
     "sn       BINARY(20) NOT NULL,"
     "flags    INT UNSIGNED DEFAULT 0,"
     "ski      VARCHAR(128) NOT NULL,"
     "aki      VARCHAR(128),"
     "sia      VARCHAR(1024),"
     "aia      VARCHAR(1024),"
     "crldp    VARCHAR(1024),"
     "sig      VARCHAR(520) NOT NULL,"
     "hash     VARCHAR(256),"
     "valfrom  DATETIME NOT NULL,"
     "valto    DATETIME NOT NULL,"
     "sigval   INT UNSIGNED DEFAULT 0,"
     "ipblen   INT UNSIGNED DEFAULT 0,"
     "ipb      BLOB,"
     "ts_mod   TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,"
     "local_id INT UNSIGNED NOT NULL UNIQUE,"
     "         PRIMARY KEY (filename, dir_id),"
     "         KEY ski (ski, subject),"
     "         KEY aki (aki, issuer),"
     "         KEY lid (local_id),"
     "         KEY sig (sig)," "         KEY isn (issuer, sn)",
     NULL,
     0},
    {                           /* RPKI_CRL */
     /*
      * Usage notes: this_upd and next_upd are stored in GMT. local_id is a
      * unique identifier obtained as max(local_id) + 1 issuer is the actual
      * CRL issuer, obtained from the issuer field of the CRL (direct CRL).
      * snlist is the list of serial numbers for this issuer. It is an array
      * of 20-byte network byte order unsigned ints that are left-padded with
      * zeroes to each be exactly 20 bytes long. The number of serials in the
      * list is snlen. Some of these revocations may already have happened and
      * the corresponding sn set to 0 in the list. sninuse keeps track of the
      * number of serial numbers that are not zero in the list.  When this
      * number drops to 0, the entire CRL may be deleted from the DB.
      * 
      * Note that snlist is of type MEDIUMBLOB, indicating that it can hold at 
      * most 16M/20 = 838860 entries.
      */
     "rpki_crl",
     "CRL",
     "filename VARCHAR(256) NOT NULL,"
     "dir_id   INT UNSIGNED NOT NULL DEFAULT 1,"
     "issuer   VARCHAR(512) NOT NULL,"
     "last_upd DATETIME NOT NULL,"
     "next_upd DATETIME NOT NULL,"
     "crlno    VARBINARY(20) NOT NULL,"
     "aki      VARCHAR(128),"
     "sig      VARCHAR(520) NOT NULL,"
     "hash     VARCHAR(256),"
     "snlen    INT UNSIGNED DEFAULT 0,"
     "sninuse  INT UNSIGNED DEFAULT 0,"
     "snlist   MEDIUMBLOB,"
     "flags    INT UNSIGNED DEFAULT 0,"
     "local_id INT UNSIGNED NOT NULL UNIQUE,"
     "         PRIMARY KEY (filename, dir_id),"
     "         KEY issuer (issuer),"
     "         KEY aki (aki),"
     "         KEY sig (sig)," "         KEY lid (local_id)",
     NULL,
     0},
    {                           /* RPKI_ROA */
     /*
      * Usage notes: the ski is the ski of the signing cert, and is thus
      * effectively the parent of this ROA. The asn is the AS number from the
      * ROA (there is only one now, not a list). The IP address information is 
      * not stored here; it must be fetched from the file itself using the ROA 
      * read code. local_id is as with certs and crls. 
      */
     "rpki_roa",
     "ROA",
     "filename VARCHAR(256) NOT NULL,"
     "dir_id   INT UNSIGNED NOT NULL DEFAULT 1,"
     "ski      VARCHAR(128) NOT NULL,"
     "sig      VARCHAR(520) NOT NULL,"
     "sigval   INT UNSIGNED DEFAULT 0,"
     "hash     VARCHAR(256),"
     "ip_addrs VARCHAR(32768) NOT NULL,"
     "asn      INT UNSIGNED NOT NULL,"
     "flags    INT UNSIGNED DEFAULT 0,"
     "local_id INT UNSIGNED NOT NULL UNIQUE,"
     "         PRIMARY KEY (filename, dir_id),"
     "         KEY asn (asn),"
     "         KEY sig (sig),"
     "         KEY lid (local_id),"
     "         KEY ski (ski)",
     NULL,
     0},
    {                           /* RPKI_MANIFEST */
     "rpki_manifest",
     "MANIFEST",
     "filename VARCHAR(256) NOT NULL,"
     "dir_id   INT UNSIGNED NOT NULL DEFAULT 1,"
     "ski      VARCHAR(128) NOT NULL,"
     "hash     VARCHAR(256),"
     "this_upd DATETIME NOT NULL,"
     "next_upd DATETIME NOT NULL,"
     "cert_id  INT UNSIGNED NOT NULL,"
     "files    MEDIUMBLOB,"
     "fileslen INT UNSIGNED DEFAULT 0,"
     "flags    INT UNSIGNED DEFAULT 0,"
     "local_id INT UNSIGNED NOT NULL UNIQUE,"
     "         PRIMARY KEY (filename, dir_id),"
     "         KEY lid (local_id),"
     "         KEY ski (ski)",
     NULL,
     0},
    {
     "rpki_ghostbusters",
     "GHOSTBUSTERS",
     "filename VARCHAR(256) NOT NULL,"
     "dir_id   INT UNSIGNED NOT NULL DEFAULT 1,"
     "local_id INT UNSIGNED NOT NULL UNIQUE,"
     "ski      VARCHAR(128) NOT NULL,"
     "hash     VARCHAR(256),"
     "flags    INT UNSIGNED DEFAULT 0,"
     "         PRIMARY KEY (filename, dir_id),"
     "         KEY lid (local_id),"
     "         KEY ski (ski)",
     NULL,
     0},
    {                           /* RPKI_DIR */
     "rpki_dir",
     "DIRECTORY",
     "dirname  VARCHAR(4096) NOT NULL,"
     "dir_id   INT UNSIGNED NOT NULL,"
     "         PRIMARY KEY (dir_id)," "         KEY dirname (dirname)",
     NULL,
     0},
    {                           /* RPKI_METADATA */
     "rpki_metadata",
     "METADATA",
     "rootdir  VARCHAR(4096) NOT NULL,"
     "inited   TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
     "rs_last  TIMESTAMP DEFAULT 0,"
     "qu_last  TIMESTAMP DEFAULT 0,"
     "gc_last  TIMESTAMP DEFAULT 0,"
     "ch_last  TIMESTAMP DEFAULT 0,"
     "flags    INT UNSIGNED DEFAULT 0,"
     "local_id INT UNSIGNED DEFAULT 1," "         PRIMARY KEY (local_id)",
     NULL,
     0},

    // these tables really should be specified in the server
    // directory, but there was no good way to do that and not
    // risk them not being created at initialization

    {                           /* RTR_SESSION */
     "rtr_session",
     "RTR_SESSION",
     "session_id SMALLINT UNSIGNED NOT NULL,"
     "           PRIMARY KEY (session_id)",
     NULL,
     0},
    {                           /* RTR_UPDATE */
     "rtr_update",
     "RTR_UPDATE",
     "serial_num      INT UNSIGNED NOT NULL," "prev_serial_num INT UNSIGNED,"   // NULL 
                                                                                // indicates 
                                                                                // no 
                                                                                // previous 
                                                                                // serial 
                                                                                // number 
                                                                                // currently 
                                                                                // exists
     "create_time     DATETIME NOT NULL,"
     "has_full        BOOLEAN NOT NULL,"
     "                PRIMARY KEY (serial_num),"
     "                UNIQUE KEY (prev_serial_num),"
     "                KEY create_time (create_time)",
     NULL,
     0},
    {                           /* RTR_FULL */
     "rtr_full",
     "RTR_FULL",
     "serial_num  INT UNSIGNED NOT NULL,"
     "asn         INT UNSIGNED NOT NULL,"
     "ip_addr     VARCHAR(50) NOT NULL,"
     "            PRIMARY KEY (serial_num, asn, ip_addr)",
     NULL,
     0},
    {                           /* RTR_INCREMENTAL */
     "rtr_incremental",
     "RTR_INCREMENTAL",
     "serial_num  INT UNSIGNED NOT NULL,"       /* serial number immediately
                                                 * after the incremental
                                                 * changes, i.e. after reading 
                                                 * all of rtr_incremental
                                                 * where serial_num = x, the
                                                 * client is at serial number
                                                 * x */
     "is_announce BOOLEAN NOT NULL,"    /* announcement or withdrawal */
     "asn         INT UNSIGNED NOT NULL,"
     "ip_addr     VARCHAR(50) NOT NULL,"
     "            PRIMARY KEY (serial_num, asn, ip_addr)",
     NULL,
     0},
};

#endif

#endif
