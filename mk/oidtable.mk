pkgdata_DATA += var/oidtable
CLEANFILES += var/oidtable

var_oidtable_ASN1_H = \
	lib/rpki-asn1/Algorithms.h \
	lib/rpki-asn1/blob.h \
	lib/rpki-asn1/certificate.h \
	lib/rpki-asn1/crlv2.h \
	lib/rpki-asn1/extensions.h \
	lib/rpki-asn1/keyfile.h \
	lib/rpki-asn1/manifest.h \
	lib/rpki-asn1/name.h \
	lib/rpki-asn1/orname.h \
	lib/rpki-asn1/privkey.h \
	lib/rpki-asn1/roa.h \
	lib/rpki-asn1/serial_number.h

var/oidtable: ./bin/asn1/make_oidtable $(var_oidtable_ASN1_H) $(TESTS_ENVIRONTMENT_DEPS)
	TEST_LOG_NAME=`basename "$@"` \
		TEST_LOG_DIR=`dirname "$@"` \
		$(TESTS_ENVIRONMENT) \
		./bin/asn1/make_oidtable var/oidtable $(var_oidtable_ASN1_H)

AM_CPPFLAGS += \
	-DOIDTABLE='(getenv("TESTS_TOP_BUILDDIR") == NULL ? "$(pkgdatadir)/oidtable" : "$(abs_top_builddir)/var/oidtable")'
