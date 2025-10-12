
println('Compiling the V project into C code...')
if system('v -keepc -shared -os ios -o build/scheduling.c .') == 1 {
	return
}

println('Building C object files...')
if system('cc -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS26.0.sdk -target aarch64-apple-ios -fobjc-arc -g -O0 -xobjective-c -std=c99 -D_DEFAULT_SOURCE -miphoneos-version-min=13.0 -c build/scheduling.c -I thirdparty/libgc/include -o build/scheduling.o') == 1 {
	return
}

println('Linking into static library...')
if system('ar rcs build/libscheduling.a build/scheduling.o') == 1 {
	return
}

println('Copying `build/libscheduling.a` to `SchedulingiOS/Libraries/libscheduling.a`...')
if system('cp build/libscheduling.a SchedulingiOS/Libraries/libscheduling.a') == 1 {
	return
}

println('Done!')
