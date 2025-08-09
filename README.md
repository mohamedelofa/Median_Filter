# Median Filter

A simple image processing tool that applies a Median Filter to PPM images to reduce noise, supporting full-color (RGB) images. The program reads a PPM file, adds padding to handle image borders, and then calculates the median value for each color channel (R, G, B) using a configurable kernel size.

## Features

- **Noise Reduction:** Effectively reduces noise in PPM images using a median filter.
- **Full-color Support:** Works on RGB images, processing each color channel independently.
- **Configurable Kernel Size:** Allows users to specify the size of the kernel for flexible filtering.
- **Border Handling:** Adds padding to manage image borders without artifacts.

- ## Viewing PPM Files

To display PPM files, you can use [XnViewMP](https://www.xnview.com/en/xnviewmp/), a free and versatile image viewer that supports the PPM format.

## Technologies

- **Language:** C++
- **Topics:** image-processing, median-filter

## Usage

1. **Input:** Provide a PPM (Portable Pixmap) image file.
2. **Configuration:** Specify the desired kernel size for median filtering.
3. **Run:** Execute the program; it will output a filtered PPM image with reduced noise.

### Example Command

```bash
./median_filter input.ppm output.ppm 3
```

Where `input.ppm` is your source image, `output.ppm` is the result, and `3` is the kernel size.

## How It Works

- The filter reads a PPM image and adds padding to handle border effects.
- For each pixel, it calculates the median value for each RGB channel within the kernel neighborhood.
- The resulting image preserves edges while removing impulse noise.

## License

This project currently does not specify a license.

## Author

- [mohamedelofa](https://github.com/mohamedelofa)

---
Feel free to contribute or open issues for suggestions and improvements!
