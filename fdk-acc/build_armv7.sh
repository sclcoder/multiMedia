./configure \
--enable-static \
--disable-shared \
--host=arm-apple-darwin \
--prefix="/Users/sclcoder/Desktop/multimedia/fdk-acc/thin/armv7"
CC="xcrun -sdk iphoneos clang" \
AS="gas-preprocessor.pl $CC"
CFLAGS="-arch armv7 -mios-simulator-version-min=7.0" \
LDFLAGS="-arch armv7 -mios-simulator-version-min=7.0"
make clean
make -j8
make install
