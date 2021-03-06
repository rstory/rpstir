/*****************************************************************************
File:     asn_timedefs.h
Contents: Header file for basic ASN.1 functions.
System:   ASN development.
Created:
Author:   Charles W. Gardiner <gardiner@bbn.com>

Remarks:

*****************************************************************************/
#ifndef _ASN_TIMEDEFS_H
#define _ASN_TIMEDEFS_H
#define UTCBASE 70
#define UTCYR 0
#define UTCYRSIZ 2
#define UTCMO (UTCYR + UTCYRSIZ)
#define UTCMOSIZ 2
#define UTCDA  (UTCMO + UTCMOSIZ)
#define UTCDASIZ 2
#define UTCHR  (UTCDA + UTCDASIZ)
#define UTCHRSIZ 2
#define UTCMI  (UTCHR + UTCHRSIZ)
#define UTCMISIZ 2
#define UTCSE (UTCMI + UTCMISIZ)
#define UTCSESIZ 2
#define UTCSFXHR 1
#define UTCSFXMI (UTCSFXHR + UTCHRSIZ)
#define UTCT_SIZE 16
#define GENTBASE (1900 + UTCBASE)
#define GENTYR 0
#define GENTYRSIZ 4
#define GENTSE (UTCSE + GENTYRSIZ - UTCYRSIZ)
#endif                          /* ASN_TIMEDEFS_H */
