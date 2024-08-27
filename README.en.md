# ModLoader

ModLoader is a dynamic module loader for the Windows platform, designed to load DLL modules dynamically. It is open-sourced under the MIT license and was written by MicroFish on August 26, 2024.

## Features

- Dynamically find and load DLL files.
- Provide functionality for finding and executing the entry point of a module.

## Usage

1. Place the ModLoader.c and ModLoader.h files into your project.
2. Ensure your modules adhere to the `MOD_ENTRY` function specification, which should return an integer.
3. Use the `ModFind` function to find all DLL files in a specified path.
4. Use the `ModLoad` function to load and execute a module by index.

## Compilation Guide

1. Make sure your development environment supports C language development.
2. Compile the ModLoader.c file using Visual Studio or another C compiler.
3. Place the resulting DLL file in a path accessible by your application.

## Contributing

We welcome contributions in any form, including but not limited to code, documentation, testing, and bug reports.

## License

This project is licensed under the GPL-3.0 license, with all rights reserved by ViudiraTech.

## Contact Us

For any questions or suggestions, please contact us through the following channels:
- Email: [f13208471983@163.com](mailto:f13208471983@163.com)
- Forum: [http://ViudiraTech.中国/](#)
