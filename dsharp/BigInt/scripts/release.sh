#!/bin/bash

(comment="\
/*\n\
    BigInt\n\
    ------\n\
    Arbitrary-sized integer class for C++.\n\
    \n\
    Version: $BIGINT_VERSION\n\
    Released on: $(date +'%d %B %Y %R %Z')\n\
    Author: Syed Faheel Ahmad (faheel@live.in)\n\
    Project on GitHub: https://github.com/faheel/BigInt\n\
    License: MIT\n\
*/\n\n"

printf "$comment"

# topologically sorted list of header files
header_files="BigInt.hpp \
    functions/utility.hpp \
    functions/random.hpp \
    constructors/constructors.hpp \
    functions/conversion.hpp \
    operators/assignment.hpp \
    operators/unary_arithmetic.hpp \
    operators/relational.hpp \
    functions/math.hpp \
    operators/binary_arithmetic.hpp \
    operators/arithmetic_assignment.hpp \
    operators/increment_decrement.hpp \
    operators/io_stream.hpp"

# First all #include's, then we open an anonymous namespace to
# prevent multiple definition errors.
for file in $header_files
do
    cat "include/$file" | grep "^#include"
done
echo '#pragma GCC diagnostic push'
echo '#pragma GCC diagnostic ignored "-Wunused-function"'
echo 'namespace {'

# append the contents of each header file to the release file,
# except the #include's.
for file in $header_files
do
    cat "include/$file" | grep -v "^#include"
    printf "\n\n"
done

echo '} /* namespace */'
echo '#pragma GCC diagnostic pop') |
# delete includes for non-standard header files from the release file
sed "/#include \"*\"/d"
