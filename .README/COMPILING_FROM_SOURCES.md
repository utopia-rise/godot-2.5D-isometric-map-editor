# Compiling from sources

In this section we will deal with compilation from sources of libraries.  
***/!\ Disclaimer***: This is for advanced users, note that libraries are already compiled in released addon. You can
find them in `addons/IsometricMap/libs`.

## Typical project Structure

Here is the project structure we recommend to compile from sources.  
```
└── Project root
    ├── godot-cpp (gdnative bindings, consider using a git submodule)
    └── godot-2.5D-isometric-map-editor (this repo, consider using it as a submodule of you GDNatives repo)
        ├── demo (contains demo project)
        ├── .github (contains github actions)
        ├── .README (documentations files)
        ├── CMakeLists.txt (Here for CLion)
        ├── LICENSE
        ├── jni (here for android build)
        ├── README.md
        ├── SConstruct (here to build on Windows, Linux, OSX and IOS
        └── src
```
For `godot-cpp` we recommend using [Utopia-Rise's fork](https://github.com/utopia-rise/godot-cpp) for android build
purpose, you can then check it out on `utopia-3.2` branch.

## Build cpp bindings

The first thing to do is to build `godot-cpp` bindings.  
Go in `godot-cpp` folder and build for the platform you want, following the
[documentation](https://github.com/godotengine/godot-cpp/blob/master/README.md#compiling-the-c-bindings-library).

### Build for ios

As ios is not documented, here is the command line to use:  
```shell script
scons platform=ios generate_bindings=yes ios_arch=[arch]
```
with: 
- `[arch] = {armv7, arm64, x86_64}`

You should then have you compiled library in `godot-cpp/bin` folder.

## Build addon

Head to `godot-2.5D-isometric-map-editor` folder.  
Excepted for android, which does not use scons but ndk-build, the command is the same than the one for bindings, without
the `generate_bindings` arguments.  
*Example*: `scons platform=windows bits=64`

You should have the built addon in `godot-2.5D-isometric-map-editor/bin` folder.

### Build for android

We use `ndk-build` for to get addon compiled for android.  
Here is the command:
`$ANDROID_NDK_ROOT/ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=Android.mk  APP_PLATFORM=android-21`

You should have set `ANDROID_NDK_ROOT` in [Build cpp bindings](#build-cpp-bindings) if you followed the
[documentation](https://github.com/godotengine/godot-cpp/blob/master/README.md#compiling-the-c-bindings-library).

You should have built addon in `godot-2.5D-isometric-map-editor/libs` folder.

## Using compiled addon

If you want to use built addon, simply copy it to the right platform folder in
`addons/IsometricMap/libs` of your project.  
As an example for demo project on linux:
`godot-2.5D-isometric-map-editor/demo/addons/IsometricMap/libs/linux/libGodotIsoMapEditor.linux.release.64.so`

You can then run editor and game with you modifications.  
By the way, feel free to PR !