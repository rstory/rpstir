#!/bin/sh -e

THIS_SCRIPT_DIR=`dirname "$0"`
. "$THIS_SCRIPT_DIR/../../../envir.setup"

cd "$THIS_SCRIPT_DIR"/..

./scripts/gen_all.sh

FAILED=""
PASSED=""

cd output
OUTPUT_DIR="`pwd`"

add_file () {
	TYPE="$1" # "good" or "bad"
	FLAGS="$2" # -f or -F
	FILE="$3" # file to add

	FILEBASENAME=`basename "$FILE"`

	case "$FILEBASENAME" in
		*.cer)
			FILETYPE=cert
			;;
		*.roa)
			FILETYPE=roa
			;;
		*.crl)
			FILETYPE=crl
			;;
		*.mft|*.man|*.mnf)
			FILETYPE=man
			;;
		*)
			echo >&2 "Error: unknown filetype for file $FILE"
			exit 1
	esac

	if test x"$TYPE" = x"bad"; then
		if ! "$RPKI_ROOT/proto/rcli" -y $FLAGS "$FILE"; then
			return
		fi

		FILECOUNT=`"$RPKI_ROOT/proto/query" -s "$THIS_SCRIPT_DIR"/querySpecs -t "$FILETYPE" -d filename -f "filename.eq.$FILEBASENAME" | wc -l`
		if test "$FILECOUNT" -ne 0; then
			echo >&2 "Error: adding bad file $FILE succeeded"
			"$RPKI_ROOT/proto/query" -i -t "$FILETYPE" -d flags -f "filename.eq.$FILEBASENAME" 2> /dev/null
			PASSED="$FILE $PASSED"
		fi
	else
		if ! "$RPKI_ROOT/proto/rcli" -y $FLAGS "$FILE"; then
			echo >&2 "Error: adding good file $FILE failed"
			FAILED="$FILE $FAILED"
			return
		fi

		FILECOUNT=`"$RPKI_ROOT/proto/query" -s "$THIS_SCRIPT_DIR"/querySpecs -t "$FILETYPE" -d filename -f "filename.eq.$FILEBASENAME" | wc -l`
		if test "$FILECOUNT" -ne 1; then
			echo >&2 "Error: adding good file $FILE failed"
			"$RPKI_ROOT/proto/query" -i -t "$FILETYPE" -d flags -f "filename.eq.$FILEBASENAME" 2> /dev/null
			FAILED="$FILE $FAILED"
		fi
	fi
}

list_files () {
	PREFIX="$1"
	FILES="$2"

	for FILE in $FILES; do echo "$PREFIX$FILE"; done | sort
}

init_db () {
	"$RPKI_ROOT/run_scripts/initDB.sh"
}

reset_db () {
	"$RPKI_ROOT/proto/rcli" -x -t "$OUTPUT_DIR" -y
	"$RPKI_ROOT/proto/rcli" -y -F "$OUTPUT_DIR"/root.cer
	"$RPKI_ROOT/proto/rcli" -y -f "$OUTPUT_DIR"/root/root.crl
	"$RPKI_ROOT/proto/rcli" -y -f "$OUTPUT_DIR"/root/root.mft
}


init_db

for BAD_ROOT in badRoot*.cer; do
	reset_db
	add_file bad -F "$BAD_ROOT"
done

cd root

for GOOD_SINGLE_FILE in good*; do
	reset_db
	add_file good -f "$GOOD_SINGLE_FILE"
done

for BAD_SINGLE_FILE in bad*; do
	reset_db
	add_file bad -f "$BAD_SINGLE_FILE"
done

for CRL_CERT in CRL*.cer; do
	CRL_NAME=`basename "$CRL_CERT" .cer`
	reset_db
	add_file good -f "$CRL_CERT"
	add_file good -f "$CRL_NAME/$CRL_NAME.mft"
	add_file bad -f "$CRL_NAME/bad$CRL_NAME.crl"
done

for MFT_CERT in MFT*.cer; do
	MFT_NAME=`basename "$MFT_CERT" .cer`
	reset_db
	add_file good -f "$MFT_CERT"
	add_file good -f "$MFT_NAME/$MFT_NAME.crl"
	add_file bad -f "$MFT_NAME/bad$MFT_NAME.mft"
done

if test -n "$FAILED" -o -n "$PASSED"; then
	if test -n "$FAILED"; then
		echo "Failed but should pass:" >&2
		list_files "    " "$FAILED" >&2
	fi
	if test -n "$PASSED"; then
		echo "Passed but should fail:" >&2
		list_files "    " "$PASSED" >&2
	fi
	exit 1
fi
