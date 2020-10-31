./configure \
--enable-static \
--disable-shared \
--host=arm-apple-darwin \
--prefix="/Users/sclcoder/Desktop/multimedia/fdk-acc/thin/arm64"
CC="xcrun -sdk iphoneos clang" \
AS="gas-preprocessor.pl $CC"
CFLAGS="-arch arm64 -mios-simulator-version-min=7.0" \
LDFLAGS="-arch arm64 -mios-simulator-version-min=7.0"
make clean
make -j8
make install
