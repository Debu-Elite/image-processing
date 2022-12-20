#include <stdlib.h>
#include <stdio.h>
int main()
{
    FILE *streamIn;// making a file pointer
    streamIn = fopen("lena512.bmp", "rb");// pointing the image file using file pointer
    printf(" address before seek = %u\n",*streamIn);// printing the file address
    unsigned char imageHeader[54]; // to get the image header
    fread(imageHeader, sizeof(unsigned char), 54, streamIn);// reading the image header using fread function
    /*

    Following is the declaration for fread() function.

    size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)


    ptr − This is the pointer to a block of memory with a minimum size of size*nmemb bytes.

    size − This is the size in bytes of each element to be read.

     nmemb − This is the number of elements, each one with a size of size bytes.

     stream − This is the pointer to a FILE object that specifies an input stream.
    */

    // extract image height and width from imageHeader
    int width = *(int*)&imageHeader[18];
    int height = *(int*)&imageHeader[22];
	int bitDepth = *(int*)&imageHeader[28];
	int offset = *(int*)&imageHeader[10];

    // colorTable related operations
    unsigned char colorTable[1024];

    if(offset != 54)
    {

    // colore table is present
    printf("color is present\n");
    fseek( streamIn, 54, SEEK_SET);
        printf("address after 54 bytes= %u \n",*streamIn);
		fread(colorTable, sizeof(unsigned char), 1024, streamIn);// reading color table and storing it in colortable array
		//printf(" bitDepth=%d ",bitDepth);
    }

   	// image data reading operations
	int imgDataSize = width * height; // calculate image size

    unsigned char imageData[imgDataSize], newimageData[imgDataSize];// array to store the data of image
    fread( imageData, sizeof(unsigned char), imgDataSize, streamIn);

    for(int i=0;i<=imgDataSize;i++)
    newimageData[i] = 255 - imageData[i];
    FILE *fo = fopen("lena_negative.bmp", "wb");

    fwrite(imageHeader, sizeof(unsigned char), 54, fo); // write the header back.
    fwrite(colorTable, sizeof(unsigned char), 1024, fo); // write the color table back
    fwrite( newimageData, sizeof(unsigned char), imgDataSize, fo); // write the values of the negative image.

fclose(fo);
fclose(streamIn);

}
