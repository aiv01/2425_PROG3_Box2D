To make cmake/conan integration works,remember to set in your ide the following cmake variable: `CMAKE_PROJECT_TOP_LEVEL_INCLUDES = ./conan_provider.cmake`

For VSCode IDE in `.vscode/settings.json`:
```json
{
    "cmake.configureSettings": {
        "CMAKE_PROJECT_TOP_LEVEL_INCLUDES": "./conan_provider.cmake"
    },    
}
```