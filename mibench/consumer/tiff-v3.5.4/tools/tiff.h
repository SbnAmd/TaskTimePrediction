//
// Created by sbn on 5/25/25.
//

#ifndef TIFF_H
#define TIFF_H


#define TIFF2BW_INPUT_FILE_LARGE    "../tiff-data/large.tif"
#define TIFF2BW_INPUT_FILE_SMALL    "../tiff-data/small.tif"
#define TIFF2BW_OUTPUT_FILE_LARGE   "output_largebw.tif"
#define TIFF2BW_OUTPUT_FILE_SMALL   "output_smallbw.tif"

#define TIFF2RGBA_INPUT_FILE_LARGE    "../tiff-data/large.tif"
#define TIFF2RGBA_INPUT_FILE_SMALL    "../tiff-data/small.tif"
#define TIFF2RGBA_OUTPUT_FILE_LARGE   "output_largergba.tif"
#define TIFF2RGBA_OUTPUT_FILE_SMALL   "output_smallrgba.tif"

#define TIFFDITHER_INPUT_FILE_LARGE    "../tiff-data/largebw.tif"
#define TIFFDITHER_INPUT_FILE_SMALL    "../tiff-data/smallbw.tif"
#define TIFFDITHER_OUTPUT_FILE_LARGE   "output_largedither.tif"
#define TIFFDITHER_OUTPUT_FILE_SMALL   "output_smalldither.tif"

#define TIFFMEDIAN_INPUT_FILE_LARGE    "../tiff-data/large.tif"
#define TIFFMEDIAN_INPUT_FILE_SMALL    "../tiff-data/small.tif"
#define TIFFMEDIAN_OUTPUT_FILE_LARGE   "output_largemedian.tif"
#define TIFFMEDIAN_OUTPUT_FILE_SMALL   "output_smallmedian.tif"

int _tiff2bw(int argc, char* argv[]);
int _tiff2rgba(int argc, char* argv[]);
int _tiffdither(int argc, char* argv[]);
int tiffmedian(int argc, char* argv[]);

void _tiff2bw_large() {
    _tiff2bw(3, (char*[]){"../tiff-v3.5.4/tools/tiff2bw", TIFF2BW_INPUT_FILE_LARGE, TIFF2BW_OUTPUT_FILE_LARGE});
}

void _tiff2bw_small() {
    _tiff2bw(3, (char*[]){"../tiff-v3.5.4/tools/tiff2bw", TIFF2BW_INPUT_FILE_SMALL, TIFF2BW_OUTPUT_FILE_SMALL});
}

void _tiff2rgba_large() {
    _tiff2rgba(5, (char*[]){"../tiff-v3.5.4/tools/tiff2rgba", "-c", "none", TIFF2RGBA_INPUT_FILE_LARGE, TIFF2RGBA_OUTPUT_FILE_LARGE});
}

void _tiff2rgba_small() {
    _tiff2rgba(5, (char*[]){"../tiff-v3.5.4/tools/tiff2rgba", "-c", "none", TIFF2RGBA_INPUT_FILE_SMALL, TIFF2RGBA_OUTPUT_FILE_SMALL});
}

void _tiffdither_large() {
    _tiffdither(5, (char*[]){"../tiff-v3.5.4/tools/tiffdither", "-c", "g4", TIFFDITHER_INPUT_FILE_LARGE, TIFFDITHER_OUTPUT_FILE_LARGE});
}

void _tiffdither_small() {
    _tiffdither(5, (char*[]){"../tiff-v3.5.4/tools/tiffdither", "-c", "g4", TIFFDITHER_INPUT_FILE_SMALL, TIFFDITHER_OUTPUT_FILE_SMALL});
}

void _tiffmedian_large() {
    _tiffdither(5, (char*[]){"../tiff-v3.5.4/tools/tiffmedian", TIFFMEDIAN_INPUT_FILE_LARGE, TIFFMEDIAN_OUTPUT_FILE_LARGE});
}

void _tiffmedian_small() {
    _tiffdither(5, (char*[]){"../tiff-v3.5.4/tools/tiffmedian", TIFFMEDIAN_INPUT_FILE_SMALL, TIFFMEDIAN_OUTPUT_FILE_SMALL});
}


#endif //TIFF_H
