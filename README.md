# RLE-Compression

A simple C program to compress/decompress file contents using Run-Length Encoding algorithm

I wrote this program because this is one of the assignments that my teacher gave me, and I also have some interest, so I decided to publish it on Github

## Compile

```sh
make
```

This project was compiled and succesfully tested on:
- Linux

## Usage

```txt
Usage:
	./rle-compression [options] [files]
Options:
	-b,  --banner		Display the banner
	-e,  --encode		Encode content of files
	-d,  --decode		Decode content of files
	-h,  --help		Display this help and exit
	-v,  --version		Show this program version
Examples:
	./rle-compression -b -e test.txt
	./rle-compression -b -d test.txt.enc
```

## References

While creating this program, I utilized various websites as resources. I hope that this will useful...

- [Run Length Encoding and Decoding](https://www.geeksforgeeks.org/run-length-encoding/)
- [Run-Length Encoding (RLE) Algorithm: Step-by-Step Guide](https://medium.com/@ishifoev/run-length-encoding-rle-algorithm-step-by-step-guide-b0b89f3a4a9f)
- [Online rle-compression tool from dcode.fr](https://www.dcode.fr/rle-compression)
- [ASCII banner](https://manytools.org/hacker-tools/ascii-banner/)

## License

This project is published under [MIT License][license]

[license]: https://github.com/T3l3sc0p3/rle-compression-c/blob/master/LICENSE
