# build lame script for armv7

./configure \
--disable-shared \
--disable-frontend \
--host=arm-apple-darwin \
--prefix="/Users/sclcoder/Desktop/multimedia/lame_3.99.5/thin/arm64" \
CC="xcrun -sdk iphoneos clang -arch arm64" \
CFLAGS="-arch arm64 -fembed-bitcode -miphoneos-version-min=7.0" \
LDFLAGS="-arch arm64 -fembed-bitcode -miphoneos-version-min=7.0"
make clean
make -j8
make install
