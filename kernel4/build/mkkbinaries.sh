#! /bin/sh

binary_name () {
    echo "_binary_"$1 | tr -d '\n' | tr -c '[A-Za-z0-9_]' _
}

if [ $1 = "-c" ]; then
    shift
    for i in "$@"; do
        j=`binary_name "$i"`
        echo "extern unsigned char ${j}_start[];"
        echo "extern unsigned char ${j}_end[];"
    done

    echo "static struct ramimage {"
    echo "    unsigned char* begin;"
    echo "    unsigned char* end;"
    echo "} ramimages[] = {"

    comma=""
    for i in "$@"; do
        j=`binary_name "$i"`
        echo "    $comma{ ${j}_start, ${j}_end }"
        comma=", "
    done

    echo "};"

elif [ $1 = "-h" ]; then
    shift
    echo "#ifndef WEENSYOS_K_BINARIES_H"
    echo "#define WEENSYOS_K_BINARIES_H 1"

    n=0
    for i in "$@"; do
        j=`binary_name "$i" | sed s/_binary_obj_/binary_/ | tr a-z A-Z`
        echo "#define WEENSYOS_$j $n"
        n=`expr $n + 1`
    done

    echo "#define WEENSYOS_NBINARIES $n"
    echo "#endif"

else
    echo "Usage: mkkbinaries.sh [-c | -h] BINARIES..." 1>&2
    exit 1
fi
