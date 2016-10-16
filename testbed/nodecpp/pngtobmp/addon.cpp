//addon.cpp
#include "node_modules/nan/nan.h"
#include <iostream>
#include <string>
#include <fstream>
#include "lodepng.h"

using namespace std;
using namespace Nan;
using namespace v8;

void encodeBMP(std::vector<unsigned char>& bmp, const unsigned char* image, int w, int h)
{
  //3 bytes per pixel used for both input and output.
  int inputChannels = 3;
  int outputChannels = 3;
  
  //bytes 0-13
  bmp.push_back('B'); bmp.push_back('M'); //0: bfType
  bmp.push_back(0); bmp.push_back(0); bmp.push_back(0); bmp.push_back(0); //2: bfSize; size not yet known for now, filled in later.
  bmp.push_back(0); bmp.push_back(0); //6: bfReserved1
  bmp.push_back(0); bmp.push_back(0); //8: bfReserved2
  bmp.push_back(54 % 256); bmp.push_back(54 / 256); bmp.push_back(0); bmp.push_back(0); //10: bfOffBits (54 header bytes)

  //bytes 14-53
  bmp.push_back(40); bmp.push_back(0); bmp.push_back(0); bmp.push_back(0);  //14: biSize
  bmp.push_back(w % 256); bmp.push_back(w / 256); bmp.push_back(0); bmp.push_back(0); //18: biWidth
  bmp.push_back(h % 256); bmp.push_back(h / 256); bmp.push_back(0); bmp.push_back(0); //22: biHeight
  bmp.push_back(1); bmp.push_back(0); //26: biPlanes
  bmp.push_back(outputChannels * 8); bmp.push_back(0); //28: biBitCount
  bmp.push_back(0); bmp.push_back(0); bmp.push_back(0); bmp.push_back(0);  //30: biCompression
  bmp.push_back(0); bmp.push_back(0); bmp.push_back(0); bmp.push_back(0);  //34: biSizeImage
  bmp.push_back(0); bmp.push_back(0); bmp.push_back(0); bmp.push_back(0);  //38: biXPelsPerMeter
  bmp.push_back(0); bmp.push_back(0); bmp.push_back(0); bmp.push_back(0);  //42: biYPelsPerMeter
  bmp.push_back(0); bmp.push_back(0); bmp.push_back(0); bmp.push_back(0);  //46: biClrUsed
  bmp.push_back(0); bmp.push_back(0); bmp.push_back(0); bmp.push_back(0);  //50: biClrImportant
  
  /*
  Convert the input RGBRGBRGB pixel buffer to the BMP pixel buffer format. There are 3 differences with the input buffer:
  -BMP stores the rows inversed, from bottom to top
  -BMP stores the color channels in BGR instead of RGB order
  -BMP requires each row to have a multiple of 4 bytes, so sometimes padding bytes are added between rows
  */

  int imagerowbytes = outputChannels * w;
  imagerowbytes = imagerowbytes % 4 == 0 ? imagerowbytes : imagerowbytes + (4 - imagerowbytes % 4); //must be multiple of 4
  
  for(int y = h - 1; y >= 0; y--) //the rows are stored inversed in bmp
  {
    int c = 0;
    for(int x = 0; x < imagerowbytes; x++)
    {
      if(x < w * outputChannels)
      {
        int inc = c;
        //Convert RGB(A) into BGR(A)
        if(c == 0) inc = 2;
        else if(c == 2) inc = 0;
        bmp.push_back(image[inputChannels * (w * y + x / outputChannels) + inc]);
      }
      else bmp.push_back(0);
      c++;
      if(c >= outputChannels) c = 0;
    }
  }

  // Fill in the size
  bmp[2] = bmp.size() % 256;
  bmp[3] = (bmp.size() / 256) % 256;
  bmp[4] = (bmp.size() / 65536) % 256;
  bmp[5] = bmp.size() / 16777216;
}



bool do_convert(vector<unsigned char> & input_data, vector<unsigned char> &bmp){
    vector<unsigned char> image; //raw pixels
    unsigned width, height;
    unsigned error = lodepng::decode(image, width, height, input_data, LCT_RGB, 8);
    if (error){
        cout << "error: " << error << ": " << lodepng_error_text(error) << "\n";
        return false;
    }
    encodeBMP(bmp, &image[0], width, height);
    return true;
}

void buffer_delete_callback(char * data, void * the_vector){
    delete reinterpret_cast<vector<unsigned char>*> (the_vector);
}

NAN_METHOD(SaveBMP){
    unsigned char*buffer = (unsigned char*)node::Buffer::Data(info[0]->ToObject());
    unsigned int size = info[1]->Uint32Value();
    vector<unsigned char> png_data(buffer, buffer + size);

    vector<unsigned char> *bmp = new vector<unsigned char>();
    if (do_convert(png_data, *bmp)){
        info.GetReturnValue().Set(NewBuffer((char*)bmp->data(),bmp->size(),buffer_delete_callback,bmp).ToLocalChecked());
    }
}

NAN_MODULE_INIT(init){
Nan::Set(target, New<String>("saveBMP").ToLocalChecked(), GetFunction(New<FunctionTemplate>(SaveBMP)).ToLocalChecked());
}


NODE_MODULE(addon, init)