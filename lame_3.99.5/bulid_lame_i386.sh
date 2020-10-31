# build lame script for i386

./configure \
--disable-shared \
--disable-frontend \
--host=arm-apple-darwin \
--prefix="/Users/sclcoder/Desktop/multimedia/lame_3.99.5/thin/i386" \
CC="xcrun -sdk iphoneos clang -arch i386" \
CFLAGS="-arch i386 -fembed-bitcode -miphoneos-version-min=7.0" \
LDFLAGS="-arch i386 -fembed-bitcode -miphoneos-version-min=7.0"
make clean
make -j8
make install
