
println('Compiling the V project into C...')
system('v -keepc -shared -os ios -o build/scheduling.c . -gc none')

println('Building C object files...')
system('cc -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS26.0.sdk -target aarch64-apple-ios -fobjc-arc -g -O0 -xobjective-c -std=c99 -D_DEFAULT_SOURCE -miphoneos-version-min=13.0 -c build/scheduling.c -o build/scheduling.o')

println('Linking into static library...')
system('ar rcs build/libscheduling.a build/scheduling.o')

println('Copying `build/libscheduling.a` to `SchedulingiOS/Libraries/libscheduling.a`...')
system('cp build/libscheduling.a SchedulingiOS/Libraries/libscheduling.a')

println('Done!')
